#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "Etapa6.h"
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
	// printf("%d\n",porcentajeDePixelesNegros);
	escribirImagen(alto,ancho,numeroImagen,matrizGrayBinarizada);
	if(porcentajeDePixelesNegros>=umbralClasificar){
		(*resultadosDeClasificacion)[numeroImagen-1]=1;
	}
	else{
		(*resultadosDeClasificacion)[numeroImagen-1]=-1;
	}
}