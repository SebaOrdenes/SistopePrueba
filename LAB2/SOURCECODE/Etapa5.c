#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "../INCLUDE/Etapa5.h"
//ENTRADA: unsigned char**, int, int, int, int *
//FUNCIONAMIENTO: funcionp que sirve para clasificar la imagen una vez convolucionada y binarizada, con el fin de determinar si nearly black o no
//SALIDA: no aplica
void clasificar(unsigned char ** matrizGrayBinarizada,int alto,int ancho,int umbralClasificar,int * resultadosDeClasificacion){
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
		*resultadosDeClasificacion=1;// nearly black
	}
	else{
		*resultadosDeClasificacion=-1;// no nearly black
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
        int resultado = 0;
        unsigned char ** matrizGrayConvolucionadayBinarizada;
        for(int i=1;i<=atoi(argv[1]);i++){ 
        	int dimensiones3[2];
        	read(STDIN_FILENO,dimensiones3,2*sizeof(int));
        	fflush(stdin);
       		matrizGrayConvolucionadayBinarizada=(unsigned char**)malloc(dimensiones3[0]*sizeof(unsigned char *));
        	for(int j=0;j<dimensiones3[0];j++){
           		matrizGrayConvolucionadayBinarizada[j]=(unsigned char*)malloc(dimensiones3[1]*sizeof(unsigned char));
        	}
        	unsigned char filaDeLaImagen2[dimensiones3[1]];
        	for(int j =0;j<dimensiones3[0];j++){

           		read(STDIN_FILENO,filaDeLaImagen2,dimensiones3[1]*sizeof(unsigned char));
           		fflush(stdin);
           		for(int k=0;k<dimensiones3[1];k++){
               		matrizGrayConvolucionadayBinarizada[j][k]=filaDeLaImagen2[k];
               
           		}
        	}
        	 
        
        	clasificar(matrizGrayConvolucionadayBinarizada,dimensiones3[0],dimensiones3[1],atoi(argv[3]),&resultado);
        	int dimensiones4[3];//dimensiones de la matrizGrayConvolucionadayBinarizada y el resulato de la clasificacion
            dimensiones4[0]=dimensiones3[0];// cantidad de filas
            dimensiones4[1]=dimensiones3[1];// cantidad de columnas
            dimensiones4[2]=resultado;// resultado de la clasificacion

            write(STDOUT_FILENO,dimensiones4,3*sizeof(int));// escribir el arreglo dimensiones4
            unsigned char filaDeLaImagen3[dimensiones4[1]];
            for(int j =0;j<dimensiones4[0];j++){
                for(int k=0;k<dimensiones4[1];k++){
                    filaDeLaImagen3[k]=matrizGrayConvolucionadayBinarizada[j][k];
                }
                write(STDOUT_FILENO,filaDeLaImagen3,dimensiones4[1]*sizeof(unsigned char));// escrbir una fila de la matrizGrayConvolucionadayBinarizada
                fflush(stdout);
            }
        } 
    }
    wait(NULL);
    return 0;
}
