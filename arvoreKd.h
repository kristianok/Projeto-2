#ifndef ARVOREKD_H
#define ARVOREKD_H

typedef void* Item;
typedef void* ArvoreKd;
typedef void* Forma;
typedef void* PontoKd;

#include "retangulo.h"
#include "circulo.h"
#include "listaDup.h"

/*
    Este modulo contem toda a implementacao do TAD Arvore KD
*/

//Cria um no para ser inserido na arvore
ArvoreKd criarNodo(Item item, double x, double y);
/*Insere um novo elemento na arvore Kd, no qual arvore e a raiz,
novo e o no a ser inserido e altura deve receber sempre 0 como
valor visto que e utilizada para a recursao e organizacao estrutural
de uma Arvore K-D
*/
ArvoreKd insertArvoreKd(ArvoreKd arvore, ArvoreKd novo, int altura);
//Remover um elemento de uma arvore KD, repeitando suas propriedades
ArvoreKd removeArvoreKd(ArvoreKd inicio, ArvoreKd nodo, int profundidade, int tipo);
/*Retorna um dos valores das coordenadas x ou y de uma arvore KD. Aceita os valores 
0 e 1 por nos tratarmos de uma arvore 2D*/
double getPontoKd(ArvoreKd arvore, int ponto);
//Retorna os pontos de uma arvore KD
PontoKd getPontosKd(ArvoreKd arvore);
//Retorna o item armazenado em um no de uma arvore KD
Item getItemKd(ArvoreKd arvore);
//Insere um elemento em uma arvore KD
ArvoreKd insertArvoreKd(ArvoreKd arvore, ArvoreKd novo, int altura);
//Compara dois nodos de uma arvore KD
int compararNodo(ArvoreKd nodo1, ArvoreKd nodo2);
//Copia o conteudo de um nodo para outro da arvore KD
void copiarNodoKd(ArvoreKd nodo1, ArvoreKd nodo2);
//Retorna o nodo com menor valor das coordenadas x ou y de um no de acordo com a dimensao analisada
ArvoreKd menorValor(ArvoreKd nodo1, ArvoreKd nodo2, ArvoreKd nodo3, int Dimensao);
//Retorna o no com o menor valor de x ou y dependendo da dimensao analisada
ArvoreKd encontraMinimo(ArvoreKd inicio, int dimensaoInicial, int profundidade);
//Libera a memoria utilizada pela arvore KD e seus elementos de uma arvore KD
ArvoreKd liberaArvoreKd(ArvoreKd inicio, int tipo);
//Retorna o no esquerdo de uma arvore
ArvoreKd getNoDireitaKd(ArvoreKd arvore);
//Retorna o no direito de uma arvore
ArvoreKd getNoEsquerdaKd(ArvoreKd arvore);
/*Busca um retangulo em uma arvore KD por meio de seu ID. Funcao exclusiva para retangulos.
Nao deve ser utilizada para outros tipos de dados tambem guardados em arvores KD*/
void buscarRetanguloPeloId(ArvoreKd arvore, Retangulo *ret, char* id);
//Imprime todos os valores x e y de uma arvore KD 
void imprimirArvore(ArvoreKd n);
//Busca um no na arvoreKd pelo seu ponto, descendo apenas em subarvore promissoras
ArvoreKd buscarNo(ArvoreKd arvore, PontoKd pont, int altura);
//Busca um nodo na arvore KD pelo seu item
ArvoreKd buscarNoPeloItem(ArvoreKd arvore, ArvoreKd noAnterior, Item item);
//Retorna qual ponto entre dois eh mais proximo do ponto analisado
ArvoreKd maisProximo(ArvoreKd n1, ArvoreKd n2, PontoKd pontos);
/*Busca o ponto x y guardado na arvore mais proximo a determinado ponto passado no parametros
pontos */
ArvoreKd buscarVizinhoMaisProximo(PontoKd pontos, ArvoreKd arvore, int altura);
/*Define os valores x e y de uma arvore KD (Usar com cautela, visto que as propriedades
especiais da arvore serao perdidas)*/
void setPontos(ArvoreKd arvore, double x, double y);
//Libera um ponto de uma arvore KD
void freePontos(PontoKd ponto);
//Cria um ponto para ser inserido em uma arvore KD
PontoKd criarPontos(double x, double y);

#endif