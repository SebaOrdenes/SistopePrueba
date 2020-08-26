#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../INCLUDE/Etapa2.h"
//Entradas:int, int, unsigned char **, unsigned char ***
//Funcionamiento: funcion principal que transforma la matriz rgb de la imagen a matriz gray
//Salidas:no aplica 
void rgbAgray(int alto,int ancho,unsigned char ** pixeles,unsigned char *** matrizGray){
	int i=0;
	(*matrizGray)=(unsigned char **)malloc(alto*sizeof(unsigned char*));
	for(int z=0;z<alto;z++){
		(*matrizGray)[z]=(unsigned char*)malloc(ancho*sizeof(unsigned char));
	}
	for(int j=0;j<alto;j++){
		for(int k=0;k<ancho;k++){
			(*matrizGray)[j][k]=(((double)pixeles[i][0])*0.3+((double)pixeles[i][1])*0.59+((double)pixeles[i][2])*0.11);
			i++;
		}
	}
}

int main(int argc , char * argv[]){
	for(int i = 1;i<=atoi(argv[1]);i++){
		int dimensiones[2];
		read(STDIN_FILENO,dimensiones,2*sizeof(int));
		unsigned char pixeles[dimensiones[0]][dimensiones[1]];
		read(STDIN_FILENO,pixeles,dimensiones[0]*dimensiones[1]*sizeof(unsigned char));
		printf("%d %d\n", dimensiones[0],dimensiones[1]);
	}
	return 0;
}