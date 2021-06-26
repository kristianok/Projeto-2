#include "leituraArquivos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void lerArquivoGeo(char* arqGeo, char* pathBSD, char* nomeArqGeo,char* arqQry, char* nomeArqQry){
	ArvoreKd retangulos=NULL;
	ArvoreKd circulos=NULL;
    Retangulo retangulo=NULL;
    Circulo circulo=NULL;
    char *nomeArqSvg,*arqSvg;
    char x[25]="0",y[25]="0",w[25]="0",h[25]="0",geoP[25],corBorda[30],corCentro[30],SqtdRets[20],*corC,*corB;
    char *id,r[25],corPreenchimentoCirculo[30],corBordaCirculo[30];
	int aux = 0;
    double maiorX = -1, menorX = -1, maiorY = -1, menorY = -1, delta = 0;
    FILE *geo;
    geo = fopen(arqGeo,"r");
    if(geo == NULL){
		printf("Nao foi possivel encontrar o arquivo geo");
		exit(0);
	}
	arqSvg = nomeSvgGeo(nomeArqGeo,pathBSD);
	SvgFile svg = newSvgFile(arqSvg);
	fscanf(geo, "%s", geoP);
	while(1==1){	
		if(feof(geo)){
			break;	
		}
		if(strcmp("nx",geoP)==0){
			fscanf(geo, "%s", SqtdRets);
		}
		else if(strcmp("cc",geoP)==0){
			fscanf(geo, "%s", corBorda);
		}
		else if(strcmp("cp",geoP)==0){
			fscanf(geo, "%s", corCentro);
		}
		else if(strcmp("bc",geoP)==0){
			fscanf(geo, "%s", corBordaCirculo);
		}
		else if(strcmp("pc",geoP)==0){
			fscanf(geo, "%s", corPreenchimentoCirculo);
		}
		else if(strcmp("r",geoP)==0){
			id = (char*) malloc(sizeof(char)*50);
			fscanf(geo, "%s", id);	
			fscanf(geo, "%s", x);
			fscanf(geo, "%s", y);
			fscanf(geo, "%s", w);
			fscanf(geo, "%s", h);
			corB = (char*) malloc(sizeof(char)*31);
			strcpy(corB,corBorda);
			corC = (char*) malloc(sizeof(char)*31);
			strcpy(corC,corCentro);
			retangulo = criarRetangulo(corB,corC,id,atof(x),atof(y),atof(w),atof(h));
			double* centroRetangulo = centroRet(retangulo);
			retangulos = insertArvoreKd(retangulos,criarNodo(retangulo,centroRetangulo[0],centroRetangulo[1]),0);
			insertRectangle(svg,atof(x),atof(y),atof(w),atof(h),corC, corB, 1.0);
			free(centroRetangulo);
			aux++;
		}
		else if(strcmp("c",geoP)==0){
			id = (char*) malloc(sizeof(char)*50);
			fscanf(geo, "%s", id);	
			fscanf(geo, "%s", x);
			fscanf(geo, "%s", y);
			fscanf(geo, "%s", r);
			corB = (char*) malloc(sizeof(char)*31);
			strcpy(corB,corBordaCirculo);
			corC = (char*) malloc(sizeof(char)*31);
			strcpy(corC,corPreenchimentoCirculo);
			circulo = criarCirculo(corB,corC,id,atof(x),atof(y),atof(r));
			circulos = insertArvoreKd(circulos,criarNodo(circulo,getXC(circulo),getYC(circulo)),0);
			insertCircle(svg,atof(x),atof(y),atof(r),corC, corB, 1.0);
		}
		if(aux == 1){
        	maiorX = atof(x);
        	menorX = atof(x);
            maiorY = atof(y);
            menorY = atof(y);
        }
        if(aux > 1){
            if(atof(x) > maiorX){
                maiorX = atof(x);
			}
            else if(atof(x) < menorX){
                menorX = atof(x);
			}
            if(atof(y) > maiorY){
                maiorY = atof(y);
			}
            else if(atof(y) < menorY){
                menorY = atof(y);
			}
		}
        if((atof(h) > delta) && (atof(w) > atof(h))){
            delta = atof(w);
		}
        if((atof(h) > delta) && (atof(h) > atof(w))){
            delta = atof(h);
		}
		fscanf(geo, "%s", geoP);
	}
	free(arqSvg);
	closeSvgFile(svg);
	fclose(geo);

	id = malloc(sizeof(char)*10);
	corC = malloc(sizeof(char)*10);
	corB = malloc(sizeof(char)*10);
	strcpy(id,"borda");
	strcpy(corC,"none");
	strcpy(corB,"black");
	Retangulo borda = criarRetangulo(corB, corC, id, 0, 0, maiorX + delta + 150 , maiorY + delta + 150);
	if(arqQry != NULL){
		lerArquivoQry(arqQry,pathBSD,nomeArqGeo, nomeArqQry, retangulos, circulos, borda);
	}
	freeRetangulo(borda);
}

