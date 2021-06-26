#ifndef LISTADUP_H
#define LISTADUP_H

typedef void *Lista;
typedef void *Posic;
typedef void *Item;

#include "retangulo.h"
#include "arvoreKd.h"

/*
    Este modulo contem toda a implementacao referente ao TAD lista 
    duplamente encadeada dinamica
*/

//Cria uma lista duplamente encadeada dinamica
Lista createLista();

//Insere um elemento na lista
Lista insert(Lista lista, Item item);

//Retorna o item da posicao da lista
Item getItem(Posic p);

//Retorna a posicao do primeiro nodo da lista
Posic getFirst(Lista lista);

//Retorna o proximo nodo da lista de acordo com o parametro passado
Posic getNext(Lista lista,Posic p);

//Remove um nodo e o desaloca da lista
Lista removeD(Lista lista, Posic p);

//Remove todos os elementos da lista e seus dependentes e a desaloca
void removeAll(Lista lista, int tipo);

/* Funcao especial que so deve ser utilizada para retangulos. Retorna o retangulo cujo id 
é igual ao passado no parametro*/
Item getRetanguloPeloId(Lista lista, char *id);

//Retorna a quantidade de nos visitados da lista
double getNodos(Lista lista);

//Retorna a quantidade de elementos na lista
int length(Lista lista);

//Insere um elemento apos o elemento passado como parametro
Posic insertAfter(Lista lista, Posic p, Item info);

//Insere um elemento antes do elemento passado como parametro
Posic insertBefore(Lista lista, Posic p, Item info);

//Retorna o elemento anterior a o elemento passado como parametro
Posic getPrevious(Lista lista, Posic p);

//Retorna o nodo da lista cujo retangulo esta guardado
Posic getPosicPeloId(Lista lista, char *id);

//Desaloca os nodos da lista sem desalocar seu item
void removeNodos(Lista lista);

//Insere uma lista em uma arvore KD
void inserirListaNaArvore(Lista lista, ArvoreKd arvore);

//Remove uma lista de no de arvore de uma arvore qualquer
ArvoreKd removerNoArvores(Lista lista, ArvoreKd arvore);

#endif
