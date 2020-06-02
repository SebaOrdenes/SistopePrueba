#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include "aplicarFiltro.h"

//Entradas:
//Funcionamiento:
//Salidas:
void rgbAgray(int alto,int ancho,unsigned char ***pixeles,int numeroImagen,int umbralBinarizar,int umbrarClasificar,char* nombreArchivoMascara,int bandera,int ** resultadosDeClasificacion){
	unsigned char ** gray;
	int i=0;
	//int numeros[9];
	gray=(unsigned char **)malloc(alto*sizeof(unsigned char*));
	for(int z=0;z<alto;z++){
		gray[z]=(unsigned char*)malloc(ancho*sizeof(unsigned char));
	}
	for(int j=0;j<alto;j++){
		for(int k=0;k<ancho;k++){
			gray[j][k]=(int)round(((double)(*pixeles)[i][0])*0.3+((double)(*pixeles)[i][1])*0.59+((double)(*pixeles)[i][2])*0.11);
			(*pixeles)[i][0]=(int)round(((double)(*pixeles)[i][0])*0.3);
			(*pixeles)[i][1]=(int)round(((double)(*pixeles)[i][1])*0.59);
			(*pixeles)[i][2]=(int)round(((double)(*pixeles)[i][2])*0.11);
			i++;
		}
	}
	applyFilter(gray,nombreArchivoMascara,alto,ancho,numeroImagen,umbralBinarizar,umbrarClasificar,bandera,resultadosDeClasificacion);
	for(int z=0;z<alto;z++){
		free(gray[z]);
	}
	free(gray);
}