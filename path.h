#ifndef PATH_H
#define PATH_H

/*
    Este módulo prove operacoes para a manipulacao de strings com
    o objetivo de nomear e estabelecer o path dos arquivos passados
    como parametro no programa
 */

//Retorna a concatenacao do path com o nome do arquivo com ou sem subpastas, evitando erros com / duplicadas
char* concatPathFile(char *path, char *fileName);

//Retorna a string sem seu suffixo .geo,.qry etc.
char* removeSuffix(char* nome);

//Retorna a string com extensão/suffixo passado nos parametros
char* addSuffix(char* nome, char* suffix);

//Remove o path de subpasta do nome do arquivo passado nos parametros
char *removerPathDoNome(char* nome);

//Adiciona um preffixo ao nome
char *addPreffix(char* nome, char* preffix);

#endif
