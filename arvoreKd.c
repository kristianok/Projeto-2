#include "arvoreKd.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define dimensao 2

struct nodoArvore{
    Item item;
    struct point *pontoKd;
	struct nodoArvore *esquerda, *direita;
};

struct point{
    double pontos[dimensao];
};

typedef struct point *points;

typedef struct nodoArvore *noArvore;

PontoKd criarPontos(double x, double y){
    points ponto = (points) malloc(sizeof(struct point));
    ponto->pontos[0] = x;
    ponto->pontos[1] = y;
    return ponto;
}

void freePontos(PontoKd ponto){
    if(ponto != NULL){
        free(ponto);
    }
}

double getPontoKd(ArvoreKd arvore, int ponto){
    noArvore no = (noArvore) arvore;
    return no->pontoKd->pontos[ponto];
}

PontoKd getPontosKd(ArvoreKd arvore){
    noArvore no = (noArvore) arvore;
    return no->pontoKd;
}

void setPontos(ArvoreKd arvore, double x, double y){
    noArvore no = (noArvore) arvore;
    no->pontoKd->pontos[0]=x;
    no->pontoKd->pontos[1]=y;
}

ArvoreKd criarNodo(Item item, double x, double y){
    noArvore nodo = (noArvore) malloc(sizeof(struct nodoArvore));
    nodo->direita=NULL;
    nodo->esquerda=NULL;
    nodo->item=item;
    nodo->pontoKd = criarPontos(x,y);
    return nodo;
}

Item getItemKd(ArvoreKd arvore){
    if(arvore == NULL){
        return NULL;
    }
    noArvore no = (noArvore) arvore;
    return no->item;
}

ArvoreKd insertArvoreKd(ArvoreKd arvore, ArvoreKd novo, int altura){
    noArvore nodo = (noArvore) arvore;
    noArvore novoNodo = (noArvore) novo;
	int eixo = altura % 2;
	if (nodo == NULL) {
		nodo = novoNodo;
		return nodo;
    }
	if (novoNodo->pontoKd->pontos[eixo] < nodo->pontoKd->pontos[eixo]){
        nodo->esquerda = insertArvoreKd(nodo->esquerda,novoNodo,altura+1);
    }
	else {
        nodo->direita = insertArvoreKd(nodo->direita,novoNodo,altura+1);
    }
    return nodo;
}

int compararNodo(ArvoreKd nodo1, ArvoreKd nodo2){

    noArvore no1 = (noArvore) nodo1;
    noArvore no2 = (noArvore) nodo2;
    int i;

    for(i = 0; i < dimensao; i++){
        if(no1->pontoKd->pontos[i] != no2->pontoKd->pontos[i]){
            return 0;
        }
    }
    if(no1->pontoKd != no2->pontoKd){
        return 0;
    }
    return 1;
}

void copiarNodoKd(ArvoreKd nodo1, ArvoreKd nodo2){

    noArvore no1 = (noArvore) nodo1;
    noArvore no2 = (noArvore) nodo2;

    for(int i = 0; i < dimensao; i++){
        no1->pontoKd->pontos[i] = no2->pontoKd->pontos[i];
    }
    
    Item aux = no2->item;
    no2->item = no1->item;
    no1->item = aux;
}

ArvoreKd menorValor(ArvoreKd nodo1, ArvoreKd nodo2, ArvoreKd nodo3, int Dimensao){

    noArvore no1 = (noArvore) nodo1;
    noArvore no2 = (noArvore) nodo2;
    noArvore no3 = (noArvore) nodo3;
    noArvore menor = no1;

    if((no2 != NULL) && (no2->pontoKd->pontos[Dimensao] < menor->pontoKd->pontos[Dimensao]))
        menor = no2;
    if((no3 != NULL) && (no3->pontoKd->pontos[Dimensao] < menor->pontoKd->pontos[Dimensao]))
        menor = no3;

    return menor;
}

