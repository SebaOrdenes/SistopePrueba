#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "../INCLUDE/Etapa2.h"
//Entradas:int, int, unsigned char **, unsigned char ***
//Funcionamiento: funcion principal que transforma la matriz rgb de la imagen a matriz gray
//Salidas:no aplica 
void rgbAgray(int alto,int ancho,unsigned char ** pixeles,unsigned char *** matrizGray){
	int i=0;
	(*matrizGray)=(unsigned char **)malloc(alto*sizeof(unsigned char*));
	for(int z=0;z<alto;z++){
		(*matrizGray)[z]=(unsigned char*)malloc(ancho*sizeof(unsigned char));
	}
	for(int j=0;j<alto;j++){
		for(int k=0;k<ancho;k++){
			(*matrizGray)[j][k]=(((double)pixeles[i][0])*0.3+((double)pixeles[i][1])*0.59+((double)pixeles[i][2])*0.11);
			i++;
		}
	}
}

int main(int argc , char * argv[]){
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
    	char *args[] = {"Etapa3.out",argv[1],argv[2],argv[3],argv[4],argv[5],NULL};
    	execvp("SOURCECODE/Etapa3.out",args);
  	}
  	else{
  		dup2(tuberia[1],STDOUT_FILENO);
    	close(tuberia[0]);
    	close(tuberia[1]);
		unsigned char ** matrizPixeles;
		unsigned char ** matrizGray;
		for(int i = 1;i<=atoi(argv[1]);i++){
			int dimensiones[4];
			read(STDIN_FILENO,dimensiones,4*sizeof(int));
			fflush(stdin);
			matrizPixeles=(unsigned char**)malloc(dimensiones[0]*sizeof(unsigned char *));
			for(int j=0;j<dimensiones[0];j++){
				matrizPixeles[j]=(unsigned char*)malloc(dimensiones[1]*sizeof(unsigned char));
			}
			unsigned char pixeles[3];
			for(int j =0;j<dimensiones[0];j++){
				read(STDIN_FILENO,pixeles,3*sizeof(unsigned char));
				fflush(stdin);
				matrizPixeles[j][0]=pixeles[0];
				matrizPixeles[j][1]=pixeles[1];
				matrizPixeles[j][2]=pixeles[2];
				
			}
			rgbAgray(dimensiones[3],dimensiones[4],matrizPixeles,&matrizGray);
			int dimensiones1[2];
			dimensiones1[0]=dimensiones[3];
			dimensiones1[1]=dimensiones[4];
			write(STDOUT_FILENO,dimensiones1,2*sizeof(int));
			unsigned char filaDeLaMatriz[dimensiones[4]];
			for(int j=0;j<dimensiones[3];j++){
				for(int k=0;k<dimensiones[4];k++){
					filaDeLaMatriz[k]=matrizGray[j][k];
				}
				write(STDOUT_FILENO,filaDeLaMatriz,dimensiones[4]*sizeof(unsigned char));
			}


		}
	}
	wait(NULL);
	return 0;
}