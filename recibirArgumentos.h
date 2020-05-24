#ifndef RECIBIRARGUMENTOS_H
#define RECIBIRARGUMENTOS_H
void recibirArgumentos(int argc,char* argv[],int * cantidadDeImagenes,int * umbralParaBinarizarLaImagen, int * umbralParaClasificacion, char * nombreArchivoMascara,int* bandera);
int esUnNumero(char * cadenaDeTexto);
void verificarSiEsNumeroEntero(char * numeroAux, int  numero,char simbolo);
#endif