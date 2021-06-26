#include "arvoreBinaria.h"
#include "visibilidade.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct nodoArvore{
    Item item;
    double x;
	struct nodoArvore *esquerda, *direita;
};

typedef struct nodoArvore *noArvore;

double getXBinaria(ArvoreBinaria arvore){
    noArvore no = (noArvore) arvore;
    return no->x;
}

void imprimirArvoreB(ArvoreBinaria n){
    noArvore no = (noArvore) n;
    if(n!=NULL){
        imprimirArvoreB(no->esquerda);
        imprimirArvoreB(no->direita);
    }
    printf("%lf",no->x);
}

ArvoreBinaria liberaArvoreBinaria(ArvoreBinaria arvore, int tipo){
    noArvore n = (noArvore) arvore;
    if(n == NULL){
        return NULL;
    }
    if(n->direita != NULL){
        liberaArvoreBinaria(n->direita,tipo);
    }
    if(n->esquerda != NULL){
        liberaArvoreBinaria(n->esquerda,tipo);
    }
    if(tipo == 1){
        if(n->item != NULL)
        freeRetangulo(n->item);
    }
    else if(tipo == 0){
        if(n->item != NULL)
        freeCirculo(n->item);
    }
    else{
        if(n->item != NULL)
        removeAll(n->item,2);
    }
    free(n);
    return NULL;
}

ArvoreBinaria criarNodoB(Item item, double x){
    noArvore nodo = (noArvore) malloc(sizeof(struct nodoArvore));
    nodo->direita=NULL;
    nodo->esquerda=NULL;
    nodo->item=item;
    nodo->x=x;
    return nodo;
}

Item getItemB(ArvoreBinaria arvore){
    noArvore no = (noArvore) arvore;
    return no->item;
}

ArvoreBinaria insertArvoreB(ArvoreBinaria arvore, ArvoreBinaria novo){
    noArvore no = (noArvore) arvore;
    noArvore novoNo = (noArvore) novo;
    if(arvore==NULL){
        no = novoNo;
        return novoNo;
    }
    if(novoNo->x < no->x) {
        no->esquerda = insertArvoreB(no->esquerda,novoNo);
    }
    else {
        no->direita = insertArvoreB(no->direita,novoNo);
    }
    return no;
}

ArvoreBinaria removeArvoreBinaria(ArvoreBinaria inicio, ArvoreBinaria nodo){
    noArvore raiz = (noArvore) inicio;
    noArvore no = (noArvore) nodo;

    if(raiz == NULL){
        printf("nao encontrou nada");
        return NULL;
    }

    if(no->x < raiz->x){
        raiz->esquerda = removeArvoreBinaria(raiz->esquerda, no);
    }
    else if (no->x > raiz->x){
        raiz->direita = removeArvoreBinaria(raiz->direita, no);
    }
    else { 
        if(raiz->direita != NULL){
            ArvoreBinaria menor = encontraMinimoB(raiz->direita);
            copiarNodo(raiz, menor);
            raiz->direita = removeArvoreBinaria(raiz->direita, menor);
        }
        else{
            if(raiz->esquerda != NULL){
                ArvoreBinaria menor = encontraMinimoB(raiz->esquerda);
                copiarNodo(raiz, menor);
                raiz->direita = removeArvoreBinaria(raiz->esquerda, menor);
                raiz->esquerda = NULL;
            }
            else{
                free(raiz);
                return NULL;
            }
        }
        return raiz;
    }

    return raiz;
}

ArvoreBinaria encontraMinimoB(ArvoreBinaria arvore){
    noArvore no = (noArvore) arvore;
    while (no && no->esquerda != NULL){
        no = no->esquerda;
    }
    return no;
}

void copiarNodo(ArvoreBinaria arvore1, ArvoreBinaria arvore2){
    noArvore no1 = (noArvore) arvore1;
    noArvore no2 = (noArvore) arvore2;
    no1->x = no2->x;
    Item aux;
    aux = no1->item;
    no1->item = no2->item;
    no2->item = aux;
}

ArvoreBinaria getNodoEsquerdaB(ArvoreBinaria arvore){
    noArvore no = (noArvore) arvore;
    return no->esquerda;
}

ArvoreBinaria getNodoDireitaB(ArvoreBinaria arvore){
    noArvore no = (noArvore) arvore;
    return no->direita;
}