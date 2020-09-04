#ifndef MAIN_H
#define MAIN_H
void validar(char num[], int cont,char * nombreMascara);
void leerMascara(char*nombreMascara);
int esUnNumero(char * cadenaDeTexto);
void verificarSiEsNumeroEntero( char* numeroAux,int numero,char simbolo);
void recibirArgumentos(int argc,char* argv[], char *  i,char * j, char * k, char * nombreArchivoMascara,char * bandera);
#endif