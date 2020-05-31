#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>


//FUNCIONAMIENTO: funcion que valida, segun la posicion del buffer, si es un numero o no.
void validar(char num[], int cont){
    for (int i = cont; i < strlen(num); i++)
    {

        if(!isdigit(num[i]) ) {
            
            printf("NUMERO INVALIDO INGRESADO. ");
            exit(EXIT_FAILURE);
            break;
        }
       
    }
}



//ENTRADA
//FUNCIONAMIENTO: funcion que lee la mascara y retorna un arreglo de 9 posiciones
//SALIDA

int* leerMascara(char*nombreMascara, int*numeros){
    FILE *fp;
    int i= 0;
	fp = fopen (nombreMascara, "r" );        
	if (fp==NULL) {fputs ("File error",stderr); exit (1);}
    char buffer[256];
    
     
    while(!feof(fp)){
        fscanf(fp,"%s\n",buffer);
        printf("%s, ",buffer);

        if(strlen(buffer)==1 && buffer[0]=='-'){  //si es un caracter y es - el programa muere
            exit(EXIT_FAILURE);
        }
        if (buffer[0]== '-')  //validar que si es un numero negativo, corresponda al patron "-numero"
        {
            validar(buffer,1);
        }
    

    validar(buffer,1); //validamos todos los caracteres siguientes

    if(i>=9){    // esto por si nos ingresan un numero o caracter adicional a la matriz de 3x3
          printf("ERROR");
          exit(EXIT_FAILURE);}

    numeros[i]= atoi(buffer);
  i++;

} 
  printf("Numero caracteres son %d",i);
  printf("EL ARREGLO POSICION 0 ES: %d", numeros[0]);
 
fclose ( fp );
 return(numeros);
} 





void applyFilter(unsigned char **MatrizGray){
	printf("%d\n",MatrizGray[0][0]);
}