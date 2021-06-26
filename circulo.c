#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "circulo.h"
#include <math.h>
#include <time.h>

struct circ {
	char *id, *corPreenchimento, *corBorda;
    double x,y;
	double r;
    double radiacao;
	int animado;
	int movido;
};

typedef struct circ circulo;

void freeCirculo(Circulo Circ){
	circulo* circ = (circulo*) Circ;
	if(circ == NULL){
		return;
	}
	free(circ->id);
	free(circ->corBorda);
	free(circ->corPreenchimento);
	free(circ);
}
Circulo criarCirculo(char* corBorda, char* corCentro, char* id, double x, double y, double r){
	circulo* circ = (circulo*)malloc(sizeof(circulo));
	circ->id = id;
	circ->corBorda = corBorda;
	circ->corPreenchimento = corCentro;
    circ->x = x;
    circ->y = y;
	circ->r = r;
	circ->radiacao = 0.0;
	circ->animado=0;
	circ->movido=0;
	return circ;
}

Circulo setXC(Circulo Circ, double x){
	circulo* circ = (circulo*) Circ;
	circ->x = x;
	
}

Circulo setYC(Circulo Circ, double y){
	circulo* circ= (circulo*) Circ;
	circ->y = y;	
	return circ;
}

Circulo setRC(Circulo Circ, double r){
	circulo* circ= (circulo*) Circ;
	circ->r = r;
	return circ;
}

Circulo setRadiacaoC(Circulo Circ, double radiacao){
	circulo* circ= (circulo*) Circ;
	circ->radiacao = radiacao;	
	return circ;
}

char* getIdC(Circulo Circ){
	circulo* circ= (circulo*) Circ;
	return circ->id;
}

double getXC(Circulo Circ){
	circulo* circ= (circulo*) Circ;
	return circ->x;
}


double getYC(Circulo Circ){
	circulo* circ= (circulo*) Circ;
	return circ->y;
}

double getRC(Circulo Circ){
	circulo* circ= (circulo*) Circ;
	return circ->r;	
}

char* getBordaC(Circulo Circ){
	circulo* circ= (circulo*) Circ;
	return circ->corBorda;
}

char* getPreenchimentoC(Circulo Circ){
	circulo* circ= (circulo*) Circ;
	return circ->corPreenchimento;
}

double getRadiacao(Circulo Circ){
    circulo* circ= (circulo*) Circ;
	return circ->radiacao;
}

int getAnimacao(Circulo Circ){
    circulo* circ= (circulo*) Circ;
	return circ->animado;
}

int getMovido(Circulo Circ){
	circulo* circ= (circulo*) Circ;
	return circ->movido;
}

Circulo setMovido(Circulo Circ, int valor){
	circulo* circ= (circulo*) Circ;
	circ->movido = valor;
	return circ;
}

Circulo setPreenchimentoC(Circulo Circ, char* corP){
	circulo* circ= (circulo*) Circ;
	char* corPre = (char*) malloc(sizeof(char)*strlen(corP)+1);
	strcpy(corPre, corP);
	free(circ->corPreenchimento);
	circ->corPreenchimento=corPre;
	return circ;
}

Circulo setBordaC(Circulo Circ, char* corB){
	circulo* circ= (circulo*) Circ;
	char* corBor = (char*) malloc(sizeof(char)*strlen(corB)+1);
	strcpy(corBor, corB);
	circ->corBorda=corBor;
	return circ;
}

int circInterior(Circulo circulo1, Circulo circulo2){
	circulo* circ1 = (circulo*) circulo1;
	circulo* circ2 = (circulo*) circulo2;
	double distancia = sqrt(((circ1->x - circ2->x) * (circ1->x - circ2->x)) + ((circ1->y - circ2->y) * (circ1->y - circ2->y)));
   	if (distancia + circ2->r < circ1->r){
		return 1;
	}
	return 0;	
}

Circulo moverCirculo(Retangulo abrigo,ArvoreKd circulos, Lista circulosCinzas,Lista circulosFinal,SvgFile svg,Circulo pessoa, double totalX, double totalY){
	circulo* circ = (circulo*) pessoa;
	Circulo posicaoInicial = criarCirculo(NULL,NULL,NULL,circ->x,circ->y,circ->r);
	circulosCinzas = insert(circulosCinzas,posicaoInicial);
    double xMassa = getX(abrigo) + (getW(abrigo) / 2);
    double yMassa = getY(abrigo) + (getH(abrigo) / 2);
	double raio = 0;
	double novoX = xMassa + cos(rand()) * (getW(abrigo)/3);
	double novoY = yMassa + cos(rand()) * (getH(abrigo)/3);
	if(checarPontoInterno(novoX,novoY,abrigo) == 0){
		double novoX = xMassa;
		double novoY = yMassa;
	}
	circ->animado = 1;
	char* id = (char*) malloc(sizeof(char)*51);
	char* corB = (char*) malloc(sizeof(char)*51);
	char* corP = (char*) malloc(sizeof(char)*51);
	strcpy(id,circ->id);
	strcpy(corB,circ->corBorda);
	strcpy(corP,circ->corPreenchimento);
	circulo* pessoaMovida = criarCirculo(corB,corP,id,novoX,novoY,circ->r);
	pessoaMovida->animado=1;
	pessoaMovida->movido=1;
	ArvoreKd nodoMovido = criarNodo(pessoaMovida,novoX,novoY);
    circulos = insertArvoreKd(circulos,nodoMovido,0);
	circulosFinal = insert(circulosFinal,pessoaMovida);	
	return circ;
}

int circuloDentroRet(Retangulo ret, Circulo c){
	circulo* circ = (circulo*) c;
	double xC = circ->x;
	double yC = circ->y;
	double r = circ->r;
	double xl = getX(ret);
	double yb = getY(ret);
	double xr = getX(ret) + getW(ret);
	double yt = getY(ret) + getH(ret);
	if(xC+r > xr || xC-r < xl || yC-r < yb || yC+r > yt){
		return 0;
	}
	return 1;
}

ArvoreKd aplicarRadiacao(ArvoreKd circulos, ArvoreBinaria poligonos, double rad){
	if(circulos != NULL){
		aplicarRadiacao(getNoDireitaKd(circulos),poligonos,rad);	
		aplicarRadiacao(getNoEsquerdaKd(circulos),poligonos,rad);
		int radia = calcularRadiacao(getXC(getItemKd(circulos)),getYC(getItemKd(circulos)),poligonos);
		circulo* circ = (circulo*) getItemKd(circulos);
		circ->radiacao += rad * pow(0.8,radia);
		//printf("%d\n",radia);
		//printf("%lf\n",circ->radiacao);
	}
	return circulos;	
}
