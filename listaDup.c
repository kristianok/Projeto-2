#include "listaDup.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct StElemLista{
	struct StElemLista *ant, *prox;
	Item it;
};

typedef struct StElemLista ElemLista;

struct StLista{
	ElemLista *prim, *ult;
	double nodos;
};

typedef struct StLista *ListaImpl;

Lista createLista(){
	ListaImpl represInterna = (ListaImpl) malloc(sizeof(struct StLista));
	represInterna->prim = NULL;
	represInterna->ult = NULL;
	represInterna->nodos = 0;
	return represInterna;	
}

int length(Lista lista){
	ListaImpl represInterna = (ListaImpl) lista;
	ElemLista *elemento = represInterna->prim;
	int i = 0;
	while(elemento!=NULL){
		elemento=elemento->prox;
		i++;
		represInterna->nodos++;
	}
	return i;	
}

Lista insert(Lista lista, Item item){
	ListaImpl represInterna = (ListaImpl) lista;
	ElemLista *novoElemento = (ElemLista*) malloc(sizeof(ElemLista));
	novoElemento->it = item;
	novoElemento->prox = NULL;
	novoElemento->ant = represInterna->ult;
	if(represInterna->ult != NULL){
		ElemLista *eleAnterior = represInterna->ult;
		eleAnterior->prox = novoElemento;
	}
	represInterna->ult = novoElemento;
	
	if(represInterna->prim == NULL){
		represInterna->prim = novoElemento;
	}
	represInterna->nodos++;
	return represInterna;
}

Lista removeD(Lista lista, Posic p){
	ListaImpl represInterna = (ListaImpl) lista;
	ElemLista* elemento = (ElemLista*) p;
	ElemLista* anterior = elemento->ant;
	if(p == NULL){
		return NULL;
	}
	if(elemento == represInterna->prim){
		represInterna->prim = elemento->prox;
		if(elemento->prox != NULL){
			elemento->prox->ant = NULL;
		}
	}
	else {
		elemento->ant->prox = elemento->prox;
	}
	if(elemento == represInterna->ult){
		represInterna->ult = anterior;
	}
	else {
		elemento->prox->ant = elemento->ant;
	}
	represInterna->nodos++;
	free(elemento);
	return represInterna;
}

void removeAll(Lista lista, int tipo){
	if(lista == NULL){
		return;
	}
	ListaImpl represInterna = (ListaImpl) lista;
	ElemLista* elemento = represInterna->prim;
	ElemLista* aux;
	while(elemento != NULL){
		aux = elemento->prox;
		elemento->prox = NULL;
		if(tipo == 0){
			freeCirculo(elemento->it);
		}
		else if (tipo == 1){
			freeRetangulo(elemento->it);
		}
		else{
			free(elemento->it);
		}
		elemento->it = NULL;
		free(elemento);
		elemento = aux;
		aux = NULL;
	}
	represInterna->prim = NULL;
	represInterna->ult = NULL;
	free(lista);
}

void removeNodos(Lista lista){
	if(lista == NULL){
		return;
	}
	ListaImpl represInterna = (ListaImpl) lista;
	ElemLista* elemento = represInterna->prim;
	ElemLista* aux;
	while(elemento != NULL){
		aux = elemento->prox;
		elemento->prox = NULL;
		elemento->ant = NULL;
		free(elemento);
		elemento = aux;
		aux = NULL;
	}
	represInterna->prim = NULL;
	represInterna->ult = NULL;
}

void inserirListaNaArvore(Lista lista, ArvoreKd arvore){
	ListaImpl represInterna = (ListaImpl) lista;
    ElemLista* deletado = represInterna->prim;
	ElemLista* aux;
	while(deletado != NULL){
		ArvoreKd novo = criarNodo(deletado->it,getXC(deletado->it),getYC(deletado->it));
		insertArvoreKd(arvore,novo,0);
		aux = deletado;
		deletado = deletado->prox;
		removeD(lista,aux);
	}
	represInterna->prim = NULL;
	represInterna->ult = NULL;
}

