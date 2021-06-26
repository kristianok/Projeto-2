#ifndef TXT_H
#define TXT_H
#include <stdio.h>
#include "retangulo.h"
#include "path.h"

/*
    Este modulo prove operacoes para a criacao, delecao e manipulacao de arquivos no formato txt.
    Tambem eh responsavel por escrever dados especificos solicitados pelas funcoes de consulta.
 */

//Gera e abre um novo arquivo txt e o retorna
FILE* abrirNovoTxt(char* nomeArqGeo, char* nomeArqQry, char* pathBSD);
//Fecha um arquivo txt
void fecharArquivoTxt(FILE* txt);
//Escreve o nome do aluno no txt
void escreverNome(FILE* txt);
//Escreve os dados da funcao dpi
void escreverDpi(FILE* txt, char** ids, int tamanho);
//Escreve os dados da funcao dr
void escreverDr(FILE* txt, char** ids, int tamanho);
//Escreve os circulos que se movem na funcao fg
void escreverFgCirculos(FILE* txt, Circulo circ);
//Escreve os retangulos utilizados como refugio na funcao fg
void escreverFg(FILE* txt,Retangulo ret);
//Escreve os ids das pessoas de forma ordenada
void escreverOrdenado(FILE* txt, char** ids, int tamanho);
#endif