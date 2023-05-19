#ifndef FUNCOES_CPP
#define FUNCOES_CPP

#include "funcoes.hpp"
#include "erro.hpp"

int handle_args(std::ifstream& in, std::ofstream& out, char** argv)
{
    int aux;
    for (int i = 1; i < 8; i += 2)
    {
        if (argv[i] == "-[i|I]")
            in.open(argv[i + 1]);
        else if (argv[i] == "-[o|O]")
            out.open(argv[i + 1]);
        else if (argv[i] == "-[m|M]" || argv[i] == "-[s|S]")
        {
            std::cin >> aux;
            return aux;
        }
    }

    if (!in.is_open() || !out.is_open())
        erro_file(); 
}

template <class T>
void quicksort(lista<T>& p)
{
}

#endif