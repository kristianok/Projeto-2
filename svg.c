#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "svg.h"

struct StSvgFile {
   FILE *fsvg;
   char *cp, *cb;
   double wb;
};

struct linha {
   double x1,x2,y1,y2;
};

typedef struct StSvgFile *SvgFileImpl;

SvgFile newSvgFile(char *nomeArq){
   FILE *f = fopen(nomeArq,"w");
   if (f == NULL){
     return NULL;
   }

   SvgFileImpl fsf = (SvgFileImpl) malloc (sizeof(struct StSvgFile));
   fsf->fsvg = f;
   fsf->cp = NULL;
   fsf->cb = NULL;
   fsf->wb = 0.0;

   fprintf(fsf->fsvg,"<svg xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\">\n");
   escreverNomeSvg(fsf);
   return fsf;
}


void insertRectangle(SvgFile f, double x, double y,double w, double h, char *cp, char *cb, double wb){
   SvgFileImpl fsf = (SvgFileImpl) f;
   fprintf(fsf->fsvg,"<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" stroke=\"%s\"  fill=\"%s\" fill-opacity=\"0.5\"  stroke-width=\"%f\"/>\n", x,y,w,h,cb,cp,wb);

}

void insertRectangleTransparent(SvgFile f, double x, double y,double w, double h, char *cp, char *cb, double wb){
   SvgFileImpl fsf = (SvgFileImpl) f;
   fprintf(fsf->fsvg,"<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" fill-opacity=\"0\" stroke=\"%s\"  fill=\"%s\"  stroke-width=\"%f\"/>\n", x,y,w,h,cb,cp,wb);

}

void insertCircle(SvgFile f, double x, double y, double r, char *cp, char *cb, double wb){
   SvgFileImpl fsf = (SvgFileImpl) f;
   fprintf(fsf->fsvg,"<circle cx=\"%f\" cy=\"%f\" r=\"%f\" stroke=\"%s\" stroke-width=\"%f\" fill=\"%s\"/>\n",x,y,r,cb,wb,cp);
}

void insertRectanglePadrao(SvgFile f, double x1, double y1,double x2, double y2){
   SvgFileImpl fsf = (SvgFileImpl) f;
   insertRectangle(f,x1,y1,x2,y2,fsf->cp,fsf->cb,fsf->wb);
}

void closeSvgFile(SvgFile f){
   SvgFileImpl fsf = (SvgFileImpl) f;
   fprintf(fsf->fsvg,"</svg>\n");
   fclose(fsf->fsvg);
   free(fsf);
}

void insertTxt(SvgFile f, double x, double y, double valor){
   SvgFileImpl fsf = (SvgFileImpl) f;
   fprintf(fsf->fsvg,"<text x=\"%f\" y=\"%f\" fill=\"black\" font-size=\"8\"> %.0f </text>\n",x,y,valor);
}

void insertLinhaTracejada(SvgFile f,double x, double y, double x2, double y2){
   SvgFileImpl fsf = (SvgFileImpl) f;
   fprintf(fsf->fsvg,"<line x1=\"%f\" x2=\"%f\" y1=\"%f\" y2=\"%f\" stroke-width=\"1.0\" stroke=\"black\" fill=\"black\" stroke-dasharray=\"4\"/>\n",x,x2,y,y2);
}

void insertLinha(SvgFile f,double x, double y, double x2, double y2){
   SvgFileImpl fsf = (SvgFileImpl) f;
   fprintf(fsf->fsvg,"<line x1=\"%f\" x2=\"%f\" y1=\"%f\" y2=\"%f\" stroke-width=\"1.0\" stroke=\"black\" fill=\"black\"/>\n",x,x2,y,y2);
}

void insertPalavras(SvgFile f, double x, double y, char* frase, double tamanhoFonte){
   SvgFileImpl fsf = (SvgFileImpl) f;
   fprintf(fsf->fsvg,"<text x=\"%f\" y=\"%f\" fill=\"black\" font-size=\"%f\"> \"%s\" </text>\n",x,y,tamanhoFonte,frase);
}