ArvoreKd encontraMinimo(ArvoreKd inicio, int dimensaoInicial, int profundidade){

    noArvore n = (noArvore) inicio;
    int Dimensao = profundidade % dimensao;

    if(n == NULL)
        return NULL;

    if(Dimensao == dimensaoInicial){

        if(n->esquerda == NULL)
            return n;
        return encontraMinimo(n->esquerda, dimensaoInicial, profundidade + 1);
    }

    return menorValor(n, encontraMinimo(n->esquerda, dimensaoInicial, profundidade + 1), encontraMinimo(n->direita, dimensaoInicial, profundidade + 1), dimensaoInicial);
}

ArvoreKd removeArvoreKd(ArvoreKd inicio, ArvoreKd nodo, int profundidade, int tipo){
    noArvore raiz = (noArvore) inicio;
    noArvore no = (noArvore) nodo;
    int Dimensao = profundidade % dimensao;

    if(raiz == NULL){
        printf("nao encontrou nada");
        return NULL;
    }
    if(compararNodo(raiz, no)){ 
        if(raiz->direita != NULL){
            ArvoreKd menor = encontraMinimo(raiz->direita, Dimensao, profundidade + 1);
            copiarNodoKd(raiz, menor);
            raiz->direita = removeArvoreKd(raiz->direita, menor, profundidade + 1, tipo);
        }
        else{
            if(raiz->esquerda != NULL){
                ArvoreKd menor = encontraMinimo(raiz->esquerda, Dimensao, profundidade + 1);
                copiarNodoKd(raiz, menor);
                raiz->direita = removeArvoreKd(raiz->esquerda, menor, profundidade + 1, tipo);
                raiz->esquerda = NULL;
            }
            else{
                if(tipo == 1){
                    if(raiz->item!= NULL)
                    freeRetangulo(raiz->item);
                }
                else if(tipo == 0){
                    if(raiz->item!= NULL) 
                    freeCirculo(raiz->item); 
                }
                free(raiz->pontoKd);
                free(raiz);
                raiz = NULL;
                return NULL;
            }
        }
        return raiz;
    }

    if(no->pontoKd->pontos[Dimensao] < raiz->pontoKd->pontos[Dimensao])
        raiz->esquerda = removeArvoreKd(raiz->esquerda, no, profundidade + 1, tipo);
    else
        raiz->direita = removeArvoreKd(raiz->direita, no, profundidade + 1, tipo);

    return raiz;
}

ArvoreKd liberaArvoreKd(ArvoreKd inicio, int tipo){//0 retangulo, 1 circulo
    noArvore n = (noArvore) inicio;

    if(n == NULL){
        return NULL;
    }
    if(n->direita != NULL){
        liberaArvoreKd(n->direita,tipo);
    }
    if(n->esquerda != NULL){
        liberaArvoreKd(n->esquerda,tipo);
    }
    if(tipo){
        if(n->item != NULL)
        freeRetangulo(n->item);
    }
    else{
        if(n->item != NULL)
        freeCirculo(n->item);
    }
    free(n->pontoKd);
    free(n);
    return NULL;
}

void imprimirArvore(ArvoreKd n){
    noArvore no = (noArvore) n;
    if(n != NULL){
        if(no->esquerda != NULL)
            printf("esquerda\n");
        imprimirArvore(no->esquerda);

        if(no->direita != NULL)
            printf("direita\n");
        imprimirArvore(no->direita);
        printf("(%lf, %lf)\n", no->pontoKd->pontos[0], no->pontoKd->pontos[1]);
    }
}

ArvoreKd buscarNo(ArvoreKd arvore, PontoKd pont , int altura){
    noArvore no = (noArvore) arvore;
    points pon = (points) pont;
    int Dimensao = altura % dimensao;
    if(no == NULL){
        return NULL;
    }
    if(pon->pontos[0] == no->pontoKd->pontos[0] && pon->pontos[1] == no->pontoKd->pontos[1]){
        return no;
    }
    if(pon->pontos[Dimensao] < no->pontoKd->pontos[Dimensao]){
        return buscarNo(no->esquerda,pont, altura+1);
    }
    else {
        return buscarNo(no->direita,pont, altura+1); 
    }
    return no;
}

