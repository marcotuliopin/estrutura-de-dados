/*
Arquivo: Hand.cpp
Conteudo: cabecalho do TAD Hand 
Autor: Marco Tulio Tristao
Data de criacao: 27-05-2022 - arquivo criado
                 31-05-2022 - comenta o codigo
                 02-06-2022 - criacao do TAD hand
                 03-06-2022 - separacao das funcoes do main para functions.cpp
*/

#ifndef HAND_HPP
#define HAND_HPP

#define HANDTAM 5

#include <string>
#include <fstream>

class Hand
{
    friend class player;
    public:
        Hand();
        int get_value();
        int* get_tb(int *e);
    private:
        void set_card(std::ifstream &infile);
        void sort();
        void set_value();
        int check_sequence();
        bool check_suits();
        int check_numbers();
        int different_numbers();
        void set_tb();
        int value; // valor da jogada
        int card[HANDTAM][2]; // cartas {valor, naipe}
        int tiebreaker[3]; // criterios de desempate
};

#endif