char* nomeSvgQry(char* nomeArqGeo, char* nomeArqQry, char* pathBSD){
   char* nomeArqGeoSemSuffix = removeSuffix(nomeArqGeo);
   char* nomeArqQrySemSuffix = removeSuffix(nomeArqQry);
   char* nomeArqGeoComTraco = addSuffix(nomeArqGeoSemSuffix,"-");
   char* nomeArqGeoQryJunto = addSuffix(nomeArqGeoComTraco,nomeArqQrySemSuffix);
   char* svgNomeSemPath = addSuffix(nomeArqGeoQryJunto,".svg");
   char* svgNome = concatPathFile(pathBSD,svgNomeSemPath);
   free(nomeArqGeoSemSuffix);
	free(nomeArqQrySemSuffix);
	free(nomeArqGeoComTraco);
	free(nomeArqGeoQryJunto);
	free(svgNomeSemPath);
   return svgNome;
}

char* nomeSvgGeo(char* nomeArqGeo, char* pathBSD){
   char* arqGeoSemSuffix = removeSuffix(nomeArqGeo);
   char* svgNomeSemPath = addSuffix(arqGeoSemSuffix,".svg");
   char* svgNome = concatPathFile(pathBSD,svgNomeSemPath);
   free(arqGeoSemSuffix);
   free(svgNomeSemPath);
   return svgNome;
}

void inserirFormas(SvgFile svg, ArvoreKd no, int tipo){
   if(no != NULL){
      inserirFormas(svg,getNoDireitaKd(no),tipo);
      inserirFormas(svg,getNoEsquerdaKd(no),tipo);
      void* forma = getItemKd(no);
      if(tipo){
         insertRectangle(svg,getX(forma),getY(forma),getW(forma),getH(forma),getPreenchimento(forma),getBorda(forma),1.0);
      }
      else if(getAnimacao(forma)==0){
         insertCircle(svg,getXC(forma),getYC(forma),getRC(forma),getPreenchimentoC(forma),getBordaC(forma),1.0);
      }
	}
}

void inserirPessoasAbrigadas(SvgFile svg, FILE* txt, ArvoreKd retangulos, ArvoreKd circulos){
   if(retangulos != NULL && circulos != NULL){
		Retangulo ret = getItemKd(retangulos);
      int qtdDentro = pessoasFg(txt,retangulos,circulos,0);
      insertTxt(svg,getX(ret)+getW(ret),getY(ret)-5,qtdDentro);
		inserirPessoasAbrigadas(svg,txt,getNoDireitaKd(retangulos),circulos);
		inserirPessoasAbrigadas(svg,txt,getNoEsquerdaKd(retangulos),circulos);
	}
}

void inserirFormasAnimadas(SvgFile svg,Lista circulosCinzas,Lista circulosFinal){
   int i = 1;
   SvgFileImpl fsf = (SvgFileImpl) svg;
   Posic circC = getFirst(circulosCinzas);
   Posic circF = getFirst(circulosFinal);
   while(circC != NULL && circF != NULL){
      Circulo circCinza = getItem(circC);
      Circulo circFinal = getItem(circF);
      insertCircle(svg,getXC(circCinza),getYC(circCinza),getRC(circCinza),"lightgrey","lightgrey",1.0);
	   insertLinhaTracejada(svg,getXC(circCinza),getYC(circCinza),getXC(circFinal),getYC(circFinal));
      fprintf(fsf->fsvg,"<path d=\"M %lf,%lf L %lf,%lf\" stroke=\"black\" stroke-width=\"1\" stroke-linecap=\"undefined\" stroke-linejoin=\"undefined\" opacity=\"1\" stroke-dasharray=\"4\" fill=\"blue\" id=\"%d\"/>\n",getXC(circCinza),getYC(circCinza),getXC(circFinal),getYC(circFinal),i);
      fprintf(fsf->fsvg,"<circle cx=\"\" cy=\"\" r=\"%lf\" stroke=\"%s\" stroke-width=\"1\" fill=\"%s\">\n",getRC(circCinza),getBordaC(circFinal),getPreenchimentoC(circFinal)); 
      fprintf(fsf->fsvg,"<animateMotion dur=\"6s\" repeatCount=\"indefinite\">\n");
      fprintf(fsf->fsvg,"<mpath xlink:href=\"#%d\"/>\n",i);
      fprintf(fsf->fsvg,"</animateMotion>\n"); 
      fprintf(fsf->fsvg,"</circle>\n"); 
      i++;
      circC = getNext(circulosCinzas,circC);
      circF = getNext(circulosFinal,circF);
   }
}

