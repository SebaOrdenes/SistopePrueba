#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void applyFilter(){

FILE *fp;
  printf("OLA SOY EL APLICAR FILTRO");
	fp = fopen ( "mascara.txt", "r" );        
	if (fp==NULL) {fputs ("File error",stderr); exit (1);}

  
fclose ( fp );



}