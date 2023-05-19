
#ifndef ERRO_HPP
#define ERRO_HPP

#include "player.hpp"
#include <iostream>

void erro_init(const char *f, const int l);
int erro_arg(const char *f, int args);
int erro_bet(int p, int pingo, player *table, std::ofstream &outfile);
int erro_file(const char *f, const int l);
int erro_num();

#endif