#ifndef ERRO_HPP
#define ERRO_HPP

#include <iostream>

int erro_argc()
{
    std::cout << "erro ao ler argumentos: numero de argumentos errado" << std::endl;    
    exit(1);
}

int erro_file()
{
    std::cout << "erro ao abrir arquivo de entrada/saida: impossivel abrir arquivo" << std::endl;
    exit(2);
}

#endif