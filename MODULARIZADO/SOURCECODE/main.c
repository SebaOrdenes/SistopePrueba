#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../INCLUDE/Etapa0.h"
#include "../INCLUDE/Etapa1.h"
#include "../INCLUDE/Etapa2.h"
#include "../INCLUDE/Etapa3.h"
#include "../INCLUDE/Etapa4.h"
#include "../INCLUDE/Etapa5.h"
#include "../INCLUDE/Etapa6.h"

//ENTRADA:iunsigned char **, int 
//FUNCIONAMIENTO: funcion que permite liberar memoria de la matrices creadas en la función ejecutarPipeline()
//SALIDA:no aplica.
void liberarMemoriaMatriz(unsigned char ** matrizGenerica,int alto){
	for (int i=0;i<alto;i++){
		free(matrizGenerica[i]);
	}
	free(matrizGenerica);
}

//ENTRADA:int, int, int, int , char * , int ** 
//FUNCIONAMIENTO: funcion que ejecuta las etapas del programa
//SALIDA:no aplica.
void ejecutarPipeline(int cantidadDeImagenes,int umbralParaClasificacion,int umbralParaBinarizarLaImagen, char * nombreArchivoMascara,int ** resultadosDeLaClasificacion){
	int alto,ancho;
	unsigned char ** matrizPixeles;
	unsigned char ** matrizGray;
	unsigned char ** matrizGrayConvolucionada;
	unsigned char ** matrizGrayConvolucionadayBinarizada;
	for(int i=1;i<=cantidadDeImagenes;i++){
		leerImagenes(&matrizPixeles,&ancho,&alto,i);//Etapa1
		rgbAgray(alto,ancho,matrizPixeles,&matrizGray);//Etapa2
		applyFilter(matrizGray,&matrizGrayConvolucionada,alto,ancho,nombreArchivoMascara);//Etapa3
		binarizar(matrizGrayConvolucionada,&matrizGrayConvolucionadayBinarizada,alto,ancho,umbralParaBinarizarLaImagen);//Etapa4
		clasificar(matrizGrayConvolucionadayBinarizada,alto,ancho,i,umbralParaClasificacion,resultadosDeLaClasificacion);//Etapa5
		escribirImagen(alto,ancho,i,matrizGrayConvolucionadayBinarizada);//Etapa6
		liberarMemoriaMatriz(matrizPixeles,alto*ancho);
		liberarMemoriaMatriz(matrizGray,alto);	
		liberarMemoriaMatriz(matrizGrayConvolucionada,alto);	
		liberarMemoriaMatriz(matrizGrayConvolucionadayBinarizada,alto);	
	}
}


//ENTRADA:int, int,*, int 
//FUNCIONAMIENTO: imprime los resultados de la clasificación de imagenes por pantalla 
//SALIDA:no aplica.
void imprimirResultados(int * resultadosDeLaClasificacion,int cantidadDeImagenes){
	printf("|    image      |  nearly black  |\n");
	printf("|---------------|----------------|\n");
	for(int z=0;z<cantidadDeImagenes;z++){
  		if (resultadosDeLaClasificacion[z]== -1){
			printf("|   imagen_%d    |       No       |\n",z+1);
		}
		else {
			printf("|   imagen_%d    |       Yes      |\n",z+1);
		}
	}
}

int main(int argc, char * argv[]){
	int cantidadDeImagenes, umbralParaBinarizarLaImagen,umbralParaClasificacion,bandera;
	int *resultadosDeLaClasificacion;
	char nombreArchivoMascara[100];
	bandera=0;
	recibirArgumentos(argc,argv,&cantidadDeImagenes,&umbralParaBinarizarLaImagen,&umbralParaClasificacion,nombreArchivoMascara,&bandera);//Etapa0
	resultadosDeLaClasificacion=(int *)malloc(cantidadDeImagenes*sizeof(int));
	ejecutarPipeline(cantidadDeImagenes,umbralParaClasificacion,umbralParaBinarizarLaImagen,nombreArchivoMascara,&resultadosDeLaClasificacion);
	if(bandera==1){
  		imprimirResultados(resultadosDeLaClasificacion,cantidadDeImagenes);
	}
	free(resultadosDeLaClasificacion);
	return 0;
}
