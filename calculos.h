#ifndef CALCULOS_H
#define CALCULOS_H
#include "arvoreKd.h"
#include "visibilidade.h"
#include "arvoreBinaria.h"
#include "circulo.h"

/*
    Este modulo contem a implementacao de funcoes responsaveis por calculos
    matematicos menos triviais
*/

//Calcula a distancia entre dois pontos 
double distanciaEntreDoisPontos(double x1,double y1,double x2,double y2);
//Calcula a distancia ao quadrado entre dois pontos
double distanciaQuadradaEntreDoisPontos(double x1,double y1,double x2,double y2);
//Retorna a movimentacao realizada no eixo x (pode ser negativa)
double movimentacaoEmX(double x1,double x2);
//Retorna a movimentacao realizada no eixo y (pode ser negativa)
double movimentacaoEmY(double y1, double y2);
/*Calcula o angulo entre o ponto xb yb e o ponto xa ya. Eh dado sob um sentido anti horario
com inicio no primeiro quadrante (0 radianos). O ponto de origem eh centrado no 
ponto xb yb (xb yb representa a coordenada das bombas) */
double calcularAngulo(double xa, double ya, double xb, double yb);
/* Calcula a interseccao de uma reta que passa pelos pontos x1 y1 e xb yb
com o retangulo envolvente. Respeita o lado ao qual o ponto xb yb 
se encontra em relacao a xa ya (xb yb representa a coordenada dos meteoros)
*/ 
Ponto calcularInterseccao(Retangulo envolvente,double xb, double yb, double x1, double y1);
//Retorna 1 se um ponto esta dentro de um poligo e 0 se esta fora
int pontoDentroPoligono(int nvert, double *vertx, double *verty, double testx, double testy);
/*Calcula a radiacao sofrida por determinado ponto de acordo com a quantidade de poligonos 
aos quais ele eh interno*/
int calcularRadiacao(double x, double y, ArvoreBinaria poligonos);
//Retorna a cor referente a determinada faixa de exposicao a radiacao
char* definirCores(double radiacao);;
//Funcao de comparacao de strings usada no qsort para ordenar ids
int compararAlfanumerico(const void* a, const void* b);

#endif