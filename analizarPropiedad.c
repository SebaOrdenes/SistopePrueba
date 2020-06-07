#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
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
	porcentajeDePixelesNegros=(int)round(((double)cantidadDePixelesNegros/(double)(alto * ancho))*100.0);
	printf("%d\n",porcentajeDePixelesNegros);
	if(porcentajeDePixelesNegros>=umbralClasificar){
		(*resultadosDeClasificacion)[numeroImagen-1]=1;
	}
	else{
		(*resultadosDeClasificacion)[numeroImagen-1]=-1;
	}
}