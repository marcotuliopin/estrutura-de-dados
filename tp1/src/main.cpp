/*
Arquivo: main.cpp
Conteudo: programa que simula um jogo virtual de poker
Autor: Marco Tulio Tristao
Data de criacao: 27-05-2022 - arquivo criado
                 31-05-2022 - comenta o codigo
                 02-06-2022 - criacao do TAD hand
                 03-06-2022 - separacao das funcoes do main para functions.cpp
*/

#ifndef MAIN_CPP
#define MAIN_CPP

#include "functions.hpp"

std::ifstream infile;
std::ofstream outfile;

/*
* Descricao: simula uma partida virtual de poker, com varios jogadores
*/
int main(int argc, char *argv[])
{
    // checa se os argumentos estao corretos
    if (erro_arg(__FILE__, argc))
        return 1;

    // abre os arquivos de entrada e de saida    
    infile.open(argv[1]);
    outfile.open(argv[2]);
    // checa se a abertura dos arquivo foi correta
    if (!infile || !outfile)
        return erro_file(__FILE__, __LINE__);

    int num_players, pingo; // numero de jogadores, aposta minima
    int num_rounds, di; // numero de rodadas, dinheiro inicial dos jogadores

    infile >> num_rounds >> di >> num_players >> pingo;

    TOTAL_PLAYERS = num_players; 

    // inicia a tabela de jogadores
    player table[num_players];

    for (int i = 0; i < num_players; i++)
        table[i].set_money(di);
    // faz as rodadas do jogo
    do
    {
        // checa se o numero de jogadores na rodada é valido
        if (num_players > TOTAL_PLAYERS || num_players < 0)
            return erro_num();
        rodada(num_players, pingo, table);
    }
    while (infile >> num_players >> pingo);

    // imprime o resultado final dos jogadores
    print_result(table);

    infile.close();
    outfile.close();
}

#endif