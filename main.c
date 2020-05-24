#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "recibirArgumentos.h"
#include "leerImagenesRGB.h"

int main(int argc, char * argv[]){
	int cantidadDeImagenes, umbralParaBinarizarLaImagen,umbralParaClasificacion,bandera;
	char nombreArchivoMascara[100];
	recibirArgumentos(argc,argv,&cantidadDeImagenes,&umbralParaBinarizarLaImagen,&umbralParaClasificacion,nombreArchivoMascara,&bandera);

}