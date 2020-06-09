#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
//Entradas:
//Funcionamiento:
//Salidas:
int esUnNumero(char * cadenaDeTexto){
	int i=1;
	for(int j=0; j<strlen(cadenaDeTexto);j++){
		if(!isdigit(cadenaDeTexto[j])){
			i=0;
			break;
		}
	}
	return i;
}

//Entradas:
//Funcionamiento:
//Salidas:
void verificarSiEsNumeroEntero( char* numeroAux,int numero,char simbolo){
	if(esUnNumero(numeroAux)==0){
		printf("Se ingreso algo distinto a un número entero.\n");
		fprintf(stderr,"Lo ingresado al lado derecho del simbolo -%c es: %s\n",simbolo,numeroAux);
		exit(EXIT_FAILURE);
	}
	if(numero<0){
		printf("El número ingresado es menor que cero.\n");
		fprintf(stderr,"El numero ingresado al lado derecho del simbolo -%c es: %d\n",simbolo,numero);
		exit(EXIT_FAILURE);
	}
}
//Entradas:
//Funcionamiento:
//Salidas:
void recibirArgumentos(int argc,char* argv[],int * cantidadDeImagenes,int * umbralParaBinarizarLaImagen, int * umbralParaClasificacion, char * nombreArchivoMascara,int * bandera){
	char *numeroAux;
	int opt;
	FILE *archivo;
	if(argc<9){
		printf("Se ingreso un numero incorrecto de argumentos\n");
		fprintf(stderr, "Uso correcto: %s [-c numero entero] [-u numero entero] [-n numero entero] [-m cadena de texto][-b]\n",argv[0]);
		exit(EXIT_FAILURE);
	}
	while((opt = getopt(argc, argv, "bm:n:u:c:")) != -1){
		switch(opt){
			case 'c':
					(*cantidadDeImagenes)= strtol(optarg, &numeroAux,10);
					verificarSiEsNumeroEntero(numeroAux,*cantidadDeImagenes,'c');
					break;
			case 'u':
					(*umbralParaBinarizarLaImagen)= strtol(optarg, &numeroAux,10);
					verificarSiEsNumeroEntero(numeroAux,*umbralParaBinarizarLaImagen,'u');
					break;
			case 'n':
					(*umbralParaClasificacion)= strtol(optarg, &numeroAux,10);
					verificarSiEsNumeroEntero(numeroAux,*umbralParaClasificacion,'n');
					break;
			case 'm':
					
					archivo=fopen(optarg,"r");
					if(archivo==NULL){
						printf("El archivo no existe en el directorio.\n");
						exit(EXIT_FAILURE);
					}
					fclose(archivo);
					strcpy(nombreArchivoMascara,optarg);
					break;
			case 'b':
					(*bandera)=1;
					break;
			default:
		            fprintf(stderr, "Uso correcto: %s [-c numero entero] [-u numero entero] [-n numero entero] [-m cadena de texto][-b]\n",argv[0]);
		            exit(EXIT_FAILURE);
					break;
		}
	}
}
