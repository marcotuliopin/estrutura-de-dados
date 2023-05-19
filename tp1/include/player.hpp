/*
Arquivo: player.hpp
Conteudo: cabecalho do TAD player
Autor: Marco Tulio Tristao
Data de criacao: 27-05-2022 - arquivo criado
                 31-05-2022 - comenta o codigo
                 02-06-2022 - criacao do TAD hand
                 03-06-2022 - separacao das funcoes do main para functions.cpp
*/

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Hand.hpp"
#include <string>

class player
{
    public:
        player();
        void set_hand(std::ifstream &infile);
        void set_bet(int i);
        int get_bet();
        void set_money(int i);
        int get_money();
        void set_name(const std::string str);
        std::string get_name();
        Hand hand; // mao do jogador
    private:
        std::string name; // nome do jogador
        int current_bet; // aposta atual do jogador
        int money; // dinheiro em carteira
};

#endif