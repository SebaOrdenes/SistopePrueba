#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include "leerImagenesRGB.h"
#include <jpeglib.h>


//Entradas:
//Funcionamiento:
//Salidas:
void leerImagenes(int cantidadDeImagenes,int umbralParaBinarizarLaImgene,int umbralParaClasificacion,int bandera, char * nombreMascara) {
  unsigned char r, g, b;
  int ancho, alto,contador;;
  int ** pixeles;
  char nombre[20];
  struct jpeg_decompress_struct cinfo;
  struct jpeg_error_mgr jerr;    
  JSAMPARRAY pJpegBuffer;    
  int row_stride;
  FILE * imagen;
  for(int i=1;i<=cantidadDeImagenes;i++){    
 	contador=0;
  	sprintf(nombre,"imagen_%i.jpg",i);      
  	if ((imagen = fopen(nombre, "rb")) == NULL) {
    	fprintf(stderr, "No se puede abrir la imagen%s\n", nombre);
    	exit(EXIT_FAILURE);
  	}
  	cinfo.err = jpeg_std_error(&jerr);
  	jpeg_create_decompress(&cinfo);
  	(void)jpeg_stdio_src(&cinfo, imagen);
  	(void)jpeg_read_header(&cinfo, TRUE);
  	(void)jpeg_start_decompress(&cinfo);
  	ancho = cinfo.output_width;
  	alto = cinfo.output_height;
  	pixeles=(int**)malloc(ancho*alto*sizeof(int*));
  	for(int j=0;j<(ancho*alto);j++){
  		pixeles[j]=(int*)malloc(3*sizeof(int));
  	}
	row_stride = ancho * cinfo.output_components;
  	pJpegBuffer = (*cinfo.mem->alloc_sarray)
    ((j_common_ptr) &cinfo, JPOOL_IMAGE, row_stride, 1);
	while (cinfo.output_scanline < cinfo.output_height) {
    	(void) jpeg_read_scanlines(&cinfo, pJpegBuffer, 1);
    	for (int x = 0; x < ancho; x++) {
      		r = pJpegBuffer[0][cinfo.output_components * x];
      		if (cinfo.output_components > 2) {
        		g = pJpegBuffer[0][cinfo.output_components * x + 1];
       			b = pJpegBuffer[0][cinfo.output_components * x + 2];
      		} else {
        	g = r;
        	b = r;
      		}
      		pixeles[contador][0]=(int)r;
      		pixeles[contador][1]=(int)g;
      		pixeles[contador][2]=(int)b;
    	}
  	}
  	fclose(imagen);
  	for(int j=0; j<(ancho*alto);j++){
  		free(pixeles[j]);
  	}
  	free(pixeles);
  	(void) jpeg_finish_decompress(&cinfo);
  	(void)jpeg_destroy_decompress(&cinfo);
  }


}

