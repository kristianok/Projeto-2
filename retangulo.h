#ifndef RETANGULO_H
#define RETANGULO_H


typedef void* Retangulo;

#include "listaDup.h"
#include "arvoreKd.h"
#include "calculos.h"
#include "circulo.h"

/*
    Este modulo contem toda a implementacao referente ao TAD retangulo
    Contem as funcoes responsaveis pela manipulacao dos seus dados e de
    suas caracteristicas proprias 
*/

//Cria um retangulo para ser inserido posteriormente na lista
Retangulo criarRetangulo(char corBorda[], char corCentro[], char id[], double x, double y, double w, double h);

// Retorna os valores referentes ao parametro id do retangulo.
char* getId(Retangulo Ret);

// Retorna os valores referentes ao parametro x do retangulo.
double getX(Retangulo Ret);

// Retorna os valores referentes ao parametro y do retangulo.
double getY(Retangulo Ret);

// Retorna os valores referentes ao parametro w do retangulo.
double getW(Retangulo Ret);

// Retorna os valores referentes ao parametro h do retangulo.
double getH(Retangulo Ret);

// Retorna os valores referentes ao parametro cor de preenchimento do retangulo.
char* getPreenchimento(Retangulo Ret);

// Retorna os valores referentes ao parametro cor da borda do retangulo.
char* getBorda(Retangulo Ret);

// Define os valores referentes ao parametro cor da borda do retangulo.
Retangulo setBorda(Retangulo Ret, char* corB);

//Define os valores referentes ao parametro cor de preenchimento do retangulo.
Retangulo setPreenchimento(Retangulo Ret, char* corP);

//Desaloca um a memoria utilizada para um retangulo
void freeRetangulo(Retangulo Ret);

//Checa se o ret2 esta dentro do ret1
int checarInterior(Retangulo Ret1, Retangulo Ret2);

//Checa se o ponto esta dentro de ret1
int checarPontoInterno(int x1, int y1, Retangulo ret1);

//Retorna o centro de massa de um retangulo
double* centroRet(Retangulo ret);

#endif
