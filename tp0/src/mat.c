//---------------------------------------------------------------------
// Arquivo	        : mat.c
// Conteudo	        : implementacao do TAD MAT
// Versao Original	: Wagner Meira Jr. (meira@dcc.ufmg.br)
// Reescrito por    : Marco Tulio P.T. Tristao (marcotristao@dcc.ufmg.br)
// Historico	    : 2021-10-18 - arquivo criado
//		            : 2021-10-21 - estrutura de diretorios
//                  : 2021-11-14 - adequacao para versao 1.1 memlog
//                  : 2022-05-01 - modificado para alocacao dinamica
//---------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include "mat.h"
#include "memlog.h"
#include "msgassert.h"

// limite superior da inicializacao aleatoria
#define INITRANDOMRANGE 10
// Macro que realiza swap sem variavel auxiliar
#define ELEMSWAP(x, y) (x += y, y = x - y, x -= y)

// Descricao: transpoe a matriz a
// Complexidade: quadratica no tempo
void transpoeMatriz(Matriz *a)
{
    // determina a maior dimensao entre tamx e tamy
    int dim = (a->tamx > a->tamy ? a->tamx : a->tamy);

    // faz a transposicao como se a matriz fosse quadrada
    for (int i = 0; i < dim; i++)
    {
        for (int j = i + 1; j < dim; j++)
        {
            ELEMSWAP((a->m[i][j]), (a->m[j][i]));
            ESCREVEMEMLOG((long int)(&(a->m[i][j])), sizeof(double), a->id);
            ESCREVEMEMLOG((long int)(&(a->m[j][i])), sizeof(double), a->id);
        }
    }
    // inverte as dimensoes da matriz transposta
    ELEMSWAP(a->tamx, a->tamy);
}

// Descricao: multiplica as matrizes a e b e armazena o resultado em c
// Complexidade: cubica no tempo e quadratica no espaço
void multiplicaMatrizes(Matriz *a, Matriz *b, Matriz *c)
{
    // verifica a compatibilidade das dimensoes
    erroAssert(a->tamy == b->tamx, "Dimensoes incompativeis");

    criaMatriz(c, a->tamx, b->tamy, 2);

    // realiza a multiplicacao de matrizes
    for (int i = 0; i < c->tamx; i++)
    {
        for (int j = 0; j < c->tamy; j++)
        {
            for (int k = 0; k < a->tamy; k++)
            {
                c->m[i][j] += a->m[i][k] * b->m[k][j];
                LEMEMLOG((long int)(&(a->m[i][k])), sizeof(double), a->id);
                LEMEMLOG((long int)(&(b->m[k][j])), sizeof(double), b->id);
                ESCREVEMEMLOG((long int)(&(c->m[i][j])), sizeof(double), c->id);
            }
        }
    }
}

// Descricao: soma as matrizes a e b e armazena o resultado em c
// Complexidade: quadratica no tempo e no espaço
void somaMatrizes(Matriz *a, Matriz *b, Matriz *c)
{
    // verifica se as dimensoes das matrizes a e b sao as mesmas
    erroAssert(a->tamx == b->tamx, "Dimensoes incompativeis");
    erroAssert(a->tamy == b->tamy, "Dimensoes incompativeis");

    // cria e inicializa a matriz c
    criaMatriz(c, a->tamx, a->tamy, 2);

    // faz a soma elemento a elemento
    for (int i = 0; i < a->tamx; i++)
    {
        for (int j = 0; j < a->tamy; j++)
        {
            c->m[i][j] = a->m[i][j] + b->m[i][j];
            LEMEMLOG((long int)(&(a->m[i][j])), sizeof(double), a->id);
            LEMEMLOG((long int)(&(b->m[i][j])), sizeof(double), b->id);
            ESCREVEMEMLOG((long int)(&(c->m[i][j])), sizeof(double), c->id);
        }
    }
}

// Descricao: acessa mat para fins de registro de acesso
// Complexidade: quadratica no tempo
double acessaMatriz(Matriz *mat)
{
    double aux, s = 0.0;
    for (int i = 0; i < mat->tamx; i++)
    {
        for (int j = 0; j < mat->tamy; j++)
        {
            aux = mat->m[i][j];
            s += aux;
            LEMEMLOG((long int)(&(mat->m[i][j])), sizeof(double), mat->id);
        }
    }
    return s; // apenas para evitar que acesso seja eliminado
}

// Descricao: imprime a matriz com a identificacao de linhas e colunas
// Complexidade: quadratica no tempo
void imprimeMatriz(Matriz *mat)
{
    // imprime os identificadores de coluna
    printf("%9s", " ");
    for (int j = 0; j < mat->tamy; j++)
        printf("%8d ", j);
    printf("\n");

    // imprime as linhas
    for (int i = mat->tamx - 1; i >= 0; i--)
    {
        printf("%8d ", i);
        for (int j = 0; j < mat->tamy; j++)
        {
            printf("%8.2f ", mat->m[i][j]);
            LEMEMLOG((long int)(&(mat->m[i][j])), sizeof(double), mat->id);
        }
        printf("\n");
    }
}

// Descricao: retorna o elemento (x,y) de mat
// Complexidade: nao varia com a entrada
double leElemento(Matriz *mat, int x, int y)
{
    // verifica se x e y sao validos
    erroAssert((x < 0) || (x >= mat->tamx), "Indice invalido");
    erroAssert((y < 0) || (y >= mat->tamy), "Indice invalido");

    LEMEMLOG((long int)(&(mat->m[x][y])), sizeof(double), mat->id);
    return mat->m[x][y];
}

