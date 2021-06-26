#ifndef GEOQRY_H
#define GEOQRY_H
#include "arvoreKd.h"
#include "path.h"
#include "retangulo.h"
#include "circulo.h"
#include "svg.h"
#include "txt.h"
#include "qry.h"
#include "arvoreBinaria.h"
#include "listaDup.h"
#include "visibilidade.h"

/*
    Este módulo prove operacoes para a leitura e processamento
    dos arquivos .geo e .qry. 
*/

/*  Os parametros arqGeo e arqQry correspondem ao
    path completo do arquivo ao passo que os parametros nomeArqGeo e nomeArqQry sao apenas
    os nomes do arquivo em si
*/

//Função responsável por ler e interpretar os dados do arquivo geo passado nos parametros
void lerArquivoGeo(char* arqGeo, char* pathBSD, char* nomeArqGeo,char* arqQry, char* nomeArqQry);

//Função responsável por ler e interpretar os dados do arquivo qry passado nos parametros
void lerArquivoQry(char* arqQry, char* pathBSD, char* nomeArqGeo, char* nomeArqQry, ArvoreKd retangulos, ArvoreKd circulos, Retangulo borda);

#endif