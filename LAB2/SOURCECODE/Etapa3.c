#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "../INCLUDE/Etapa3.h"

//ENTRADA: char[], int
//FUNCIONAMIENTO: funcion que valida, segun la posicion del buffer, si es un numero o no.
//SALIDA: no aplica
void validar(char num[], int cont){
    for (int i = cont; i < strlen(num); i++)
    {

        if(!isdigit(num[i]) ) {
            
            printf("El símbolo %c no es valido\n",num[i]);
            exit(EXIT_FAILURE);
            break;
        }
       
    }
}



//ENTRADA:char*, int*
//FUNCIONAMIENTO: funcion que lee la mascara y retorna un arreglo de 9 posiciones
//SALIDA: arreglo de int

int* leerMascara(char*nombreMascara, int*numeros){
    FILE *fp;
    int i= 0;
	fp = fopen (nombreMascara, "r" );        
	if (fp==NULL) {fputs ("File error",stderr); exit (1);}
    char buffer[256];
    
     
    while(!feof(fp)){
        fscanf(fp,"%s\n",buffer);
        if(strlen(buffer)==1 && buffer[0]=='-'){  //si es un caracter y es - el programa muere
            exit(EXIT_FAILURE);
        }
        if (buffer[0]== '-')  //validar que si es un numero negativo, corresponda al patron "-numero"
        {
            validar(buffer,1);
        }
        else{
            validar(buffer,1);
        } //validamos todos los caracteres siguientes

        if(i>=9){    // esto por si nos ingresan un numero o caracter adicional a la matriz de 3x3
          printf("Error. La cantidad de números en el archivo es mayor a 9\n");
          exit(EXIT_FAILURE);
        }

        numeros[i]= atoi(buffer);
        i++;

    } 
    if (i<9){
        printf("Error. La cantidad de números en el archivo es menor a 9\n");
        exit(EXIT_FAILURE);
    }
    fclose ( fp );
    return(numeros);
} 

//ENTRADA:int, int, unsigned char**, int*, int. int
//FUNCIONAMIENTO:funcion que, en base a una posicion x e y dada, retorna los valores de las 8 posiciones colindantes a esa posicion
//SALIDA: puntero a un arreglo de int
int* getNumeros(int posX, int posY,unsigned char** matrizGray,int* lista, int altoMatriz,int anchoMatriz){
    int tempX;
    int tempY;
    tempX= posX -1;
    tempY= posY -1;
    if (tempX<0 || tempY<0 || tempX>=altoMatriz || tempY>=anchoMatriz){lista[0]=0;}
    else
    {lista[0]= matrizGray[tempX][tempY];}

    tempX= posX-1;
    tempY= posY;
    if (tempX<0 || tempY<0 || tempX>=altoMatriz || tempY>=anchoMatriz){lista[1]=0;}
    else
    {lista[1]= matrizGray[tempX][tempY];}
    
    tempX= posX-1;
    tempY=posY+1;
    if (tempX<0 || tempY<0 || tempX>=altoMatriz || tempY>=anchoMatriz){lista[2]=0;}
    else
    {lista[2]= matrizGray[tempX][tempY];}

    tempX= posX;
    tempY=posY-1;
    if (tempX<0 || tempY<0 || tempX>=altoMatriz || tempY>=anchoMatriz){lista[3]=0;}
    else
    {lista[3]= matrizGray[tempX][tempY];}

    tempX= posX;
    tempY=posY;
    if (tempX<0 || tempY<0 || tempX>=altoMatriz || tempY>=anchoMatriz){lista[4]=0;}
    else
    {lista[4]= matrizGray[tempX][tempY];}

    tempX= posX;
    tempY=posY+1;
    if (tempX<0 || tempY<0 || tempX>=altoMatriz || tempY>=anchoMatriz){lista[5]=0;}
    else
    {lista[5]= matrizGray[tempX][tempY];}

    tempX= posX+1;
    tempY=posY-1;
    if (tempX<0 || tempY<0 || tempX>=altoMatriz || tempY>=anchoMatriz){lista[6]=0;}
    else
    {lista[6]= matrizGray[tempX][tempY];}

    tempX= posX+1;
    tempY=posY;
    if (tempX<0 || tempY<0 || tempX>=altoMatriz || tempY>=anchoMatriz){lista[7]=0;}
    else
    {lista[7]= matrizGray[tempX][tempY];}

    tempX= posX+1;
    tempY=posY+1;
    if (tempX<0 || tempY<0 || tempX>=altoMatriz || tempY>=anchoMatriz){lista[8]=0;}
    else
    {lista[8]= matrizGray[tempX][tempY];}


    return(lista);

}

