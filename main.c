#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "recibirArgumentos.h"
//#include "leerImagenesRGB.h"

int main(int argc, char * argv[]){
	int cantidadDeImagenes, umbralParaBinarizarLaImagen,umbralParaClasificacion,bandera;
	char nombreArchivoMascara[100];
	bandera=0;
	recibirArgumentos(argc,argv,&cantidadDeImagenes,&umbralParaBinarizarLaImagen,&umbralParaClasificacion,nombreArchivoMascara,&bandera);
	printf("La cantidad de imagenes son: %d\n", cantidadDeImagenes);
	printf("El umbral para binarizar la imagen es: %d\n", umbralParaBinarizarLaImagen);
	printf("El umbral para clasificar la imagen es: %d\n", umbralParaClasificacion);
	printf("El nombre del archivo que contiene la mascara es: %s\n", nombreArchivoMascara);
	printf("La condición de la bandera es: %d\n", bandera);
	return 0;
}