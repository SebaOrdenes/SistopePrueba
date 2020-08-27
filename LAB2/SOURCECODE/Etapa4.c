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
int main(int argc,char* argv[]){}