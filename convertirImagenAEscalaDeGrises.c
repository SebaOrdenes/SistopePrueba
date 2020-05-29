#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include "convertirImagenAEscalaDeGrises.h"
#include "aplicarFiltro.h"

//Entradas:
//Funcionamiento:
//Salidas:
void rgbAgray(int alto,int ancho,unsigned char ***pixeles,int numeroImagen,int umbralBinarizar,int umbrarClasificar,char* nombreArchivoMascara,int bandera){
	unsigned char gray[alto][ancho];
	int i=0;
	int numeros[9];
	for(int j=0;j<alto;j++){
		for(int k=0;k<ancho;k++){
			gray[j][k]=(int)round(((double)(*pixeles)[i][0])*0.3+((double)(*pixeles)[i][1])*0.59+((double)(*pixeles)[i][2])*0.11);
			(*pixeles)[i][0]=(int)round(((double)(*pixeles)[i][0])*0.3);
			(*pixeles)[i][1]=(int)round(((double)(*pixeles)[i][1])*0.59);
			(*pixeles)[i][2]=(int)round(((double)(*pixeles)[i][2])*0.11);
			i++;
			//printf("%d %d\n",gray[j][k],i);
		}
	}
	/*for(int j=0;j<alto;j++){
		for(int k=0;k<ancho;k++){
			printf("%d ",gray[j][k]);
		}
		printf("\n");
	}*/

int *arreglo= leerMascara(nombreArchivoMascara,numeros);
}