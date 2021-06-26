#include <stdio.h>
#include <stdlib.h>
#include "visibilidade.h"
#include <math.h>

struct pon{
    double x,y;
};

struct seg {
    struct pon* pontoInicial;
    struct pon* pontoFinal;
    int ativo;
};

struct vert{
    struct pon* ponto;
    struct seg* segmento;
    int tipo;
    int codigo;
    double angulo;
};

typedef struct pon *ponto;
typedef struct seg *segmento;
typedef struct vert *vertice;

Vertice criarVertice(Segmento seg,double x,double y, double angulo){
    vertice ver = (vertice) malloc(sizeof(struct vert));
    ver->ponto = criarPonto(x,y);
    ver->segmento = seg;
    ver->angulo = angulo;
    return ver;
}

void liberarVertices(Lista vertices){
    if(vertices == NULL){
        return;
    }
    Posic ver = getFirst(vertices);
    while(ver != NULL){
        vertice vert = (vertice) getItem(ver);
        freeVertice(vert);
        ver = getNext(vertices,ver);
    }
}

Ponto getPontoInicial(Segmento seg){
    segmento segm = (segmento) seg;
    return segm->pontoInicial;
}

Ponto getPontoFinal(Segmento seg){
    segmento segm = (segmento) seg;
    return segm->pontoFinal;
}

void liberarSegmentos(Lista segmentos){
    if(segmentos == NULL){
        return;
    }
    Posic seg = getFirst(segmentos);
    while(seg != NULL){
        segmento segm = (segmento) getItem(seg);
        freeSegmento(segm);
        seg = getNext(segmentos,seg);
    }
}

Ponto getPontoVert(Vertice vert){
    vertice ver = (vertice) vert;
    return ver->ponto;
}


Ponto criarPonto(double x, double y){
    ponto pont = (ponto) malloc(sizeof(struct pon));
    pont->x = x;
    pont->y = y;
    return pont;
}

double getPontoX(Ponto pon){
    ponto p = (ponto) pon;
    return p->x;
}

double getPontoY(Ponto pon){
    ponto p = (ponto) pon;
    return p->y;
}

void freeSegmento(Segmento segm){
    segmento seg = (segmento) segm;
    free(seg->pontoFinal);
    free(seg->pontoInicial);
    free(seg);
}

void freeVertice(Vertice verti){
    vertice vert = (vertice) verti;
    free(vert->ponto);
    free(verti);
}

void escreverVertices(Lista vertices){
    if(vertices == NULL){
        return;
    }
    printf("\n");
    Posic ver = getFirst(vertices);
    while(ver != NULL){
        vertice vert = (vertice) getItem(ver);
        printf("%lf->",vert->angulo);
        ver = getNext(vertices,ver);
    }
    printf("\n");
}

Segmento criarSeg(double x1, double y1, double x2, double y2, int ativo){
    segmento segm = (segmento) malloc(sizeof(struct seg));
    segm->pontoInicial = criarPonto(x1,y1);
    segm->pontoFinal = criarPonto(x2,y2);
    segm->ativo = 0;
    return segm;
}

Lista extrairVertices(Lista segmentos){
    if(segmentos == NULL){
        return NULL;
    }
    Lista vertices = createLista();
    Posic seg = getFirst(segmentos);
    vertice vert;
    segmento segm;
    while(seg != NULL){
        segm = (segmento) getItem(seg);
        vert = criarVertice(segm,segm->pontoInicial->x,segm->pontoInicial->y, 0);
        insert(vertices,vert);
        vert = criarVertice(segm,segm->pontoFinal->x,segm->pontoFinal->y, 0);
        insert(vertices,vert);
        seg = getNext(segmentos,seg);
    }
    return vertices;
}

Lista estabelecerAngulos(Lista vertices, double xb, double yb){
    if(vertices == NULL){
        return NULL;
    }
    Posic vert = getFirst(vertices);
    vertice vertic;
    while(vert != NULL){
        vertic = (vertice) getItem(vert);
        vertic->angulo = calcularAngulo(vertic->ponto->x,vertic->ponto->y,xb,yb);
        vert = getNext(vertices,vert);
    }
    return vertices;
}
    

Lista ordenaVertices(Lista vertices){
    if(vertices == NULL){
        return NULL;
    }
    void *verts[length(vertices)];
    int i = 0;
    Posic vert = getFirst(vertices);
    while(vert != NULL){
        Vertice verti = getItem(vert);
        verts[i] = verti;
        vert = getNext(vertices,vert);
        i++;
    }
    qsort(verts,i,sizeof(void*),compararPorAngulo);
    removeNodos(vertices);
    i--;
    while(i >= 0){
        vertice ver = (vertice) verts[i];
        insert(vertices,verts[i]);
        i--;
    }
    return vertices;
}