ArvoreKd buscarNoPeloItem(ArvoreKd arvore, ArvoreKd noAnterior, Item item){
    noArvore no = (noArvore) arvore;
    noArvore noAnte = (noArvore) noAnterior;
    if(no == NULL || item == NULL|| no->item == item){
        return no;
    }
    if(no->esquerda != NULL){
        no = buscarNoPeloItem(no->esquerda,no,item);
    }
    if(no->item == item){
        return no;
    }
    if(no->direita != NULL){
        no = buscarNoPeloItem(no->direita,no,item);
    }
    if(no->item == item){
        return no;
    }
    return noAnte;
}

void buscarRetanguloPeloId(ArvoreKd arvore, Retangulo *ret, char* id){
      noArvore no = (noArvore) arvore;

    if((no != NULL) && (*ret == NULL)){

        buscarRetanguloPeloId(no->esquerda, ret, id);
        buscarRetanguloPeloId(no->direita, ret, id);

        if(strcmp(getId(no->item),id) == 0){
            *ret = no->item;
            return;
        }
    }
}

ArvoreKd getNoDireitaKd(ArvoreKd arvore){
    if(arvore == NULL){
        return NULL;
    }
    noArvore n = (noArvore) arvore;
    return n->direita;
}

ArvoreKd getNoEsquerdaKd(ArvoreKd arvore){
    noArvore n = (noArvore) arvore;
    if(arvore == NULL){
        return NULL;
    }
    return n->esquerda;
}

ArvoreKd buscarVizinhoMaisProximo(PontoKd pontos, ArvoreKd arvore, int altura){
    if (arvore == NULL){
        return NULL;
    } 
    points pon = (points) pontos;
    noArvore nodo = (noArvore) arvore;
    ArvoreKd proxNo=NULL, outroNo=NULL;
	int eixo = 0;
	eixo = altura % 2;
	if (pon->pontos[eixo] < nodo->pontoKd->pontos[eixo]){
        proxNo = nodo->esquerda;
        outroNo = nodo->direita;
    }
	else {
        proxNo = nodo->direita;
        outroNo = nodo->esquerda;
    }  
    ArvoreKd temp = buscarVizinhoMaisProximo(pontos,proxNo,altura+1);
    noArvore melhor = (noArvore) maisProximo(temp,arvore,pontos);
    double distancia = distanciaQuadradaEntreDoisPontos(pon->pontos[0],pon->pontos[1],melhor->pontoKd->pontos[0],melhor->pontoKd->pontos[1]);
    double distanciaEspaco = pon->pontos[eixo] - nodo->pontoKd->pontos[eixo];

    if(distancia >= distanciaEspaco * distanciaEspaco){
        temp = buscarVizinhoMaisProximo(pontos,outroNo,altura+1);
        melhor = maisProximo(temp,melhor,pontos);
    }
    return melhor;
}

ArvoreKd maisProximo(ArvoreKd n1, ArvoreKd n2, PontoKd pontos){
	if (n1 == NULL) {
        return n2;
    }
	if (n2 == NULL){
        return n1;
    }
    noArvore no1 = (noArvore) n1;
    noArvore no2 = (noArvore) n2;
    points pon = (points) pontos;
	double d1 = distanciaQuadradaEntreDoisPontos(no1->pontoKd->pontos[0],no1->pontoKd->pontos[1],pon->pontos[0],pon->pontos[1]);
	double d2 = distanciaQuadradaEntreDoisPontos(no2->pontoKd->pontos[0],no2->pontoKd->pontos[1],pon->pontos[0],pon->pontos[1]);
	if (d1 < d2){
	    return n1;
     }
	else{
	    return n2;
    }
}
