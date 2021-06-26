#include "qry.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

ArvoreKd removerDpi(ArvoreKd arvore, ArvoreKd no, FILE* txt, double x1, double y1, Lista removidos){
    if(no != NULL){
        removerDpi(arvore,getNoDireitaKd(no),txt,x1,y1,removidos);
        removerDpi(arvore,getNoEsquerdaKd(no),txt,x1,y1,removidos);
        Retangulo removivel = getItemKd(no);
        if(checarPontoInterno(x1,y1,removivel)){
            insert(removidos,no);
        }
	}
    return arvore;
}

void resultadosDpi(FILE* txt, Lista removidos){
    int i = 0;
    char** novos = (char**) malloc(sizeof(char*)*length(removidos));
    Posic novo = getFirst(removidos);   
    while(novo != NULL){
        novos[i] = getId(getItemKd(getItem(novo)));
        i++;
        novo = getNext(removidos,novo);
    }
    qsort(novos,i,sizeof(char*),compararAlfanumerico);
    escreverDpi(txt,novos,i);
    free(novos);
}

ArvoreKd removerDr(ArvoreKd arvore, ArvoreKd no,FILE* txt, Retangulo ret, Lista removidos){
	if(no != NULL){
        removerDr(arvore,getNoDireitaKd(no),txt, ret,removidos);
        removerDr(arvore,getNoEsquerdaKd(no),txt, ret,removidos);
        Retangulo removivel = getItemKd(no);
        if(checarInterior(ret,removivel) && ret != removivel){
            //printf("|%p|\n",no);
            insert(removidos,no);
        }
	}
    return arvore;
}

void resultadosDr(FILE* txt, Lista removidos){
    int i = 0;
    char** novos = (char**) malloc(sizeof(char*)*length(removidos));
    Posic novo = getFirst(removidos);   
    while(novo != NULL){
        novos[i] = getId(getItemKd((getItem(novo))));
        i++;
        novo = getNext(removidos,novo);
    }
    qsort(novos,i,sizeof(char*),compararAlfanumerico);
    escreverDr(txt,novos,i);
    free(novos);
}

ArvoreKd fg(Circulo movido,Lista circulosCinzas, Lista circulosFinal,SvgFile svg,ArvoreKd noCirc, ArvoreKd retangulos, ArvoreKd circulos, FILE* txt, Circulo circuloFg){ 
    if(noCirc != NULL && retangulos != NULL){

        fg(movido,circulosCinzas,circulosFinal,svg,getNoDireitaKd(noCirc),retangulos,circulos,txt, circuloFg);
        fg(movido,circulosCinzas,circulosFinal,svg,getNoEsquerdaKd(noCirc),retangulos,circulos,txt, circuloFg);

        Circulo pessoa = getItemKd(noCirc);

        if(circInterior(circuloFg,pessoa)){
            ArvoreKd abrigoKd = buscarVizinhoMaisProximo(getPontosKd(noCirc),retangulos,0);
            if(checarPontoInterno(getXC(pessoa),getYC(pessoa),getItemKd(abrigoKd)) == 0 && getAnimacao(pessoa)==0){
                pessoa = moverCirculo(getItemKd(abrigoKd),circulos,circulosCinzas,circulosFinal,svg,pessoa,movimentacaoEmX(getXC(pessoa),getPontoKd(abrigoKd,0)),movimentacaoEmY(getYC(pessoa),getPontoKd(abrigoKd,1))); 
                circulos = removeArvoreKd(circulos,noCirc,0,0);             
            }     
        }  
	}
    return circulos;
}

int pessoasFg(FILE* txt, ArvoreKd retangulos, ArvoreKd circulos, int i){
	if(retangulos != NULL && circulos != NULL){
		Circulo circulo = getItemKd(circulos);
		Retangulo ret = getItemKd(retangulos);
		if(checarPontoInterno(getXC(circulo),getYC(circulo),ret) == 1){
			i++;
		}
		i = pessoasFg(txt,retangulos,getNoDireitaKd(circulos), i);
		i = pessoasFg(txt,retangulos,getNoEsquerdaKd(circulos), i);
	}
    return i;
}

int pessoasAbrigadasFg(FILE* txt, ArvoreKd retangulos, ArvoreKd circulos, Lista refugiados){
	if(retangulos != NULL && circulos != NULL){
        int i = 0;
		Circulo circulo = getItemKd(circulos);
		Retangulo ret = getItemKd(retangulos);
		if(checarPontoInterno(getXC(circulo),getYC(circulo),ret) && getMovido(circulo) == 1){
            i = 1;
            circulo = setMovido(circulo,0);
            insert(refugiados,circulo);
		}
        return i + pessoasAbrigadasFg(txt,retangulos,getNoDireitaKd(circulos),refugiados) + pessoasAbrigadasFg(txt,retangulos,getNoEsquerdaKd(circulos),refugiados);
	}
    return 0;
}

void resultadosFg(SvgFile svg,FILE* txt, ArvoreKd retangulos, ArvoreKd circulos, Lista abrigos, Lista listasDeRefugiados){
	if(retangulos != NULL && circulos != NULL){
        int abrigados = 0;
		Retangulo ret = getItemKd(retangulos);
        Lista refugiados = createLista();
		resultadosFg(svg,txt,getNoDireitaKd(retangulos),circulos,abrigos,listasDeRefugiados);
		resultadosFg(svg,txt,getNoEsquerdaKd(retangulos),circulos,abrigos,listasDeRefugiados);
        abrigados = pessoasAbrigadasFg(txt,retangulos,circulos,refugiados);
        if(abrigados > 0){
            insert(listasDeRefugiados,refugiados);
            insert(abrigos,ret);
        } 
        else{
            free(refugiados);
        }
	}
}

