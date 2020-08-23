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


int main(){printf("Hola Mundo\n");}