int compararPorAngulo (const void* ver1, const void *ver2) {
    vertice a = *(vertice*) ver1;
    vertice b = *(vertice*) ver2;
	if(a->angulo > b->angulo){
	    return -1;
	} 
	else if(a->angulo < b->angulo){
   		return 1;
	}
	return 0;
}

int interceptaEmY(Segmento seg, double xb, double yb){
    segmento segm = (segmento) seg;
    ponto ponInicial = segm->pontoInicial;
    ponto ponFinal = segm->pontoFinal;
    if(((ponInicial->y < yb && ponFinal->y > yb) || (ponFinal->y < yb && ponInicial->y > yb)) && ponInicial->x >= xb && ponFinal->x >= xb){
        return 1;
    }
    return 0;
}

Lista coletarSegmentos(Lista segmentos,ArvoreKd retangulos, double xb, double yb){
    if(retangulos != NULL){
        coletarSegmentos(segmentos,getNoDireitaKd(retangulos),xb,yb);
        coletarSegmentos(segmentos,getNoEsquerdaKd(retangulos),xb,yb); 
        Retangulo ret = getItemKd(retangulos);
        double x = getX(ret);
        double y = getY(ret);
        double w = getW(ret);
        double h = getH(ret);
        segmento seg;

        seg = criarSeg(x+w,y,x,y,0);
        insereSegmento(segmentos,seg,xb,yb);

        seg = criarSeg(x,y,x,y+h,0);
        insereSegmento(segmentos,seg,xb,yb);

        seg = criarSeg(x,y+h,x+w,y+h,0);
        insereSegmento(segmentos,seg,xb,yb);

        seg = criarSeg(x+w,y+h,x+w,y,0);
        insereSegmento(segmentos,seg,xb,yb);
    }
    return segmentos;
}

Lista inserirBorda(Lista segmentos, Retangulo ret, double xb, double yb){
    double x = getX(ret);
    double y = getY(ret);
    double w = getW(ret);
    double h = getH(ret);
    segmento seg;
    seg = criarSeg(x,y,x+w,y,0);
    insereSegmento(segmentos,seg,xb,yb);

    seg = criarSeg(x,y,x,y+h,0);
    insereSegmento(segmentos,seg,xb,yb);

    seg = criarSeg(x+w,y,x+w,y+h,0);
    insereSegmento(segmentos,seg,xb,yb);

    seg = criarSeg(x,y+h,x+w,y+h,0);
    insereSegmento(segmentos,seg,xb,yb);

    return segmentos;
}

void insereSegmento(Lista segmentos,Segmento seg, double xb, double yb){
    segmento segm = (segmento) seg;
    if(interceptaEmY(segm,xb,yb)){
        //Dar uma olhada aqui
        segmento s1;
        segmento s2;
        //printf("|%lf %lf %lf %lf|\n", segm->pontoInicial->x,segm->pontoInicial->y,segm->pontoFinal->x,segm->pontoFinal->y);
        if(segm->pontoInicial->y > segm->pontoFinal->y){
            s1 = (segmento) criarSeg(segm->pontoInicial->x,yb,segm->pontoInicial->x,segm->pontoInicial->y,0);
            s2 = (segmento) criarSeg(segm->pontoFinal->x,yb,segm->pontoFinal->x,segm->pontoFinal->y,0);
            s1->ativo = 1;
        }
        else{
            s1 = (segmento) criarSeg(segm->pontoInicial->x,yb,segm->pontoInicial->x,segm->pontoInicial->y,0);
            s2 = (segmento) criarSeg(segm->pontoFinal->x,yb,segm->pontoFinal->x,segm->pontoFinal->y,0);
            s2->ativo = 1;
        }
        //printf("%lf %lf\n",calcularAngulo(s1->pontoInicial->x,s1->pontoInicial->y,xb,yb),calcularAngulo(s1->pontoFinal->x,s1->pontoFinal->y,xb,yb));
        //printf("%lf %lf\n",calcularAngulo(s2->pontoInicial->x,s2->pontoInicial->y,xb,yb),calcularAngulo(s2->pontoFinal->x,s2->pontoFinal->y,xb,yb));
        insert(segmentos, s1);
        insert(segmentos, s2);
        freeSegmento(segm);
    }
    else{
        insert(segmentos,segm);
    }
}

