#include <stdio.h>
#include <stdlib.h>
#include "txt.h"

FILE* abrirNovoTxt(char* nomeArqGeo, char* nomeArqQry, char* pathBSD){
char* nomeArqGeoSemSuffix = removeSuffix(nomeArqGeo);
char* nomeArqQrySemSuffix = removeSuffix(nomeArqQry);
char* nomeArqGeoComTraco = addSuffix(nomeArqGeoSemSuffix,"-");
char* nomeArqGeoQryJunto = addSuffix(nomeArqGeoComTraco,nomeArqQrySemSuffix);
char* txtNomeSemPath = addSuffix(nomeArqGeoQryJunto,".txt");
char* txtNome = concatPathFile(pathBSD,txtNomeSemPath);
	FILE* txt = fopen(txtNome,"w");
	if(txt == NULL){
		printf("Nao foi possivel escrever no arquivo txt");
		exit(0);
	}
	escreverNome(txt);
	free(nomeArqGeoSemSuffix);
	free(nomeArqQrySemSuffix);
	free(nomeArqGeoComTraco);
	free(nomeArqGeoQryJunto);
	free(txtNomeSemPath);
	free(txtNome);
    return txt;
}

void fecharArquivoTxt(FILE* txt){
    if(txt != NULL){
        fclose(txt);
    }
}

void escreverNome(FILE* txt){
	fprintf(txt,"Kristiano Pasini de Oliveira\n");
}

void escreverDpi(FILE* txt, char** ids, int tamanho){
	for(int i = 0; i < tamanho; i++){
		fprintf(txt,"%s\n",ids[i]);
	}
}

void escreverDr(FILE* txt, char** ids, int tamanho){
	for(int i = 0; i < tamanho; i++){
		fprintf(txt,"%s\n",ids[i]);
	}
}

void escreverFgCirculos(FILE* txt, Circulo circ){
	if(circ == NULL){
		return;
	}
	fprintf(txt,"%s\n",getIdC(circ));
	}

void escreverFg(FILE* txt,Retangulo ret){
	if(ret == NULL){
		return;
	}
	fprintf(txt,"---------------------------------\n");
	fprintf(txt,"%s\n",getId(ret));
}

void escreverOrdenado(FILE* txt, char** ids, int tamanho){
	for(int i = 0; i < tamanho; i++){
		fprintf(txt,"%s\n",ids[i]);
	}
}