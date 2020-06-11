#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../INCLUDE/Etapa0.h"
#include "../INCLUDE/Etapa1.h"


int main(int argc, char * argv[]){
	int cantidadDeImagenes, umbralParaBinarizarLaImagen,umbralParaClasificacion,bandera;
	char nombreArchivoMascara[100];
	bandera=0;
	recibirArgumentos(argc,argv,&cantidadDeImagenes,&umbralParaBinarizarLaImagen,&umbralParaClasificacion,nombreArchivoMascara,&bandera);
	leerImagenes(cantidadDeImagenes,umbralParaBinarizarLaImagen,umbralParaClasificacion,bandera,nombreArchivoMascara);
	return 0;
}
