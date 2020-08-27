#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "../INCLUDE/Etapa4.h"

//ENTRADA:unsigned char**, unsigned char *** , int , int 
//FUNCIONAMIENTO: función que binariza la matriz gray ya convolucionada.
//SALIDA:no aplica
void binarizar(unsigned char ** matrizGrayConvolucionada,unsigned char *** matrizGrayConvolucionadayBinarizada,int alto,int ancho,int umbralBinarizar){
	(*matrizGrayConvolucionadayBinarizada)=(unsigned char**)malloc(alto*sizeof(unsigned char*));
	for(int i=0;i<alto;i++){
		(*matrizGrayConvolucionadayBinarizada)[i]=(unsigned char *)malloc(ancho*sizeof(unsigned char));
	}
	for(int i=0;i<alto;i++){
		for (int j=0;j<ancho;j++){
			if(matrizGrayConvolucionada[i][j]>umbralBinarizar){
				(*matrizGrayConvolucionadayBinarizada)[i][j]=255;
			}
			else{
				(*matrizGrayConvolucionadayBinarizada)[i][j]=0;
			}
		}
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
        char *args[] = {"Etapa4.out",argv[1],argv[2],argv[3],argv[4],argv[5],NULL};
        execvp("SOURCECODE/Etapa4.out",args);
    }
    else{
        dup2(tuberia[1],STDOUT_FILENO);
        close(tuberia[0]);
        close(tuberia[1]);
        unsigned char ** matrizGrayConvolucionada;
        unsigned char ** matrizGrayConvolucionadayBinarizada;
        for(int i=1;i<=atoi(argv[1]);i++){ 
        	int dimensiones2[2];
        	read(STDIN_FILENO,dimensiones2,2*sizeof(int));
        	fflush(stdin);
       		matrizGrayConvolucionada=(unsigned char**)malloc(dimensiones2[0]*sizeof(unsigned char *));
        	for(int j=0;j<dimensiones2[0];j++){
           		matrizGrayConvolucionada[j]=(unsigned char*)malloc(dimensiones2[1]*sizeof(unsigned char));
        	}
        	unsigned char filaDeLaImagen1[dimensiones2[1]];
        	for(int j =0;j<dimensiones2[0];j++){

           		read(STDIN_FILENO,filaDeLaImagen1,dimensiones2[1]*sizeof(unsigned char));
           		fflush(stdin);
           		for(int k=0;k<dimensiones2[1];k++){
               		matrizGrayConvolucionada[j][k]=filaDeLaImagen1[k];
               
           		}
        	}
        	binarizar(matrizGrayConvolucionada,&matrizGrayConvolucionadayBinarizada,dimensiones2[0],dimensiones2[1],atoi(argv[2]));
        	int dimensiones3[2];
            dimensiones3[0]=dimensiones2[0];
            dimensiones3[1]=dimensiones2[1];
            write(STDOUT_FILENO,dimensiones3,2*sizeof(int));
            unsigned char filaDeLaImagen2[dimensiones3[1]];
            for(int j =0;j<dimensiones3[0];j++){
                for(int k=0;k<dimensiones3[1];k++){
                    filaDeLaImagen2[k]=matrizGrayConvolucionadayBinarizada[j][k];
                }
                write(STDOUT_FILENO,filaDeLaImagen2,dimensiones3[1]*sizeof(unsigned char));
                fflush(stdout);
            }
        } 
    }
    wait(NULL);
    return 0;
}