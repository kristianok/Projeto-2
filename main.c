#include "main.h"
#include <stdlib.h>
#include <string.h>
int main(int argc, char *argv[])
{
	int i=1;
	char *nomeArqGeo=NULL, *nomeArqQry=NULL, *pathBED=NULL, *pathBSD=NULL, *arqGeo=NULL, *arqQry=NULL; 
	//Coleta dos parametros do programa
	while(i<argc){
		if (strcmp("-e",argv[i])==0){
		i++;
		if(argc-1 < i){
			printf("Parametros insuficientes");
			exit(0);
		}
		pathBED = (char *)malloc((strlen(argv[i])+1)*sizeof(char));
		strcpy(pathBED,argv[i]);
		}
	
		else if (strcmp("-f",argv[i])==0){
			i++;
			if(argc-1 < i){
				printf("Parametros insuficientes");
				exit(0);
			}
		nomeArqGeo = (char *)malloc((strlen(argv[i])+1)*sizeof(char));
		strcpy(nomeArqGeo,argv[i]);
		}	
	
		else if (strcmp("-o",argv[i])==0){
			i++;
			if(argc-1 < i){
				printf("Parametros insuficientes");
				exit(0);
			}
			pathBSD = (char *)malloc((strlen(argv[i])+1)*sizeof(char));
			strcpy(pathBSD,argv[i]);
		}
	
		else if (strcmp("-q",argv[i])==0){
			i++;
			if(argc-1 < i){
				printf("Parametros insuficientes");
				exit(0);
			}
			nomeArqQry = (char *)malloc((strlen(argv[i])+1)*sizeof(char));
			strcpy(nomeArqQry,argv[i]);
		}
		i++;
	}
	char* auxNomeGeo, *auxNomeQry;
	arqGeo = concatPathFile(pathBED,nomeArqGeo);
	auxNomeGeo = removerPathDoNome(nomeArqGeo);
	arqQry = concatPathFile(pathBED,nomeArqQry);
	auxNomeQry = removerPathDoNome(nomeArqQry);
	lerArquivoGeo(arqGeo,pathBSD,auxNomeGeo,arqQry,auxNomeQry);
	
	free(arqGeo);
	free(nomeArqGeo);
	free(pathBED);
	free(pathBSD);
	if(nomeArqQry != NULL){
		free(arqQry);
		free(nomeArqQry);
	}
	return 0;
}
