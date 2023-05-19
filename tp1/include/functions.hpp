/*
Arquivo: functions.hpp
Conteudo: cabecalho de funcoes e bibliotecas usadas em functions.cpp e main.cpp
Autor: Marco Tulio Tristao
Data de criacao: 27-05-2022 - arquivo criado
                 31-05-2022 - comenta o codigo
                 02-06-2022 - criacao do TAD hand
                 03-06-2022 - separacao das funcoes do main para functions.cpp
*/

#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include "erro.hpp"
#include "player.hpp"
#include "Hand.hpp"
#include <iostream>
#include <cstring>
#include <string>
#include <algorithm>
#include <initializer_list>

extern int TOTAL_PLAYERS; // numero total de jogadores da mesa

// Cabecalhos
void rodada(const int &num_players, const int &pingo, player *table);
int play(bool *participantes, const int &num_players, const int &pingo, player *table);
int better_hand(bool *participantes, player *table);
int create_round_bet(bool *participantes, const int &pingo, player *table);
int desempata(const int &f, const int &s, player *table);
void print_result(player *table);
void print_winner(int num_players, int *winner, player *table);
int parse_input(int p, player *table);

#endif