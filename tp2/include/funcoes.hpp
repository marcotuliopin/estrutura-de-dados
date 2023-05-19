#ifndef FUNCOES_HPP
#define FUNCOES_HPP

#include <iostream>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include "erro.hpp"
#include "vector.hpp"
#include "lista.hpp"

int handle_args(std::ifstream& in, std::ofstream& out, char** argv);

template <class T>
void quicksort(vector<T>& p);

#endif