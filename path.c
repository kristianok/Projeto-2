#include "path.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char* concatPathFile(char *path, char *fileName){
    char *arq;
    if(fileName == NULL){
        return NULL;
    }
    if(path != NULL){
	    arq = (char *)malloc((strlen(fileName)+strlen(path)+2)*sizeof(char));
    }
	if(path == NULL) {
		arq = (char *)malloc((strlen(fileName)+1)*sizeof(char));
        sprintf(arq,"%s",fileName);
    }
	else if(path[strlen(path)-1] == '/'){
		if(fileName[0] == '/'){
			sprintf(arq,"%s.%s",path,fileName);
		}
		else {
			sprintf(arq,"%s%s",path,fileName);	
		}
	}
	else if(fileName[0] == '/'){
		sprintf(arq,"%s%s",path,fileName);			
	}
	else {
		sprintf(arq,"%s/%s",path,fileName);			
	}
    return arq;
}

char *removeSuffix(char* nome){
	if(nome == NULL){
		return NULL;
	}
    char *nomeSemSuffix;
	nomeSemSuffix = (char*) malloc(((strlen(nome)+1)*sizeof(char)));
	strcpy(nomeSemSuffix,nome);
    nomeSemSuffix = strtok(nomeSemSuffix,".");
    return nomeSemSuffix;
}

char *removerPathDoNome(char* nome){
	if(nome == NULL){
		return NULL;
	}
	char *nomeSemPath;
	int indiceUltimaBarra=-1;
	for(int i = 0;i<strlen(nome);i++){
		if(nome[i]=='/'){
			indiceUltimaBarra = i;
		}
	}
	nomeSemPath = nome+indiceUltimaBarra+1;
	if(nomeSemPath == NULL){
		return nome;
	}
    return nomeSemPath;
}

char *addSuffix(char* nome, char* suffix){
	if(nome == NULL || suffix == NULL){
		return NULL;
	}
    char *nomeComSuffix;
	nomeComSuffix = (char*) malloc(((strlen(nome)+strlen(suffix)+2)*sizeof(char)));
    sprintf(nomeComSuffix,"%s%s",nome,suffix);
	return nomeComSuffix;
}

char *addPreffix(char* nome, char* preffix){
	if(nome == NULL || preffix == NULL){
		return NULL;
	}
    char *nomeComPreffix;
	nomeComPreffix = (char*) malloc(((strlen(nome)+strlen(preffix)+2)*sizeof(char)));
    sprintf(nomeComPreffix,"%s%s",preffix,nome);
	return nomeComPreffix;
}

