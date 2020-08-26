#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <jpeglib.h>
#include "../INCLUDE/Etapa1.h"

//Entradas:unsigned char ***,int *, int *, int
//Funcionamiento:funcion principal que lee las imagenes ingresadas luego de ejecutar el pipeline y la convierte a matriz rgb.
//Salidas: no aplic
unsigned char ** leerImagenes(int* ancho,int * alto,int i) {
  unsigned char ** pixeles;
  unsigned char r, g, b;
  int contador;
  char nombre[20];
  struct jpeg_decompress_struct cinfo;
  struct jpeg_error_mgr jerr;    
  JSAMPARRAY pJpegBuffer;    
  int row_stride;
  FILE * imagen;
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
  *ancho = cinfo.output_width;
  *alto = cinfo.output_height;
  pixeles=(unsigned char**)malloc((*ancho)*(*alto)*sizeof(unsigned char*));
  for(int j=0;j<((*ancho)*(*alto));j++){
  	pixeles[j]=(unsigned char*)malloc(3*sizeof(unsigned char));
  }
	row_stride = (*ancho) * cinfo.output_components;
    pJpegBuffer = (*cinfo.mem->alloc_sarray)
  ((j_common_ptr) &cinfo, JPOOL_IMAGE, row_stride, 1);
	while (cinfo.output_scanline < cinfo.output_height) {
    	(void) jpeg_read_scanlines(&cinfo, pJpegBuffer, 1);
    	for (int x = 0; x < (*ancho); x++) {
      		r = pJpegBuffer[0][cinfo.output_components * x];
      		if (cinfo.output_components > 2) {
        		g = pJpegBuffer[0][cinfo.output_components * x + 1];
       			b = pJpegBuffer[0][cinfo.output_components * x + 2];
      		} else {
        	g = r;
        	b = r;
      		}
      		pixeles[contador][0]=r;
      		pixeles[contador][1]=g;
      		pixeles[contador][2]=b;
      		contador++;
      		
    	}
    	
  }
  fclose(imagen);
  (void) jpeg_finish_decompress(&cinfo);
  (void)jpeg_destroy_decompress(&cinfo);
  return pixeles;
  
}
//ENTRADA:iunsigned char **, int 
//FUNCIONAMIENTO: funcion que permite liberar memoria de la matrices creadas en la función ejecutarPipeline()
//SALIDA:no aplica.
void liberarMemoriaMatriz(unsigned char ** matrizGenerica,int alto){
  for (int i=0;i<alto;i++){
    free(matrizGenerica[i]);
  }
  free(matrizGenerica);
}

int main(int argc,char * argv[]){
  int alto,ancho;
  unsigned char ** pixelesAux;
  /*int tuberia[2];
  pipe(tuberia);
  pid_t pid = fork();
  if(pid < 0){
    printf("No se pudo crear el hijo\n");
    exit(EXIT_FAILURE);
  }
  else if(pid == 0){
    dup2(tuberia[0],STDIN_FILENO);
    close(tuberia[0]);
    close(tuberia[1]);
    char *args[] = {"Etapa2.out",argv[1],argv[2],argv[3],argv[4],argv[5],NULL};
    execvp("SOURCECODE/Etapa2.out",args);
  }
  else{
      dup2(tuberia[1],STDOUT_FILENO);
      close(tuberia[0]);
      close(tuberia[1]);*/
      int i=0;
      while(i < atoi(argv[1])){
        int imagen[1];
        read(STDIN_FILENO,imagen,1*sizeof(int));
        pixelesAux=leerImagenes(&ancho,&alto,imagen[0]);
        
        int filas = ancho*alto;
        int columnas = 3;
        unsigned char pixeles[filas][columnas];
        printf("%d %d %d %d\n",ancho,alto,filas,pixelesAux[0][0]);
        
        //int dimensiones[2];
        //dimensiones[0] = filas;
        //dimensiones[1] = 3;
        
        for(int j=0;j<filas;j++){
          for(int k=0;k<columnas;k++){ 
            pixeles[j][k]=pixelesAux[j][k];
          }
        }

       
        
        //unsigned char pixelesAux[filas][3];
        //write(STDOUT_FILENO,dimensiones,2*sizeof(int));
        //write(STDOUT_FILENO,pixeles,filas*3*sizeof(unsigned char));
        liberarMemoriaMatriz(pixelesAux,filas);
        i++;
      }
    
  //}
  wait(NULL);
  return 0;
}
