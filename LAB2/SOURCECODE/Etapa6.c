#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <jpeglib.h>
#include "../INCLUDE/Etapa6.h"
//ENTRADA:int, int, int, unsigned char
//FUNCIONAMIENTO: funcion que escribe una nueva imagen para la salida del programa  
//SALIDA:no aplica.
void escribirImagen(int alto,int ancho,int numeroImagen,unsigned char ** matrizGrayBinarizada)
{
    struct jpeg_compress_struct cinfo;
    struct jpeg_error_mgr jerr;
    char nombre[20];
    unsigned char * matrizGrayBinarizadaAux;
    matrizGrayBinarizadaAux=(unsigned char *)malloc(alto*ancho*sizeof(unsigned char));
    sprintf(nombre,"salida_%i.jpg",numeroImagen);
    int contador=0;
    for(int i=0;i<alto;i++){
        for(int j=0;j<ancho;j++){
            matrizGrayBinarizadaAux[contador]=matrizGrayBinarizada[i][j];
            contador++;
        }
    }
  
/* este es un puntero a una fila de datos de imagen */
    JSAMPROW row_pointer[1];
    FILE *outfile = fopen( nombre, "wb" );
   
    if ( !outfile )
    {
        printf("Error opening output jpeg file %s\n!", nombre);
        exit(EXIT_FAILURE);
    }
    cinfo.err = jpeg_std_error( &jerr );
    jpeg_create_compress(&cinfo);
    jpeg_stdio_dest(&cinfo, outfile);

  
/* Configuración de los parámetros del archivo de salida aquí */
    cinfo.image_width = ancho;
    cinfo.image_height = alto;
    cinfo.input_components = 1;
    cinfo.in_color_space = JCS_GRAYSCALE; //img->color_space;
    /* parámetros de compresión predeterminados, no debemos preocuparnos por esto */
    jpeg_set_defaults( &cinfo );
   
    jpeg_start_compress( &cinfo, TRUE );
    /* como leer un archivo, esta vez escriba una fila a la vez */
    while( cinfo.next_scanline < cinfo.image_height )
    {
        row_pointer[0]= &matrizGrayBinarizadaAux[ cinfo.next_scanline * cinfo.image_width*cinfo.input_components];
        jpeg_write_scanlines( &cinfo, row_pointer, 1 );
    }
    /* similar a leer el archivo, limpiar después de que hayamos terminado de comprimir */
    jpeg_finish_compress( &cinfo );
    jpeg_destroy_compress( &cinfo );
    fclose( outfile );
   
    
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

int main(int argc,char* argv[]){
    unsigned char ** matrizGrayConvolucionadayBinarizada;
    for(int i=1;i<=atoi(argv[1]);i++){
        int dimensiones4[3];
        read(STDIN_FILENO,dimensiones4,3*sizeof(int));
        fflush(stdin);
        matrizGrayConvolucionadayBinarizada=(unsigned char**)malloc(dimensiones4[0]*sizeof(unsigned char *));
        for(int j=0;j<dimensiones4[0];j++){
            matrizGrayConvolucionadayBinarizada[j]=(unsigned char*)malloc(dimensiones4[1]*sizeof(unsigned char));
        }
        unsigned char filaDeLaImagen3[dimensiones4[1]];
        for(int j =0;j<dimensiones4[0];j++){

            read(STDIN_FILENO,filaDeLaImagen3,dimensiones4[1]*sizeof(unsigned char));
            fflush(stdin);
            for(int k=0;k<dimensiones4[1];k++){
                matrizGrayConvolucionadayBinarizada[j][k]=filaDeLaImagen3[k];
               
            }
        }
        for(int j=0;j<dimensiones4[0];j++){
            for(int k=0;k<dimensiones4[1];k++){
                printf("%d ", matrizGrayConvolucionadayBinarizada[j][k]);
            }
            printf("\n");
        }
        //escribirImagen(dimensiones4[0],dimensiones4[1],i,matrizGrayConvolucionadayBinarizada);
    }
}