void lerArquivoQry(char* arqQry, char* pathBSD, char* nomeArqGeo, char* nomeArqQry, ArvoreKd retangulos, ArvoreKd circulos, Retangulo borda){
	FILE *qry, *txt;
	char qryP[25],qtdRets[25],x[25],y[25],w[25],h[25], idQry[30], r[25], k[30],s[30], *svgNome;
	int animacao=0;
	double meteoros[2000];
	int qtdMeteoros = 0, ocorreuIm = 0;
	Lista circulosCinzas=createLista();
	Lista circulosFinal=createLista();
	ArvoreBinaria poligonos = NULL;
	Lista todosPoligonos=createLista();
	Circulo movido = NULL;
	ArvoreKd ArvoreRetangulos=NULL;
	ArvoreBinaria sombras;
	Lista novosMortos;
	Lista mortos = createLista();
	qry = fopen(arqQry,"r");
	if(qry == NULL){
		printf("Nao foi possivel encontrar o arquivo qry");
		exit(0);
	}
	srand(time(NULL));
	fscanf(qry,"%s",qryP);
	txt = abrirNovoTxt(nomeArqGeo, nomeArqQry, pathBSD);
	svgNome = nomeSvgQry(nomeArqGeo, nomeArqQry, pathBSD); 
    SvgFile svgQry = newSvgFile(svgNome);
	while(1==1){
		if(feof(qry)){
			break;
		}
		else if(strcmp("dpi",qryP)==0){
			fprintf(txt,"\ndpi\n");
			fscanf(qry, "%s", x);
			fscanf(qry, "%s", y);
			Lista removidosDpi = createLista();
			retangulos = removerDpi(retangulos,retangulos,txt, atof(x), atof(y),removidosDpi);
			resultadosDpi(txt,removidosDpi);
			if(length(removidosDpi) > 0){
				removerNoArvores(removidosDpi,retangulos);
			}

			//Liberacao de memoria das variaveis auxiliares
			removeNodos(removidosDpi);
			free(removidosDpi);
		}
		else if(strcmp("dr",qryP)==0){
			fprintf(txt,"\ndr\n");
			fscanf(qry, "%s", idQry);
			Lista removidosDr = createLista();
			Retangulo ret = NULL;
			buscarRetanguloPeloId(retangulos, &ret, idQry);
			if(ret != NULL){
				retangulos = removerDr(retangulos,retangulos,txt,ret,removidosDr);
				resultadosDr(txt,removidosDr);
				if(length(removidosDr) > 0){
					removerNoArvores(removidosDr,retangulos);
				}
			}
			//Liberacao de memoria das variaveis auxiliares
			removeNodos(removidosDr);
			free(removidosDr);
		}
		else if(strcmp("fg",qryP)==0){
			fprintf(txt,"\nfg\n");
			fscanf(qry, "%s", x);
			fscanf(qry, "%s", y);
			fscanf(qry, "%s", r);
			Lista abrigos = createLista();
			Lista listasDeRefugiados = createLista();
    		Circulo circuloFg = criarCirculo(NULL,NULL,NULL,atof(x),atof(y),atof(r));
			//insertCircle(svgQry,getXC(circuloFg),getYC(circuloFg),getRC(circuloFg),NULL,NULL,1.0);
			circulos = fg(movido,circulosCinzas,circulosFinal,svgQry,circulos,retangulos,circulos,txt,circuloFg);
			resultadosFg(svgQry,txt,retangulos,circulos,abrigos,listasDeRefugiados);
			ordenarFg(txt,listasDeRefugiados,abrigos);

			//Liberacao de memoria das variaveis auxiliares
			free(circuloFg);
			removeNodos(abrigos);
			free(abrigos);
			removeNodos(listasDeRefugiados);
			free(listasDeRefugiados);
			animacao = 1;
		}
		else if(strcmp("im",qryP)==0){
			fprintf(txt,"\nim\n");
			fscanf(qry, "%s", x);
			fscanf(qry, "%s", y);
			fscanf(qry, "%s", s);
			Lista mortosIm = createLista();
			Lista mortosIns = createLista();
			double proporcao = atof(s);
			proporcao = (proporcao+3000)/1000;
			insertCircle(svgQry,atof(x),atof(y),proporcao,"#5E5E5E","#5E5E5E",1.0);
			poligonos = Im(txt, borda, retangulos,circulos,atof(x),atof(y),atof(s));
			meteoros[qtdMeteoros] = atof(s);
			qtdMeteoros++;
			insert(todosPoligonos,poligonos);
			circulos = aplicarRadiacao(circulos,poligonos,atof(s));
			circulos = resultadosIm(txt,circulos, circulos, mortosIm,mortosIns, mortos);
			fprintf(txt,"------Mortos Iminentes------\n");
			ordemIm(txt,mortosIm);
			fprintf(txt,"------Mortos Instantaneos------\n");
			ordemIm(txt,mortosIns);

			//Liberacao de memoria das variaveis auxiliares
			removeNodos(mortosIns);
			free(mortosIns);
			removeNodos(mortosIm);
			free(mortosIm);
			ocorreuIm = 1;
		}
		else if(strcmp("t30",qryP)==0){
			fprintf(txt,"\nt30\n");
			novosMortos = createLista();
			circulos = t30(circulos,circulos, novosMortos, mortos);
			resultadosT30(txt, novosMortos);

			//Liberacao de memoria das variaveis auxiliares
			removeNodos(novosMortos);
			free(novosMortos);
		}
		else if(strcmp("nve",qryP)==0){
			fprintf(txt,"\nnve\n");
			fscanf(qry, "%s", x);
			fscanf(qry, "%s", y);
			double radiacao;
			radiacao = nve(txt,todosPoligonos,atof(x),atof(y),meteoros);
			inserirRetanguloSuavizado(svgQry,atof(x),atof(y),radiacao);
		}
		fscanf(qry,"%s",qryP);	
	}
	inserirFormas(svgQry,retangulos,1);
	if(animacao){
		inserirFormasAnimadas(svgQry,circulosCinzas,circulosFinal);
		inserirPessoasAbrigadas(svgQry,txt,retangulos,circulos);
	}
	inserirFormas(svgQry,circulos,0);
	insertRectangleTransparent(svgQry,getX(borda),getY(borda),getW(borda),getH(borda),getPreenchimento(borda),getBorda(borda),1.0);
	inserirMortos(svgQry,mortos);
	

	//Liberacao de memoria das variaveis auxiliares utilizadas
	if(ocorreuIm){
		todosPoligonos = freeArvoresPoligonos(todosPoligonos);
	}
	else{
		free(todosPoligonos);
	}

	removeAll(mortos,0);
	removeAll(circulosCinzas,2);
	removeNodos(circulosFinal);
	free(circulosFinal);
	fclose(qry);
	free(svgNome);
	closeSvgFile(svgQry);
    fecharArquivoTxt(txt);
	liberaArvoreKd(retangulos,1);
	liberaArvoreKd(circulos,0);
}