ArvoreBinaria buscarPoligonos(Retangulo borda, Lista segmentos, double xb, double yb){
    ArvoreBinaria poligonos = NULL;
    ponto ponto1;
    ponto ponto2;
    Posic seg = getFirst(segmentos);
    segmento segm;
    while (seg!=NULL){
        Lista pontos = createLista();
        segmento segm = getItem(seg); 
        ponto1 = (ponto) calcularPonto(borda,segm->pontoInicial->x,segm->pontoInicial->y,xb,yb);
        ponto2 = (ponto) calcularPonto(borda,segm->pontoFinal->x,segm->pontoFinal->y,xb,yb);
        if(calcularAngulo(ponto1->x,ponto1->y,xb,yb) < calcularAngulo(ponto2->x,ponto2->y,xb,yb)){ 
            pontos = insert(pontos,criarPonto(segm->pontoInicial->x,segm->pontoInicial->y));
            pontos = insert(pontos,ponto1); 
            pontos = inserirPontosExtras(segm,pontos,borda,ponto1,ponto2,xb,yb); 
            pontos = insert(pontos,ponto2);
            pontos = insert(pontos,criarPonto(segm->pontoFinal->x,segm->pontoFinal->y));    
        }
        else{
            pontos = insert(pontos,criarPonto(segm->pontoFinal->x,segm->pontoFinal->y));  
            pontos = insert(pontos,ponto2);
            pontos = inserirPontosExtras(segm,pontos,borda,ponto2,ponto1,xb,yb);
            pontos = insert(pontos,ponto1); 
            pontos = insert(pontos,criarPonto(segm->pontoInicial->x,segm->pontoInicial->y));
        }
        poligonos = insertArvoreB(poligonos,criarNodoB(pontos,menorValorX(pontos)));
        seg = getNext(segmentos,seg);
    }
    return poligonos;
}

Ponto calcularPonto(Retangulo borda,double x, double y, double xb, double yb){
    Ponto pon = calcularInterseccao(borda,xb,yb,x,y);
    return pon;
}

Lista inserirPontosExtras(Segmento segm,Lista pontos, Retangulo borda, Ponto ponto1, Ponto ponto2, double xb, double yb){
    double xe = getX(borda),ye = getY(borda),xwb = getW(borda),yhb = getH(borda);
    ponto pon1 = (ponto) ponto1;
    segmento se = (segmento) segm;
    ponto pon2 = (ponto) ponto2;
    ponto pon;
    segmento seg;
    double x1 = pon1->x, y1 = pon1->y, x2 = pon2->x, y2 = pon2->y;
    double angVert1 = 0, angVert2 = 0, angVert3 = 0, angVert4 = 0, angPonto1 = 0, angPonto2;
    double cantoX = 0, cantoY = 0;
    angPonto1 = calcularAngulo(x1,y1,xb,yb);
    angPonto2 = calcularAngulo(x2,y2,xb,yb);
    angVert1 = calcularAngulo(xwb,ye,xb,yb);
    angVert2 = calcularAngulo(xe,ye,xb,yb);
    angVert3 = calcularAngulo(xe,yhb,xb,yb);
    angVert4 = calcularAngulo(xwb,yhb,xb,yb);
    if(se->ativo == 1){
        if(angPonto1 == 0){
            angPonto1 = 6.28;
        }
        if(angPonto2 == 0){
            angPonto2 = 6.28;
        }
    }
    if(angVert1 > angPonto1 && angVert1 < angPonto2){
        pon = criarPonto(xwb,ye);
        insert(pontos,pon);
    }
    if(angVert2 > angPonto1 && angVert2 < angPonto2){
        pon = criarPonto(xe,ye);
        insert(pontos,pon);
    }
    if(angVert3 > angPonto1 && angVert3 < angPonto2){
        pon = criarPonto(xe,yhb);
        insert(pontos,pon);
    }
    if(angVert4 > angPonto1 && angVert4 < angPonto2){
        pon = criarPonto(xwb,yhb);
        insert(pontos,pon);
    }
    return pontos;
}

Lista freeArvoresPoligonos(Lista listaDeArvores){
    if(listaDeArvores == NULL){
        return NULL;
    }
    Posic polig = getFirst(listaDeArvores);
    while(polig != NULL){
        ArvoreBinaria poli = getItem(polig);
        liberaArvoreBinaria(poli,2);
        polig = getNext(listaDeArvores,polig);
    }
    removeNodos(listaDeArvores);
    free(listaDeArvores);
    return NULL;
}

double menorValorX(Lista pontos){
    if(pontos == NULL){
        return 1;
    }
    Posic po = getFirst(pontos);
    double menorX = 0;
    if(po != NULL){
        menorX = getPontoX(getItem(po));
    }
    while(po!= NULL){  
        ponto pon = getItem(po);
        if(getPontoX(pon) < menorX){
            menorX = getPontoX(pon);
        }
        po = getNext(pontos,po);
    }
    return menorX;
}