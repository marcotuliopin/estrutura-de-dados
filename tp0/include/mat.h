//---------------------------------------------------------------------
// Arquivo	        : mat.h
// Conteudo	        : definicoes do TAD MAT 
// Versao Original	: Wagner Meira Jr. (meira@dcc.ufmg.br)
// Reescrito por    : Marco Tulio P.T. Tristao (marcotristao@dcc.ufmg.br)
// Historico	    : 2021-10-18 - arquivo criado
//		            : 2021-10-21 - estrutura de diretorios
//                  : 2022-05-01 - modificado para alocacao dinamica
//---------------------------------------------------------------------

#ifndef MATH
#define MATH

#include "memlog.h"

typedef struct mat{
	double** m; // nao ha limite de tamanho definido para mat
	int tamx, tamy;
	int id;
} Matriz;


void transpoeMatriz(Matriz *a);
void multiplicaMatrizes(Matriz *a, Matriz *b, Matriz *c);
void somaMatrizes(Matriz *a, Matriz *b, Matriz *c);
double acessaMatriz(Matriz *mat);
void imprimeMatriz(Matriz *mat);
double leElemento (Matriz *mat, int x, int y);
void escreveElemento(Matriz *mat, int x, int y, double v);
void escreveMatriz(Matriz *mat, char file[]);
void copiaMatriz(Matriz *src, Matriz *dst, int dst_id);
void inicializaMatrizdeEntrada(Matriz *mat, char *file, int id);
void criaMatriz(Matriz *mat, int tx, int ty,int id);
void alocaMatriz(Matriz *mat);
void destroiMatriz(Matriz *a);

#endif