Retangulo getRetanguloPeloId(Lista lista, char *id){
    ListaImpl represInterna = (ListaImpl) lista;
	ElemLista* elemento = represInterna->prim;
	Item elem;
    while(elemento != NULL){
		elem = elemento->it;
       	if(strcmp(getId(elem),id)==0){
            return elem;
        }
		elemento = elemento->prox;
		represInterna->nodos++;
    }
    printf("retangulo com esse id nao encontrado");
    return NULL;
}

Posic getPosicPeloId(Lista lista, char *id){
    ListaImpl represInterna = (ListaImpl) lista;
	ElemLista* elemento = represInterna->prim;
	Item elem;
    while(elemento != NULL){
		elem = elemento->it;
       	if(strcmp(getId(elem),id)==0){
            return elemento;
        }
		elemento = elemento->prox;
		represInterna->nodos++;
    }
    printf("retangulo com esse id nao encontrado");
    return NULL;
}

Item getItem(Posic p){
	if(p == NULL){
		return NULL;
	}
	ElemLista *elemento = (ElemLista *) p;
	return elemento->it;
}

Posic insertBefore(Lista lista, Posic p, Item info){
	ListaImpl represInterna = (ListaImpl) lista;
	ElemLista *inserido = (ElemLista*) p;
	ElemLista *elemento = represInterna->prim;
	ElemLista *anterior;
	
	while(elemento != NULL){
		if(elemento->prox == (ElemLista*) p){
			inserido = (ElemLista*) malloc(sizeof(ElemLista));
			inserido->it = info;
			anterior = elemento->ant;
			anterior->prox = inserido;
			inserido->prox = elemento;
			inserido->ant = anterior;
			elemento->ant = inserido; 
			return inserido;
		}	
		elemento = elemento->prox;
	}
	return NULL;	
}

Posic insertAfter(Lista lista, Posic p, Item info){
	ListaImpl represInterna = (ListaImpl) lista;
	ElemLista *inserido = (ElemLista*) p;
	ElemLista *elemento = represInterna->prim;
	ElemLista *proximo;
	
	while(elemento != NULL){
		if(elemento->prox == (ElemLista*) p){
			inserido = (ElemLista*) malloc(sizeof(ElemLista));
			inserido->it = info;
			proximo = elemento->prox; 
			proximo->ant = inserido;
			inserido->prox = proximo;
			inserido->ant = elemento; 
			elemento->prox = inserido;
			return inserido;
		}	
		elemento = elemento->prox;
	}
	return NULL;	
}

Posic getFirst(Lista lista){
	ListaImpl represInterna = (ListaImpl) lista;
	if(represInterna == NULL)
		return NULL;
	else
		return represInterna->prim;
}

Posic getNext(Lista lista, Posic p){
	ListaImpl represInterna = (ListaImpl) lista;
	ElemLista *elemento = (ElemLista*) p;
	if(p == NULL){
		return NULL;
	}
	represInterna->nodos++;
	return elemento->prox;
}

Posic getLast(Lista lista){
	ListaImpl represInterna = (ListaImpl) lista;
	if(represInterna == NULL)
		return NULL;
	else
		return represInterna->ult;
}

Posic getPrevious(Lista lista, Posic p){
	ListaImpl represInterna = (ListaImpl) lista;
	ElemLista *elemento = represInterna->prim;
	if(p == NULL){
		return NULL;
	}
	while(elemento != NULL){
		if(elemento == (ElemLista*) p){
			return elemento->ant;
		}	
		elemento = elemento->prox;
		represInterna->nodos++;
	}
	return NULL;	
}

double getNodos(Lista lista){
	ListaImpl represInterna = (ListaImpl) lista;
	return represInterna->nodos;
}

ArvoreKd removerNoArvores(Lista lista, ArvoreKd arvore){
	if(lista == NULL){
		return NULL;
	}
	ListaImpl represInterna = (ListaImpl) lista;
	ElemLista *elemento = represInterna->prim;
	while(elemento!=NULL){
		//printf("%p\n",elemento->it);
		arvore = removeArvoreKd(arvore,elemento->it,0,1);
		elemento = elemento->prox;
	}
	return arvore;
}

