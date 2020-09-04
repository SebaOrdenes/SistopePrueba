#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include "../INCLUDE/main.h"


//Entradas:Char *
//Funcionamiento:funcion que verifica si el elemento ingresado es un numero entero
//Salidas: int
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

//Entradas:char*, int* , char
//Funcionamiento: funcion que verifica si la cadena de texto corresponde a un numero
//Salidas: no aplica.
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

//ENTRADA: char[], int, char *
//FUNCIONAMIENTO: funcion que valida, segun la posicion del buffer, si es un numero o no.
//SALIDA: no aplica
void validar(char num[], int cont, char * nombreMascara){
    for (int i = cont; i < strlen(num); i++)
    {

        if(!isdigit(num[i]) ) {
            
            printf("Error en el archivo '%s'. El símbolo %c no es valido.\n",nombreMascara,num[i]);
            exit(EXIT_FAILURE);
            break;
        }
       
    }
}

//ENTRADA:char*, int*
//FUNCIONAMIENTO: funcion que lee la mascara y retorna un arreglo de 9 posiciones
//SALIDA: arreglo de int

void leerMascara(char*nombreMascara){
    FILE *fp;
    int i= 0;
	fp = fopen (nombreMascara, "r" );        
    char buffer[256];
    
     
    while(!feof(fp)){
        fscanf(fp,"%s\n",buffer);
        if(strlen(buffer)==1 && buffer[0]=='-'){  //si es un caracter y es - el programa aborta su ejución.
            printf("Error en el archivo '%s'.El simbolo - sin un número no está permitido.\n",nombreMascara);
            exit(EXIT_FAILURE);
        }
        if (buffer[0]== '-')  //validar que si es un numero negativo, corresponda al patron "-numero"
        {
            validar(buffer,1,nombreMascara);
        }
        else{
            validar(buffer,1,nombreMascara);
        } //validamos todos los caracteres siguientes

        if(i>=9){    // esto por si nos ingresan un numero o caracter adicional a la matriz de 3x3
          printf("Error. La cantidad de números en el archivo '%s' es mayor a 9\n",nombreMascara);
          exit(EXIT_FAILURE);
        }
        i++;
    } 
    if (i<9){
        printf("Error. La cantidad de números en el archivo '%s' es menor a 9\n",nombreMascara);
        exit(EXIT_FAILURE);
    }
    fclose ( fp );
} 

//Entradas:int, char*, in*, int*, int*, char*, int*
//Funcionamiento: funcion principal que recibe los argumentos de entrada cuando se invoca el pipeline
//Salidas: no aplica
void recibirArgumentos(int argc,char* argv[], char *  i,char * j, char * k, char * nombreArchivoMascara,char * bandera){
	char *numeroAux;
	int cantidadDeImagenes,umbralParaBinarizarLaImagen,umbralParaClasificacion;
	int opt;
	FILE *archivo;
	char nombre[20];
	FILE * imagen;
	if(argc<9){
		printf("Se ingreso un numero incorrecto de argumentos\n");
		fprintf(stderr, "Uso correcto: %s [-c numero entero] [-u numero entero] [-n numero entero] [-m cadena de texto][-b]\n",argv[0]);
		exit(EXIT_FAILURE);
	}
	while((opt = getopt(argc, argv, "bm:n:u:c:")) != -1){
		switch(opt){
			case 'c':
					cantidadDeImagenes= strtol(optarg, &numeroAux,10);
					verificarSiEsNumeroEntero(numeroAux,cantidadDeImagenes,'c');
					for(int i=1;i<=cantidadDeImagenes;i++){
						sprintf(nombre,"imagen_%i.jpg",i);      
  						if ((imagen = fopen(nombre, "rb")) == NULL) {
    						fprintf(stderr, "Error. La %s no existe, por favor verificar que la cantidad de imagenes sea igual a las que existen en el direcctorio.\n", nombre);
    						exit(EXIT_FAILURE);
  						}
  						fclose(imagen);
					}
					strcpy(i,optarg);
					break;
			case 'u':
					umbralParaBinarizarLaImagen= strtol(optarg, &numeroAux,10);
					verificarSiEsNumeroEntero(numeroAux,umbralParaBinarizarLaImagen,'u');
					if(umbralParaBinarizarLaImagen>255){
						printf("Umbral para binarizar (Rango: [0 a 255]) sobrepasado.\n");
						exit(EXIT_FAILURE);
					}
					strcpy(j,optarg);
					break;
					
			case 'n':
					umbralParaClasificacion= strtol(optarg, &numeroAux,10);
					verificarSiEsNumeroEntero(numeroAux,umbralParaClasificacion,'n');
					if ( umbralParaClasificacion > 100)
					{
						printf("Umbral para clasificar (Rango: [0 a 100]) sobrepasado.\n");
						exit(EXIT_FAILURE);
					}
					strcpy(k,optarg);
					break;
			case 'm':
					
					archivo=fopen(optarg,"r");
					if(archivo==NULL){
						printf("El archivo %s no existe en el directorio.\n", optarg);
						exit(EXIT_FAILURE);
					}
					leerMascara(optarg);
					strcpy(nombreArchivoMascara,optarg);
					break;
			case 'b':
					strcpy(bandera,"1");
					break;
			default:
		            fprintf(stderr, "Uso correcto: %s [-c numero entero] [-u numero entero] [-n numero entero] [-m cadena de texto][-b]\n",argv[0]);
		            exit(EXIT_FAILURE);
					break;
		}
	}
}






int main(int argc, char * argv[]){
	int tuberia[2];
  	pipe(tuberia);
	char cantidadDeImagenes[100], umbralParaBinarizarLaImagen[100],umbralParaClasificacion[100],bandera[100];
	char nombreArchivoMascara[100];
	strcpy(bandera,"0");
	recibirArgumentos(argc,argv,cantidadDeImagenes,umbralParaBinarizarLaImagen,umbralParaClasificacion,nombreArchivoMascara,bandera);//verificar y almacenar los parametros ingresados a través de la terminal.
	pid_t pid = fork();
	if(pid < 0){
		printf("Fallo la creación del hijo\n");
		exit(EXIT_FAILURE);
	}
	else if(pid == 0){
		dup2(tuberia[0],STDIN_FILENO);
    	close(tuberia[0]);
    	close(tuberia[1]);
		char *args[] = {"Etapa1.out",cantidadDeImagenes,umbralParaBinarizarLaImagen,umbralParaClasificacion,bandera,nombreArchivoMascara,NULL};
		execvp("SOURCECODE/Etapa1.out",args);
	}
	else{
		dup2(tuberia[1],STDOUT_FILENO);
    	close(tuberia[0]);
    	close(tuberia[1]);
		int i=1;
		int imagen[1];
		while(i<=atoi(cantidadDeImagenes)){
			imagen[0]=i;
			write(STDOUT_FILENO,imagen,1*sizeof(int));// escrbir el número de la imagen para que sea leído en la siguiente etapa.
			i++;
		}
	}
	wait(NULL);
	return 0;
}
