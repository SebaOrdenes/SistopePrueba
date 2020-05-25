#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include "leerImagenesRGB.h"

void leerImagenes(){

	//Declaramos variables
	int fd;
	char * R;
	uint8_t r,g,b;
	 
	//ABRIR ARCHIVO
	//O_RDONLY abre el archivo salida.JPG en modo lectura
	fd = open("Arcoch.jpg",O_RDONLY);
	int contador = 0;
 
	//CONTROLAR SI EXISTE ARCHIVO
	if(fd!=-1)
	{
		//LEER EL ARCHIVO
		//El archivo se lee caracter por caracter
		while(read(fd,&R,sizeof(R)!=0)){
		sscanf(R, "%03hhx%03hhx%02hhx", &r, &g, &b);
		printf("%d %d %d \n",r,g,b);
		contador++;
		}
		
		
//CERRAR ARCHIVO
		close(fd);
		printf("%d\n",contador);
	}
 	else{
		printf("\nEl archivo no existe");
	}
}