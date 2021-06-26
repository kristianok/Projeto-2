#include <stdio.h>
#include "calculos.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>
double distanciaQuadradaEntreDoisPontos(double x1,double y1,double x2,double y2){
    double distancia;
    double totalX, totalY;
    totalX = fabs(movimentacaoEmX(x1,x2));
    totalY = fabs(movimentacaoEmY(y1,y2));
    distancia = totalX * totalX + totalY * totalY;
    
    return distancia;
}

double distanciaEntreDoisPontos(double x1,double y1,double x2,double y2){
    double distancia = sqrt(distanciaQuadradaEntreDoisPontos(x1,y1,x2,y2));
    return distancia;
}

double movimentacaoEmX(double x1,double x2){
    double totalX;
    totalX = x2 - x1;
    return totalX;
}

double movimentacaoEmY(double y1, double y2){
    double totalY;
    totalY = y2 - y1;
    return totalY;
}

Ponto calcularInterseccao(Retangulo envolvente,double xb, double yb, double x1, double y1){
    //printf("bomba: %lf %lf ponto: %lf %lf\n",xb,yb,x1,y1);
    double xe,ye,xwb,yhb,x=0,y=0;
    xe = 0;
    ye = 0;
    xwb = getW(envolvente);
    yhb = getH(envolvente);
    double intersecX = 0, intersecY = 0;
    int parede;
    double m = 0; 
    double angVert1 = 0, angVert2 = 0, angVert3 = 0, angVert4 = 0, angPonto = 0;
    if(x1 == xb){
        if(y1 < yb){
            y = ye;
            parede = 1;
        }
        else{
            y = yhb;
            parede = 3;
        }
        x = x1;
    }
    else{
        m = (y1 - yb)/(x1 - xb); 
        angPonto = calcularAngulo(x1,y1,xb,yb);
        angVert1 = calcularAngulo(xwb,ye,xb,yb);
        angVert2 = calcularAngulo(xe,ye,xb,yb);
        angVert3 = calcularAngulo(xe,yhb,xb,yb);
        angVert4 = calcularAngulo(xwb,yhb,xb,yb);
        //printf("%f %f %f %f angPonto: %f\n",angVert1,angVert2,angVert3,angVert4,angPonto);
        if(angPonto >= angVert1  && angPonto <= angVert2){
            y = ye;
            parede = 1;
        }
        else if(angPonto >= angVert2  && angPonto <= angVert3){
            x = xe;
            parede = 2;
        }
        else if(angPonto >= angVert3  && angPonto <= angVert4){
            y = yhb;
            parede = 3;
        }
        else{
            x = xwb;
            parede = 0;
        }
        if(parede % 2 == 1){
            x = (y - y1)/m + x1;
        }
        else{
            y = m*(x - x1) + y1;
        }
    }
    if(x < 0 || y < 0){
        //printf("%f %f %f %f angPonto: %f\n",angVert1,angVert2,angVert3,angVert4,angPonto);
        //printf("ponto: %lf %lf meteoro: %lf %lf vertice %lf %lf \n ",x,y,xb,yb,x1,y1);
    }
    Ponto pon = criarPonto(x,y);
    //printf("%lf, %lf, bateu na parede: %d\n",x,y, parede);
    return pon;
}

double calcularAngulo(double xa, double ya, double xb, double yb){
    double angulo=0;
    double hipotenusa = distanciaEntreDoisPontos(xa,ya,xb,yb);
    double CA = distanciaEntreDoisPontos(xa,yb,xb,yb);
    angulo += acos(CA/hipotenusa);
    if(xa > xb){
        if(ya > yb){
            angulo = (3.14/2) - angulo;
            angulo += (3.14*3)/2;
        }
    }
    else {
        if(ya < yb){
            angulo = 3.14/2 - angulo;
            angulo += 3.14/2;
        }
        else{
            angulo += 3.14;
        }
    }
    return angulo;
}

int pontoDentroPoligono(int nvert, double *vertx, double *verty, double testx, double testy){
    int i, j, c = 0;
    for (i = 0, j = nvert-1; i < nvert; j = i++) {
        if ( ((verty[i]>testy) != (verty[j]>testy)) && (testx < (vertx[j]-vertx[i]) * (testy-verty[i]) / (verty[j]-verty[i]) + vertx[i]) )
            c = !c;
    }
    if(c == 1){
        //printf("ta dentro\n");
    }
    return c;
}

int compararAlfanumerico(const void* a, const void* b){
    char** id1 = (char**) a;
    char** id2 = (char**) b;
    return strcmp(*id1,*id2);
}

int calcularRadiacao(double x, double y, ArvoreBinaria poligonos){
    if(poligonos == NULL){
        return 0;
    }
    Lista pontos = getItemB(poligonos);
    double verticesX[7] = {0,0,0,0,0,0,0}, verticesY[7] = {0,0,0,0,0,0,0};
    Posic pon = getFirst(pontos);
    int i = 0;
    while(pon != NULL){
        verticesX[i] = getPontoX(getItem(pon));
        verticesY[i] = getPontoY(getItem(pon));
        //printf("%lf %lf\n",verticesX[i],verticesY[i]);
        i++;
        pon = getNext(pontos,pon);
    }
    //printf("%d\n",i);
    if(x < getXBinaria(poligonos)){
        return pontoDentroPoligono(i,verticesX,verticesY,x,y) + calcularRadiacao(x,y,getNodoEsquerdaB(poligonos)); 
    }
    else{
        return pontoDentroPoligono(i,verticesX,verticesY,x,y) + calcularRadiacao(x,y,getNodoDireitaB(poligonos));
    }
    //return pontoDentroPoligono(i,verticesX,verticesY,x,y) + calcularRadiacao(x,y,getNodoDireitaB(poligonos)) + calcularRadiacao(x,y,getNodoEsquerdaB(poligonos));
}

char* definirCores(double radiacao){
    if(radiacao < 25){
        return "#00FFFF";
    }
    else if(radiacao < 50){
        return "#00FF00";
    }
    else if(radiacao < 100){
        return "#FF00FF";
    }
    else if(radiacao < 250){
        return "#0000FF";
    }
    else if(radiacao < 500){
        return "#800080";
    }
    else if(radiacao < 1000){
        return "#000080";
    }
    else if(radiacao < 8000){
        return "#FF0000";
    }
    else {
        return "#000000";
    }
}
