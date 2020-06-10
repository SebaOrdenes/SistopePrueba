#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "Etapa6.h"
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
<<<<<<< HEAD
	porcentajeDePixelesNegros=(int)(((double)cantidadDePixelesNegros/(double)(alto * ancho))*100.0);
	// printf("%d\n",porcentajeDePixelesNegros);
=======
	porcentajeDePixelesNegros=(((double)cantidadDePixelesNegros/(double)(alto * ancho))*100.0);
	printf("%d\n",porcentajeDePixelesNegros);
>>>>>>> master
	escribirImagen(alto,ancho,numeroImagen,matrizGrayBinarizada);
	if(porcentajeDePixelesNegros>=umbralClasificar){
		(*resultadosDeClasificacion)[numeroImagen-1]=1;
	}
	else{
		(*resultadosDeClasificacion)[numeroImagen-1]=-1;
	}
}