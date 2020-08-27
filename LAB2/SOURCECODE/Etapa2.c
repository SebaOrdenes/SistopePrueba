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
	unsigned char ** matrizPixeles;
	unsigned char ** matrizGray;
	for(int i = 1;i<=atoi(argv[1]);i++){
		int dimensiones[4];
		read(STDIN_FILENO,dimensiones,4*sizeof(int));
		fflush(stdin);
		matrizPixeles=(unsigned char**)malloc(dimensiones[0]*sizeof(unsigned char *));
		for(int j=0;j<dimensiones[0];j++){
			matrizPixeles[j]=(unsigned char*)malloc(dimensiones[1]*sizeof(unsigned char));
		}
		unsigned char pixeles[3];
		for(int j =0;j<dimensiones[0];j++){
			read(STDIN_FILENO,pixeles,3*sizeof(unsigned char));
			matrizPixeles[j][0]=pixeles[0];
			matrizPixeles[j][1]=pixeles[1];
			matrizPixeles[j][2]=pixeles[2];
			fflush(stdin);
		}
		rgbAgray(dimensiones[3],dimensiones[4],matrizPixeles,&matrizGray);

	}
	return 0;
}