// Descricao: atribui o valor v ao elemento (x,y) de mat
// Complexidade: nao varia com a entrada
void escreveElemento(Matriz *mat, int x, int y, double v)
{
    // verifica se x e y sao validos
    erroAssert((x < 0) || (x >= mat->tamx), "Indice invalido");
    erroAssert((y < 0) || (y >= mat->tamy), "Indice invalido");

    mat->m[x][y] = v;
    ESCREVEMEMLOG((long int)(&(mat->m[x][y])), sizeof(double), mat->id);
}

// Descricao: escreve a matriz mat em um arquivo de saida
// Complexidade: quadratica no tempo
void escreveMatriz(Matriz *mat, char f[])
{
    // cria arquivo de saida
    FILE *file = fopen(f, "w");
    erroAssert(file != NULL, "Falha ao criar arquivo de saida");
    // escreve a matriz no arquivo de saida
    for (int i = mat->tamx - 1; i >= 0; i--)
    {
        for (int j = 0; j < mat->tamy; j++)
        {
            fprintf(file, "%.2f ", mat->m[i][j]);
            LEMEMLOG((long int)(&(mat->m[i][j])), sizeof(double), mat->id);
        }
        fprintf(file, "\n");
    }

    fclose(file);
}

// Descricao: faz uma copia de src em dst
// Complexidade: quadratica no tempo e no espaço
void copiaMatriz(Matriz *src, Matriz *dst, int dst_id)
{
    // cria novamente a matriz dst para ajustar as suas dimensoes
    criaMatriz(dst, src->tamx, src->tamy, dst_id);
    // copia os elementos da matriz src
    for (int i = 0; i < src->tamx; i++)
    {
        for (int j = 0; j < src->tamy; j++)
        {
            dst->m[i][j] = src->m[i][j];
            LEMEMLOG((long int)(&(src->m[i][j])), sizeof(double), src->id);
            ESCREVEMEMLOG((long int)(&(dst->m[i][j])), sizeof(double), dst->id);
        }
    }
}

// Descricao: le o arquivo de entrada e atribui os valores a matriz
// Complexidade: quadratica no tempo e no espaço 
void inicializaMatrizdeEntrada(Matriz *mat, char *f, int id)
{
    FILE *file = fopen(f, "r");
    // verifica se o arquivo com a matriz foi aberto
    erroAssert(file != NULL, "Falha ao abrir arquivo de leitura");

    // le o tamanho da matriz
    char line1[3];
    fgets(line1, 4, file);
    int tx = line1[0] - '0';
    int ty = line1[2] - '0'; 

    // inicializa as dimensoes e aloca memoria para mat
    criaMatriz(mat, tx, ty, id);

    // designa os inteiros do arquivo para os elementos de mat
    for (int i = mat->tamx - 1; i >= 0; i--)
    {
        for (int j = 0; j < mat->tamy; j++)
        {
            char c = getc(file); 
            erroAssert(!feof(file), "Tamanho da entrada não corresponde ao da matriz");

            while (!isdigit(c))
                c = getc(file);
            mat->m[i][j] = c - '0';
            ESCREVEMEMLOG((long int)(&(mat->m[i][j])), sizeof(double), mat->id);
        }
    }

    fclose(file);
}

// Descricao: cria matriz com dimensoes tx X ty
// Complexidade: linear no tempo e quadratica no espaço
void criaMatriz(Matriz *mat, int tx, int ty, int id)
{
    // inicializa as dimensoes da matriz
    mat->tamx = tx;
    mat->tamy = ty;
    // verifica se os valores de tx e ty são validos
    erroAssert(mat->tamx > 0 && mat->tamy > 0, "Dimensão x ou y nula");

    // inicializa o identificador da matriz, para rastreamento
    mat->id = id;

    alocaMatriz(mat);
}

// Descricao: aloca memoria para a matriz mat
// Complexidade: linear no tempo e quadratica no espaço
void alocaMatriz(Matriz *mat)
{
    // aloca memoria para a matriz
    mat->m = malloc(mat->tamx * sizeof(double *));
    erroAssert(mat->m != NULL, "Falha ao alocar memória");
    ESCREVEMEMLOG((long int)(&(mat->m)), mat->tamx * sizeof(double *), mat->id);

    // inicializa os elementos da matriz para 0, por segurança
    for (int i = 0; i < mat->tamx; i++)
    {
        mat->m[i] = calloc(mat->tamy, sizeof(double));
        erroAssert(mat->m[i] != NULL, "Falha ao inicializar vetor");
        ESCREVEMEMLOG((long int)(&(mat->m[i])), mat->tamy * sizeof(double), mat->id);
    }
}

// Descricao: destroi a matriz a, que se torna inacessível
// Complexidade: O(n) no tempo
void destroiMatriz(Matriz *a)
{
    // impede o acesso a ponteiro nulo caso a matriz tenha sido destruida
    erroAssert(a->m != NULL, "Matriz já foi destruida");

    // libera a memoria alocada para a matriz
    for (int i = 0; i < a->tamx; i++)
        free(a->m[i]);
    free(a->m);
    a->m = NULL;

    a->tamx = a->tamy = a->id = -1;
}
