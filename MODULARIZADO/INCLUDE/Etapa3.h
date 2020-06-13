#ifndef ETAPA3_H
#define ETAPA3_H
void validar(char num[], int cont);
int* leerMascara(char*nombreMascara, int* numeros);
void applyFilter(unsigned char ** MatrizGray,unsigned char *** matrizGrayConvolucionada,int alto,int ancho, char * nombreArchivoMacara);
int resultadoMascara(int*numeroMatriz, int*numerosMascara);
int* getNumeros(int posX, int posY,unsigned char** matrizGray,int* lista, int altoMatriz,int anchoMatriz);
#endif