//ENTRADA:int*, int*
//FUNCIONAMIENTO : funcion que calcula el numero a poner en la nueva matriz una vez aplicada la mascara, el cual habra que posicionalo en las mismas
//coordenadas x e y iniciales
//SALIDA: int
int resultadoMascara(int*numeroMatriz, int*numerosMascara){
    int contador=0;
    for (int i = 0; i < 9; i++)
    {
       int tempA= numerosMascara[i];
       int tempB= numeroMatriz[i];
       int tempC= tempA*tempB;
       contador= contador+tempC;
       
    }
    return contador;
    
}



//ENTRADA: unsigned char **, unsigned char ***, int, int
//FUNCIONAMIENTO: funcion principal que aplica el filtro entregado por la máscara, en la matriz
//SALIDA: no aplica

void applyFilter(unsigned char ** MatrizGray,unsigned char *** matrizGrayConvolucionada,int alto,int ancho,char * nombreArchivoMascara){
	int numeros[9];
    int *arreglo= leerMascara(nombreArchivoMascara,numeros);
    (*matrizGrayConvolucionada)=(unsigned char **)malloc(alto*sizeof(unsigned char *));
    for(int i=0;i<alto;i++){
        (*matrizGrayConvolucionada)[i]=(unsigned char *)malloc(ancho*sizeof(unsigned char));
    }
    int lista[9];
    int * numerosMatriz;
    for (int i=0;i<alto;i++){
        for(int j=0;j<ancho;j++){
            numerosMatriz=getNumeros(i,j,MatrizGray,lista,alto,ancho);
            (*matrizGrayConvolucionada)[i][j]=resultadoMascara(numerosMatriz,arreglo);
        }
        
    }
}

int main(int argc,char * argv[]){
    int tuberia[2];
    pipe(tuberia);
    pid_t pid =fork();
    if(pid < 0){
        printf("No se pudo crear el hijo\n");
        exit(EXIT_FAILURE);
    }
    else if(pid == 0){
        dup2(tuberia[0],STDIN_FILENO);
        close(tuberia[0]);
        close(tuberia[1]);
        char *args[] = {"Etapa4.out",argv[1],argv[2],argv[3],argv[4],argv[5],NULL};
        execvp("SOURCECODE/Etapa4.out",args);
    }
    else{
        dup2(tuberia[1],STDOUT_FILENO);
        close(tuberia[0]);
        close(tuberia[1]);
        unsigned char ** matrizGray;
        unsigned char ** matrizGrayConvolucionada;
        for(int i=1;i<=atoi(argv[1]);i++){
            int dimensiones1[2];
            read(STDIN_FILENO,dimensiones1,2*sizeof(int));//leer las dimensiones de la matrizGray de la etapa anterior
            fflush(stdin);
            matrizGray=(unsigned char**)malloc(dimensiones1[0]*sizeof(unsigned char *));
            for(int j=0;j<dimensiones1[0];j++){
                matrizGray[j]=(unsigned char*)malloc(dimensiones1[1]*sizeof(unsigned char));
            }
            unsigned char filaDeLaMatriz[dimensiones1[1]];
            for(int j =0;j<dimensiones1[0];j++){

                read(STDIN_FILENO,filaDeLaMatriz,dimensiones1[1]*sizeof(unsigned char));//leer una fila de la etapa anterior
                fflush(stdin);
                for(int k=0;k<dimensiones1[1];k++){
                    matrizGray[j][k]=filaDeLaMatriz[k];
                    // almacenar una fila de la matrizGray, correspondiente a la etapa anterior
                }
            }
          
            applyFilter(matrizGray,&matrizGrayConvolucionada,dimensiones1[0],dimensiones1[1],argv[5]);
       
            int dimensiones2[2];// dimensiones de la matrizGrayCOnvolucionada
            dimensiones2[0]=dimensiones1[0];// cantidad de filas
            dimensiones2[1]=dimensiones1[1];// cantidad de columnas
            write(STDOUT_FILENO,dimensiones2,2*sizeof(int));
            unsigned char filaDeLaImagen1[dimensiones2[1]];//arreglo para enviar una fila de la matrizGrayConvolucionada.
            for(int j =0;j<dimensiones2[0];j++){
                for(int k=0;k<dimensiones2[1];k++){
                    filaDeLaImagen1[k]=matrizGrayConvolucionada[j][k];
                }
                write(STDOUT_FILENO,filaDeLaImagen1,dimensiones2[1]*sizeof(unsigned char));//escribir la fila.
                fflush(stdout);
            }
        }
    }
    wait(NULL);
    return 0;
}