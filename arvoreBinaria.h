#ifndef ARVOREBINARIA_H
#define ARVOREBINARIA_H

typedef void* Item;
typedef void *ArvoreBinaria;

/*
    Este modulo contem toda a implementacao do TAD Arvore Binaria
*/

//Imprime os valores de uma arvore binaria
void imprimirArvoreB(ArvoreBinaria n);
//Retorna o valor de referencia de uma arvore binaria
double getXBinaria(ArvoreBinaria arvore);
//Retorna o item armazenado em um no de uma arvore binaria
Item getItemB(ArvoreBinaria arvore);
//Cria um no de arvore binaria
ArvoreBinaria criarNodoB(Item item, double x);
//Insere um no em determinado lado de uma arvore binaria de acordo com seu valor de referencia
ArvoreBinaria insertArvoreB(ArvoreBinaria arvore, ArvoreBinaria novo);
//Remove um elemento da arvore binaria, respeitando suas propriedades
ArvoreBinaria removeArvoreBinaria(ArvoreBinaria inicio, ArvoreBinaria nodo);
//Retorna o no com o menor valor de referencia
ArvoreBinaria encontraMinimoB(ArvoreBinaria arvore);
//Copia o conteudo de um nodo para outro da arvore binaria
void copiarNodo(ArvoreBinaria arvore1, ArvoreBinaria arvore2);
//Retorna o no a direita de uma raiz/no
ArvoreBinaria getNodoDireitaB(ArvoreBinaria arvore);
//Retorna o no a esquerda de uma raiz/no
ArvoreBinaria getNodoEsquerdaB(ArvoreBinaria arvore);
//Libera a memoria utilizada por uma arvore binaria
ArvoreBinaria liberaArvoreBinaria(ArvoreBinaria arvore, int tipo);
#endif