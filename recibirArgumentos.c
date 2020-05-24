#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

//Entradas:
//Funcionamiento:
//Salidas:
void recibirArgumentos(int argc,char* argv,int * cantidadDeImagenes,int * umbralParaBinarizarLaImagen, int * umbralParaClasificacion, char * nombreArchivoMascara,int * bandera){
	if(argc<9){
		
	}
	while((opt = getopt(argc, argv, "bm:n:u:c:")) != -1){
		switch(opt){
			case 'c':
					break;
			case 'u':
					break;
			case 'n':
					break;
			case 'm':
					break;
			case 'b':
					break;
			default:
					break;
		}
	}
}
