#include "retangulo.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

struct retan {
	char *id, *corPreenchimento, *corBorda;
	double x,y,w,h;
};

typedef struct retan retangulo;

void freeRetangulo(Retangulo Ret){
	retangulo* rect = (retangulo*) Ret;
	free(rect->id);
	free(rect->corBorda);
	free(rect->corPreenchimento);
	free(rect);
}
Retangulo criarRetangulo(char* corBorda, char* corCentro, char* id, double x, double y, double w, double h){
	retangulo* rect = (retangulo*)malloc(sizeof(retangulo));
	rect->id = id;
	rect->corBorda = corBorda;
	rect->corPreenchimento = corCentro;
	rect->x = x;
	rect->y = y;
	rect->w = w;
	rect->h = h;	
	return rect;
}

Retangulo setX(Retangulo Ret, double x){
	retangulo* ret = (retangulo*) Ret;
	ret->x = x;
	
}

Retangulo setY(Retangulo Ret, double y){
	retangulo* ret = (retangulo*) Ret;
	ret->y = y;	
	return ret;
}

Retangulo setW(Retangulo Ret, double w){
	retangulo* ret = (retangulo*) Ret;
	ret->w = w;
	return ret;
}

Retangulo setH(Retangulo Ret, double h){
	retangulo* ret = (retangulo*) Ret;
	ret->h = h;	
	return ret;
}

char* getId(Retangulo Ret){
	retangulo* ret = (retangulo*) Ret;
	return ret->id;
}

double getX(Retangulo Ret){
	retangulo* ret = (retangulo*) Ret;
	return ret->x;
}

double getY(Retangulo Ret){
	retangulo* ret = (retangulo*) Ret;
	return ret->y;	
}

double getW(Retangulo Ret){
	retangulo* ret = (retangulo*) Ret;
	return ret->w;
}

double getH(Retangulo Ret){
	retangulo* ret = (retangulo*) Ret;
	return ret->h;	
}

char* getPreenchimento(Retangulo Ret){
	retangulo* ret = (retangulo*) Ret;
	return ret->corPreenchimento;
}

char* getBorda(Retangulo Ret){
	retangulo* ret = (retangulo*) Ret;
	return ret->corBorda;
}

Retangulo setPreenchimento(Retangulo Ret, char* corP){
	retangulo* ret = (retangulo*) Ret;
	char* corPre = (char*) malloc(sizeof(char)*strlen(corP)+1);
	strcpy(corPre, corP);
	ret->corPreenchimento=corPre;
	return ret;
}

Retangulo setBorda(Retangulo Ret, char* corB){
	retangulo* ret = (retangulo*) Ret;
	char* corBor = (char*) malloc(sizeof(char)*strlen(corB)+1);
	strcpy(corBor, corB);
	ret->corBorda=corBor;
	return ret;
}

//Retorna verdadeiro quando o ret2 esta dentro do ret1
int checarInterior(Retangulo Ret1, Retangulo Ret2){
	if(Ret1 == NULL || Ret2 == NULL){
		return 0;
	}
	retangulo* ret1 = (retangulo*) Ret1;
	retangulo* ret2 = (retangulo*) Ret2;
	double x,y,w,h,xl1,xr1,yl1,yr1,xl3,xr3,yl3,yr3;
	x = ret1->x;
    y = ret1->y;
    w = ret1->w;
    h = ret1->h;
    xl3 = x;
    xr3 = x+w;
    yl3 = y+h;
    yr3 = y;
	x = ret2->x;
    y = ret2->y;
    w = ret2->w;
    h = ret2->h;
    xl1 = x;
    xr1 = x+w;
    yl1 = y+h;
    yr1 = y;  
	if(xl1 >= xl3 && xr1<= xr3 && yr1 >= yr3 && yl1 <= yl3){
		return 1;
	}
	return 0;
}

//Retorna verdadeiro quando o ponto x1,y1 e interior ao ret
int checarPontoInterno(int x1, int y1, Retangulo ret1){
	if(ret1 == NULL){
		return 0;
	}
	retangulo *ret = (retangulo*) ret1;
	double x,y,w,h;
	x = ret->x;
    y = ret->y;
    w = ret->w;
    h = ret->h;
	if(x1 < x + w && x1 > x && y1 > y && y1 < y+h){
		return 1;
	}
	return 0;
}
double* centroRet(Retangulo ret){
	if(ret == NULL){
		return NULL;
	}
	retangulo *retan = (retangulo*) ret;
    double* centroRet = (double*) malloc(sizeof(double)*2);
    centroRet[0] = retan->x + (retan->w/2);
    centroRet[1] = retan->y + (retan->h/2);
	return centroRet;
}




