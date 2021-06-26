#ifndef VISIBILIDADE_H
#define VISIBILIDADE_H

typedef void* Vertice;
typedef void* Segmento;
typedef void* Ponto;

#include "listaDup.h"
#include "calculos.h"
#include "arvoreKd.h"
#include "arvoreBinaria.h"

/*
    Este modulo contem toda a implementacao referente a criacao e manipulacao
    de uma arvore binaria de poligonos a fim de se calcular a ateanuacao e a exposicao
    a radiacao sofridas pela pessoa
*/

//Cria um ponto contendo coordenadas x e y
Ponto criarPonto(double x, double y);
//Retorna a coordenada x de um ponto
double getPontoX(Ponto pon);
//Retorna a coordenada y de um ponto
double getPontoY(Ponto pon);
//Cria um segmento com inicio em x1 y1 e fim em x2 y2
Segmento criarSeg(double x1, double y1, double x2, double y2, int ativo);
//Coleta de uma arvorekd de retangulos todos os segmentos formados
Lista coletarSegmentos(Lista segmentos,ArvoreKd retangulos, double xb, double yb);
//Retorna 1 se o segmento tem interceptacao em y com a bomba e quando aquele esta a direita da bomba
int interceptaEmY(Segmento seg, double xb, double yb);
//Insere um segmento em uma lista de segmentos
void insereSegmento(Lista segmentos,Segmento seg, double xb, double yb);
//Libera a memoria utilizada por uma lista de segmentos
void liberarSegmentos(Lista segmentos);
//Libera a memoria usada por um segmento
void freeSegmento(Segmento segm);
//Retorna o ponto final de um segmento
Ponto getPontoFinal(Segmento seg);
//Retorna o ponto inicial de um segmento
Ponto getPontoInicial(Segmento seg);
//Cria poligonos por meio de uma lista de segmentos e os insere em uma arvore binaria
ArvoreBinaria buscarPoligonos(Retangulo borda,Lista segmentos,double xb, double yb);
/*Calcula o ponto no retangulo envolvente que eh interceptado pela reta que
passa por um ponto xb yb e por um ponto x y*/
Ponto calcularPonto(Retangulo borda,double x, double y, double xb, double yb);
//Insere vertices do retangulo envolvente no poligono quando necessario
Lista inserirPontosExtras(Segmento segm,Lista pontos, Retangulo borda, Ponto ponto1, Ponto ponto2, double xb, double yb);
//Libera a memoria usada por uma lista de arvores de poligonos
Lista freeArvoresPoligonos(Lista listaDeArvores);
/*Retorna o menor valor de x de um vertice do poligono para ser usado como
chave de ordenacao da arvore binaria, a fim de se descer apenas em arvores
promissoras*/
double menorValorX(Lista pontos);


/* As funcoes abaixo seriam utilizadas para o algoritmo da regiao de visibilidade
porem nao foram utilizadas devido a regiao ser determinada de outra forma
por meio do calculo da sombra como poligonos 
*/

//Cria uma struct do tipo vertice 
Vertice criarVertice(Segmento seg,double x,double y, double angulo);
//Extrai os vertices de uma lista segmentos
Lista extrairVertices(Lista segmentos);
//Estabelece o angulo que cada vertice faz em relacao ao ponto de impacto do meteoro 
Lista estabelecerAngulos(Lista vertices, double xb, double yb);
//Ordena os vertices de acordo com o angulo
Lista ordenaVertices(Lista vertices);
//Escreve os vertices na tela (usado para testes)
void escreverVertices(Lista vertices);
//Insere os segmentos do retangulo envolvente na lista de segmentos
Lista inserirBorda(Lista segmentos, Retangulo ret, double xb, double yb);
//Retorna o ponto de um vertice
Ponto getPontoVert(Vertice vert);
//Compara valores double e os ordena
int compararPorAngulo (const void* ver1, const void *ver2);
//Libera a memoria utilizada por uma lista de vertices
void liberarVertices(Lista segmentos);
//Libera a memoria usada por um vertice
void freeVertice(Vertice verti);

#endif