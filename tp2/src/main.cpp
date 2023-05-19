/*
Arquivo: main.cpp
Conteudo: programa que poe em uma ordem arbitraria as palavras de um texto
Autor: Marco Tulio Tristao
Data de criacao: 20-06-2022 - arquivo criado
                 22-06-2022 - finalizacao do codigo do arquivo
*/

#ifndef MAIN_CPP
#define MAIN_CPP

#include "funcoes.hpp"

/*
* Descricao: recebe uma ordem arbitraria dos caracteres alfabeticos e um texto que deve ser ordenado nessa ordem
* Requer: arquivo de entrada (flag -[i|I]), arquivo de saida (flag -[o|O]), mediana (flag -[m|M]),
*   maior particao a ser ordenada separadamente (flag -[s|S])
*/
int main(int argc, char** argv)
{
    std::ifstream in; // arquivo de entrada
    std::ofstream out; // arquivo de saida
    std::string leitor; // auxiliar para leitura do arquivo
    char ordem[26]; // nova ordem lexicografica
    vector<std::string> texto; // vetor de palavras do texto

    if (argc != 9)
        erro_argc();

    // parsea os argumentos da linha de comando
    handle_args(in, out, argv);

    // faz a leitura do arquivo de entrada
    in >> leitor;
    while (!in.eof())
    {
        // le a nova ordem lexicografica
        if (leitor == "#ORDEM")
            for (int i = 0; i < 26; i++)
                in >> ordem[i];
        // le o bloco de texto e adiciona as palavra à tabela
        else
            while (in >> leitor && leitor != "#ORDEM")
                texto.push_back(leitor);
    }

    // ordena a lista
    texto.sort();

    // imprime o vetor
    texto.print();

    // fecha o arquivo de entrada e de saida
    in.close();
    out.close(); 
}

#endif