void ordenarFg(FILE* txt,Lista listasDeRefugiados,Lista abrigos){
    Posic abri = getFirst(abrigos);
    char** abrigosOrdenados = (char**) malloc(sizeof(char*)*length(abrigos));
    int i2 = 0;
    while(abri != NULL){   
        abrigosOrdenados[i2] = getId(getItem(abri));
        i2++;
        abri = getNext(abrigos,abri);
    }
    qsort(abrigosOrdenados,i2,sizeof(char*),compararAlfanumerico);
    for(int i = 0;i< i2;i++){
        int j = 0;
        for(Posic refu = getFirst(listasDeRefugiados),abri = 
            getFirst(abrigos);refu != NULL;refu = getNext(listasDeRefugiados,refu), 
            abri = getNext(abrigos,abri)){
            if(abrigosOrdenados[i] == getId(getItem(abri))){
                Lista refugiados = getItem(refu);
                int b = 0;
                char** novos = (char**) malloc(sizeof(char*)*length(refugiados));
                Posic novo = getFirst(refugiados);   
                while(novo != NULL){
                    novos[b] = getIdC(getItem(novo));
                    b++;
                    novo = getNext(refugiados,novo);
                }
                qsort(novos,b,sizeof(char*),compararAlfanumerico);
                escreverFg(txt,getItem(abri));
                escreverOrdenado(txt,novos,b);
                removeNodos(refugiados);
                free(refugiados);
                free(novos);
            }
        }
    }
    free(abrigosOrdenados);
}

ArvoreBinaria Im(FILE* txt,Retangulo borda, ArvoreKd retangulos, ArvoreKd circulos, double x, double y, double s){
    Lista segmentos = createLista();
    ArvoreBinaria poligonos;
	segmentos = coletarSegmentos(segmentos,retangulos,x,y);
    poligonos = buscarPoligonos(borda,segmentos,x,y);
    liberarSegmentos(segmentos);
	removeNodos(segmentos);
	free(segmentos);
    return poligonos;
}

ArvoreKd resultadosIm(FILE* txt,ArvoreKd circulos, ArvoreKd no, Lista mortosIm,Lista mortosIns, Lista mortos){
    if(circulos != NULL){
        resultadosIm(txt,getNoEsquerdaKd(circulos),no,mortosIm,mortosIns,mortos);
        resultadosIm(txt,getNoDireitaKd(circulos),no,mortosIm,mortosIns,mortos);
        char* cor = definirCores(getRadiacao(getItemKd(circulos)));
        setPreenchimentoC(getItemKd(circulos),cor);
        if(getRadiacao(getItemKd(circulos))>=1000 && getRadiacao(getItemKd(circulos)) < 8000){
            insert(mortosIm,getItemKd(circulos));
        }
        else if(getRadiacao(getItemKd(circulos))>=8000){
            insert(mortosIns,getItemKd(circulos));
            insert(mortos,getItemKd(circulos));
            no = removeArvoreKd(no,circulos,0,2);
        }
        //printf("%lf\n",getRadiacao(getItemKd(circulos)));
    }
    return no;
}

ArvoreKd t30(ArvoreKd no,ArvoreKd circulos, Lista novosMortos, Lista mortos){
    if(circulos != NULL){
        t30(no,getNoEsquerdaKd(circulos),novosMortos,mortos);
        t30(no,getNoDireitaKd(circulos),novosMortos,mortos);
        Circulo pessoa = getItemKd(circulos);
        if(getRadiacao(pessoa) >= 1000 && getRadiacao(pessoa) < 8000){
            setPreenchimentoC(pessoa,"#000000");
            insert(mortos,pessoa);
            insert(novosMortos,pessoa);
            no = removeArvoreKd(no,circulos,0,2);
        }
    }
    return no;
}

void ordemIm(FILE* txt, Lista mortosIm){
    int i = 0;
    char** novos = (char**) malloc(sizeof(char*)*length(mortosIm));
    Posic novo = getFirst(mortosIm);   
    while(novo != NULL){
        novos[i] = getIdC(getItem(novo));
        i++;
        novo = getNext(mortosIm,novo);
    }
    qsort(novos,i,sizeof(char*),compararAlfanumerico);
    escreverOrdenado(txt,novos,i);
    free(novos);
}

void resultadosT30(FILE* txt, Lista novosMortos){
    int i = 0;
    char** novos = (char**) malloc(sizeof(char*)*length(novosMortos));
    Posic novo = getFirst(novosMortos);   
    while(novo != NULL){
        novos[i] = getIdC(getItem(novo));
        i++;
        novo = getNext(novosMortos,novo);
    }
    qsort(novos,i,sizeof(char*),compararAlfanumerico);
    escreverOrdenado(txt,novos,i);
    free(novos);
}

double nve(FILE* txt, Lista arvoresPoligonos, double x, double y, double* qtdRadiacao){
    Posic ar = getFirst(arvoresPoligonos);
    int i = 0;
    double rad = 0, radiacao = 0;
    while(ar!=NULL){
        ArvoreBinaria poligonos = getItem(ar);
        ar = getNext(arvoresPoligonos,ar);
        int sombras = calcularRadiacao(x,y,poligonos);
        rad = qtdRadiacao[i] * pow(0.8,sombras);
        radiacao += rad;
        i++;
    }
    fprintf(txt,"Quantidade de radiacao no ponto: %lf",radiacao);
    return radiacao;
}