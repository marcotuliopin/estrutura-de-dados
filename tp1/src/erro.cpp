#ifndef ERRO_CPP
#define ERRO_CPP

#include "erro.hpp"

/*
* Descricao: tratamento de erro em caso de falha na inicializacao de variavel
*/
void erro_init(const char *f, const int l)
{
    std::cout << "Erro na inicializaçao de variavel em: " << f << ":" << l << std::endl;
    abort();
}

/*
* Descricao: tratamento de erro em caso de chamada errada na linha de comando
* Retorna: 0, caso nao haja erro e 1 no contrario
*/
int erro_arg(const char *f, int args)
{
    if (args == 3)
        return 0;

    std::cout <<  "Erro na leitura de argumentos para a funcao em: " << f << std::endl;
    std::cout << "Formato correto: {programa} {arquivo de entrada} {arquivo de saida}" << std:: endl;
    return 1;
}

/*
* Descricao: tratamento de erro em caso de aposta invalida
* Modifica: table[i].money
* Retorna: 0, caso nao haja erro e 1 no contrario
*/
int erro_bet(int p, int pingo, player *table, std::ofstream &outfile)
{
    int player_bet = table[p].get_bet();

    // retorna a funcao se a aposta for valida
    if (player_bet >= pingo && player_bet + pingo <= table[p].get_money() && player_bet % 50 == 0)
        return 0;

    for (int i = 0; i < p; i++) // retorna o valor da aposta aos jogadores
        table[i].set_money((table[i].get_bet() + pingo)); 

    outfile << "0 0 I" << std::endl; // imprime mensagem de erro da rodada
    return 1;
}

/*
* Descricao: tratamento de erro em caso de abertura errada dos arquivos de entrada ou saida
* Retorna: 1 
*/
int erro_file(const char *f, const int l)
{
    std::cout << "Erro na abertura de arquivos em: " << f << ":" << l << std::endl;
    return 1;
}

/*
* Descricao: tratamento de erro em caso de numero invalido de jogadores na rodada
* Retorna: 1
*/
int erro_num()
{
    std::cout << "Jogadores invalidos foram encontrados." << std::endl;
    return 1;
}

#endif