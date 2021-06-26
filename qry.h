#ifndef QRY_H
#define QRY_H
#include "retangulo.h"
#include "listaDup.h"
#include "path.h"
#include "svg.h"
#include <stdio.h>
#include "arvoreKd.h"
#include "txt.h"
#include "calculos.h"
#include "visibilidade.h"
#include "arvoreBinaria.h"

/*
    Este módulo prove operacoes para o funcionamento
    de todos os comandos de consultas solicitadas
    pelos arquivos qry
*/

/* O parametro ListaDupla determina o tipo de lista usada na função 
(duplamente encadeada dinamica ou simplesmente encadeada estatica)*/

//Cria uma lista de 10 cores
Lista criarCores();

//Remove os retangulos cujo ponto x1 y1 e interno
ArvoreKd removerDpi(ArvoreKd arvore, ArvoreKd no, FILE* txt, double x1, double y1, Lista removidos);

//Remove os retangulos dentro do retangulo passado como parametro
ArvoreKd removerDr(ArvoreKd arvore, ArvoreKd no, FILE* txt, Retangulo ret, Lista removidos);

//Ordena e onsere no txt os dados referentes ao dpi
void resultadosDpi(FILE* txt, Lista removidos);

//Ordena e onsere no txt os dados referentes ao dr
void resultadosDr(FILE* txt, Lista removidos);

//Processa os dados do comando fg, recebe ambas as arvores e listas auxiliares para guarda as posicoes da rota da animacao
ArvoreKd fg(Circulo movido,Lista circulosCinzas,Lista circulosFinal,SvgFile svg,ArvoreKd noCirc, ArvoreKd retangulos, ArvoreKd circulos, FILE* txt, Circulo circuloFg);

//Armazena em listas auxiliares os resultados do comando fg e os envia para ordenacao e para ser escrito no txt
void resultadosFg(SvgFile svg,FILE* txt, ArvoreKd retangulos, ArvoreKd circulos, Lista abrigos,Lista refugiados);

//Conta a quantidade de pessoas escondidas em cada edificacao
int pessoasFg(FILE* txt, ArvoreKd retangulos, ArvoreKd circulos, int i);

//Insere em uma lista as pessoas que foram se esconder em um determinado retangulo e retorna essa quantidade
int pessoasAbrigadasFg(FILE* txt, ArvoreKd retangulos, ArvoreKd circulos, Lista refugiados);

//Ordena e envia para insercao no txt os resultados do comando fg
void ordenarFg(FILE* txt,Lista listasDeRefugiados,Lista abrigos);

//Processa os dados do comando im e gera uma arvore binaria dos poligonos de sombra
ArvoreBinaria Im(FILE* txt, Retangulo borda,ArvoreKd retangulos, ArvoreKd circulos, double x, double y, double s);

//Ordena e insere em uma lista auxiliar as pessoas com morte instanea e morte iminente
ArvoreKd resultadosIm(FILE* txt,ArvoreKd circulos,ArvoreKd no, Lista mortosIm,Lista mortosIns, Lista mortos);

//Ordena os dados de im e os envia para serem escritos no txt
void ordemIm(FILE* txt, Lista mortosIm);

//Processa os dados do comando t30 e gera lista auxiliares contendo os mortos recentes e passados
ArvoreKd t30(ArvoreKd no,ArvoreKd circulos, Lista novosMortos, Lista mortos);

//Insere no txt pessoas que morreram com o passar do tempo
void resultadosT30(FILE* txt, Lista novosMortos);

//Processa os dados do comando nve e insere no txt a exposicao do ponto
double nve(FILE* txt, Lista arvoresPoligonos, double x, double y, double* qtdRadiacao);

#endif