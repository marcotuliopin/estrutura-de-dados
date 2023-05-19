/*
Arquivo: Hand.cpp
Conteudo: implementacao do TAD player
Autor: Marco Tulio Tristao
Data de criacao: 27-05-2022 - arquivo criado
                 31-05-2022 - comenta o codigo
                 02-06-2022 - criacao do TAD hand
                 03-06-2022 - separacao das funcoes do main para functions.cpp
*/

#ifndef PLAYER_CPP
#define PLAYER_CPP

#include "player.hpp"
#include <iostream>

player::player() : hand(), name{""}, current_bet{0}, money{0} {}

/*
* Descricao: chama funcao para definir a mao do jogador para a rodada
* Modifica: p.hand
*/
void player::set_hand(std::ifstream &infile)
{
    this->hand.set_card(infile);
}

/*
* Descricao: define a aposta da rodada atual 
* Modifica: p.current_bet
*/
void player::set_bet(int i)
{
    this->current_bet = i;
}

/*
* Descricao: retorna -1 caso a aposta nao seja valida. No contrario, subtrai o valor da aposta do dinheiro do jogador e retorna esse valor.
* Modifica: p.money 
*/
int player::get_bet()
{
    // remove alguma contribuicao extra da mao da pessoa
    return this->current_bet;
}

/*
* Descricao: soma um valor ao dinheiro do jogador
* Requer: i (valor a ser somado)
* Modifica: p.money 
*/
void player::set_money(int i)
{
    this->money += i;
    if (this->money < 0)
        this->money = 0;
}

/*
* Descricao: retorna o valor do dinheiro do jogador
*/
int player::get_money()
{
    return this->money;
}

/*
* Descricao: define o nome do jogador
* Requer: str (nome do jogador)
* Modifica: p.name
*/
void player::set_name(const std::string str)
{
    this->name = str;
}

/*
* Descricao: retorna o nome do jogador
*/
std::string player::get_name()
{
    return this->name;
}

#endif