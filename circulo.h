#ifndef CIRCULO_H
#define CIRCULO_H

typedef void* Circulo;

#include "arvoreKd.h"
#include "retangulo.h"
#include "svg.h"
#include "arvoreBinaria.h"
/*
    Este modulo contem toda a implementacao referente ao TAD circulo 
*/

//Cria um circulo 
Circulo criarCirculo(char* corBorda, char* corCentro, char* id, double x, double y, double r);
//Libera a memoria de um circulo
void freeCirculo(Circulo Circ);
//Define o x de um circulo
Circulo setXC(Circulo Circ, double x);
//Define o y de um circulo
Circulo setYC(Circulo Circ, double y);
//Define o raio de um circulo
Circulo setRC(Circulo Circ, double r);
//Define a radiacao de um circulo
Circulo setRadiacaoC(Circulo Circ, double radiacao);
//Recupera o id de um circulo
char* getIdC(Circulo Circ);
//Recupera o x de um circulo
double getXC(Circulo Circ);
//Recupera o y de um circulo
double getYC(Circulo Circ);
//Recupera o r de um circulo
double getRC(Circulo Circ);
//Recupera a cor da borda de um circulo
char* getBordaC(Circulo Circ);
//Recupera a radiacao de um circulo
double getRadiacao(Circulo Circ);
//Define a cor de preenchimento de um circulo
Circulo setPreenchimentoC(Circulo Circ, char* corP);
//Define a cor da borda de um circulo
Circulo setBordaC(Circulo Circ, char* corB);
//Recupera a cor de preenchimento de um circulo
char* getPreenchimentoC(Circulo Circ);
//Retorna 1 para circulo animado e 0 para nao animado
int getAnimacao(Circulo Circ);
//Retorna 1 para circulo movido e 0 para circulo nao movido
int getMovido(Circulo Circ);
//Define se um circulo foi movido
Circulo setMovido(Circulo Circ, int valor);
//Retorna true se o circulo2 esta dentro do circulo1
int circInterior(Circulo circulo1, Circulo circulo2);
//Move um circulo para determinada posicao e guarda os dados de seu movimento em listas auxiliares
Circulo moverCirculo(Retangulo abrigo,ArvoreKd circulos,Lista circulosCinzas,Lista circulosFinal,SvgFile svg,Circulo pessoa, double totalX, double totalY);
//Testa se o circulo c esta dentro do retangulo ret
int circuloDentroRet(Retangulo ret, Circulo c);
//Aplica a todos os circulos a radiacao gerada pela sua respectiva exposicao a um meteoro
ArvoreKd aplicarRadiacao(ArvoreKd circulos, ArvoreBinaria poligonos, double rad);

#endif