void inserirSegmentosSvg(SvgFile svg, Lista segmentos){
   Posic seg = getFirst(segmentos);
   while(seg != NULL){
      Ponto segm = getItem(seg);
	   double x1 = getPontoX(getPontoInicial(segm));
      double y1 = getPontoY(getPontoInicial(segm));
	   double x2 = getPontoX(getPontoFinal(segm));
      double y2 = getPontoY(getPontoFinal(segm));
	   insertLinha(svg,x1,y1,x2,y2);
      seg = getNext(segmentos,seg);
   }
}

void inserirPoligonosSvg(Lista todosPoligonos, SvgFile svg){
   Posic polis = getFirst(todosPoligonos);
   while(polis != NULL){
      ArvoreBinaria poligonos = getItem(polis);
      inserirPoligonoSvg(poligonos,svg);
	   polis = getNext(todosPoligonos,polis);
   }
}

void inserirPoligonoSvg(ArvoreBinaria poligonos, SvgFile svg){
   if(poligonos != NULL){
      inserirSegmentosSvg(svg,getItemB(poligonos));
      inserirPoligonoSvg(getNodoEsquerdaB(poligonos),svg);
      inserirPoligonoSvg(getNodoDireitaB(poligonos),svg);
   }
}

void escreverNomeSvg(SvgFile f){
   SvgFileImpl fsf = (SvgFileImpl) f;
   fprintf(fsf->fsvg,"\n\t<!-- Kristiano Pasini de Oliveira -->\n\n");
}

void inserirRetanguloSuavizado(SvgFile f ,double x, double y, double radiacao){
   SvgFileImpl fsf = (SvgFileImpl) f;
   char* cor = definirCores(radiacao);
   fprintf(fsf->fsvg,"<rect x=\"%lf\" y=\"%lf\" width=\"8\" height=\"8\" stroke=\"%s\"  fill=\"%s\" fill-opacity=\"1.0\" stroke-linejoin=\"round\"  stroke-width=\"1\"/> \n", x,y,cor,cor);
}

void inserirMortos(SvgFile f,Lista mortos){
   Posic mor = getFirst(mortos);
   while(mor!=NULL){
      Circulo circ = getItem(mor);
      insertCircle(f,getXC(circ),getYC(circ),getRC(circ),"black","black",1.0);
      inserirCruz(f,getXC(circ),getYC(circ),getRC(circ));
      mor = (getNext(mortos,mor));
   }
}

void inserirCruz(SvgFile f, double x, double y, double r){
   SvgFileImpl fsf = (SvgFileImpl) f;
   fprintf(fsf->fsvg,"<line x1=\"%f\" x2=\"%f\" y1=\"%f\" y2=\"%f\" stroke-width=\"1.0\" stroke=\"white\" fill=\"black\"/>\n",x-r,x+r,y,y);
   fprintf(fsf->fsvg,"<line x1=\"%f\" x2=\"%f\" y1=\"%f\" y2=\"%f\" stroke-width=\"1.0\" stroke=\"white\" fill=\"black\"/>\n",x,x,y-r,y+r);
}

