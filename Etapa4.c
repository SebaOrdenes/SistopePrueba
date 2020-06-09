#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "Etapa5.h"
void binarizar(unsigned char ** matrizGrayConvolucionada,int alto,int ancho,int numeroImagen,int umbralBinarizar,int umbralClasificar,int **resultadosDeClasificacion){
	unsigned char ** matrizGrayBinarizada;
	matrizGrayBinarizada=(unsigned char**)malloc(alto*sizeof(unsigned char*));
	for(int i=0;i<alto;i++){
		matrizGrayBinarizada[i]=(unsigned char *)malloc(ancho*sizeof(unsigned char));
	}
	for(int i=0;i<alto;i++){
		for (int j=0;j<ancho;j++){
			if(matrizGrayConvolucionada[i][j]>umbralBinarizar){
				matrizGrayBinarizada[i][j]=255;
			}
			else{
				matrizGrayBinarizada[i][j]=0;
			}
		}
	}
	clasificar(matrizGrayBinarizada,alto,ancho,numeroImagen,umbralClasificar,resultadosDeClasificacion);
	for(int i=0;i<alto;i++){
		free(matrizGrayBinarizada[i]);
	}
	free(matrizGrayBinarizada);
}