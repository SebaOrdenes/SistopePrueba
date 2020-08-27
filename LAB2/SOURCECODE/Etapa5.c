#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../INCLUDE/Etapa5.h"
//ENTRADA: unsigned char**, int, int, int, int ,int int**
//FUNCIONAMIENTO: funcion que a partir que sirve para clasificar la imagen una vez convolucionada, para saber si aplica o no como nearly black
//SALIDA: no aplica
void clasificar(unsigned char ** matrizGrayBinarizada,int alto,int ancho,int numeroImagen,int umbralClasificar,int ** resultadosDeClasificacion){
	int cantidadDePixelesNegros=0;
	int porcentajeDePixelesNegros;
	for (int i=0;i<alto;i++){
		for(int j=0;j<ancho;j++){
			if(matrizGrayBinarizada[i][j]==0){
				cantidadDePixelesNegros++;
			}
		}
	}
	porcentajeDePixelesNegros=(int)(((double)cantidadDePixelesNegros/(double)(alto * ancho))*100.0);
	if(porcentajeDePixelesNegros>=umbralClasificar){
		(*resultadosDeClasificacion)[numeroImagen-1]=1;
	}
	else{
		(*resultadosDeClasificacion)[numeroImagen-1]=-1;
	}
}

int main(int argc,char* argv[]){
	int tuberia[2];
    pipe(tuberia);
    pid_t pid =fork();
    if(pid < 0){
        printf("No se pudo crear el hijo\n");
        exit(EXIT_FAILURE);
    }
    else if(pid == 0){
        dup2(tuberia[0],STDIN_FILENO);
        close(tuberia[0]);
        close(tuberia[1]);
        char *args[] = {"Etapa6.out",argv[1],argv[2],argv[3],argv[4],argv[5],NULL};
        execvp("SOURCECODE/Etapa6.out",args);
    }
    else{
        dup2(tuberia[1],STDOUT_FILENO);
        close(tuberia[0]);
        close(tuberia[1]);
    }
}
