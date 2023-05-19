/*
Arquivo: functions.cpp
Conteudo: implementacao das funcoes de functions.hpp
Autor: Marco Tulio Tristao
Data de criacao: 27-05-2022 - arquivo criado
                 31-05-2022 - comenta o codigo
                 02-06-2022 - criacao do TAD hand
                 03-06-2022 - separacao das funcoes do main para functions.cpp
*/

#ifndef FUNCTIONS_CPP
#define FUNCTIONS_CPP

#include "functions.hpp"

// dicionario de jogadas e suas siglas
std::string HANDS[] = {"HC", "OP", "TP", "TK", "S", "F", "FH", "FK" , "SF", "RSF"};
int TOTAL_PLAYERS;
extern std::ifstream infile; // arquivo de entrada
extern std::ofstream outfile; // arquivo de saida

/*
* Descricao: organiza em alto nivel o esquema de uma rodada de poker. A partir do numero de jogadores,
* direciona o codigo para as funcoes que darao continuidade a rodada
*/
void rodada(const int &num_players, const int &pingo, player *table)
{
    bool participantes[num_players]; // lista de jogadores que participam da rodada
    memset(participantes, false, TOTAL_PLAYERS);

    // le os dados dos jogadores da rodada
    for (int i = 0; i < num_players; i++)
    {
        int aux = parse_input(i, table);
        participantes[aux] = true;
    }
    // computa o resultado da rodada
    play(participantes, num_players, pingo, table);
}

/*
* Descricao: realiza as rodadas do jogo, encontrando os vencedores e o montante de cada jogador apos a rodada
* Requer: participantes (lista com os jogadores que participam da rodada), num_players (numero de jogadores que participam da rodada),
* pingo (aposta minima), table (lista de jogadores)
* Modifica: p.money para todos os jogadores p
* Retorna: status de validez da rodada
*/
int play(bool *participantes, const int &num_players, const int &pingo, player *table)
{
    int maior; // jogada mais valiosa
    int bet; // montante de apostas
    int winner[num_players]; // lista de vencedores
    int num_winners; // numero de vencedores

    memset(winner, -1, num_players * sizeof(int)); 
    
    // encontra a maior hand na jogada
    maior = better_hand(participantes, table);

    // encontra o montante total de apostas da rodada
    bet = create_round_bet(participantes, pingo, table);

    // se a aposta for invalida
    if (!bet)
        return 1;

    // encontra empates
    num_winners = 0;
    for (int i = 0; i < TOTAL_PLAYERS; i++)
    {
        if (!participantes[i])
            continue;
        // se o jogador tiver a maior jogada da rodada
        if (table[i].hand.get_value() == maior)
        {
            winner[num_winners] = i;
            num_winners++;
        }     
    };

    // desempata candidatos a vencedores
    for (int i = 0; i < num_players; i++)
    {
        if (winner[i] < 0) // pula o loop caso ja tenha sido tirado no desempate
            continue;
        for (int j = i + 1; j < num_players; j++)
        {
            if (winner[j] < 0) // pula o loop caso ja tenha sido tirado no desempate
                continue;
            // acha jogador  a ser tirado dos vencedores
            int aux = desempata(winner[i], winner[j], table);
            // desempata se for possivel
            if (aux > 0)
            {
                if (aux == 1)
                    winner[i] = -1;
                else    
                    winner[j] = -1;
                num_winners--;
            }
        }
    }
    
    // divide o montante das apostas para os vencedores
    bet /= num_winners;
    for (int i = 0; i < num_players; i++)
    {
        if (winner[i] < 0)
            continue;    
        table[winner[i]].set_money(bet);
    }

    // imprime os vencedores da rodada;
    outfile << num_winners << " " << bet << " " << HANDS[maior - 1] << std::endl;
    print_winner(num_players, winner, table);

    return 0;
}

/*
* Descricao: analisa a hand de cada jogador e retorna a jogada mais valiosa da partida. 
* Requer: participantes (lista com os jogadores que participam da rodada), table (lista de jogadores)
* Retorna: valor da maior hand
*/
int better_hand(bool *participantes, player *table)
{
    int maior = 0; // maior hand da rodada

    for (int i = 0; i < TOTAL_PLAYERS; i++)
    {
        if (!participantes[i]) // pula o loop se o jogador nao participa da rodada
            continue;
        int valid_hand = table[i].hand.get_value();
        maior = std::max(maior, valid_hand); 
    }
    return maior;
}

/*
* Descricao: cria o montante de apostas da rodada a partir da aposta de cada participante e do pingo de todos os jogadores.
* Requer: participantes (lista com os jogadores que participam da rodada), pingo (aposta minima), table (lista de jogadores)
* Retorna: valor da aposta da rodada
*/
int create_round_bet(bool *participantes, const int &pingo, player *table)
{
    int bet = TOTAL_PLAYERS*pingo; // aposta da rodada

    for (int i = 0; i < TOTAL_PLAYERS; i++)
    {
        if (!participantes[i]) // pula o loop caso o jogador nao participe da rodada
            continue;
        // checa o valor da aposta do jogador
        int player_bet = table[i].get_bet(); 
        // se a rodada for invalida, retorna o valor da aposta aos jogadores
        if(erro_bet(i, pingo, table, outfile))
            return 0;
        table[i].set_money(-player_bet);

        table[i].set_money(-pingo); // remove a contribuicao minima de cada jogador
        bet += player_bet; 
    }
    return bet;
}

/*
* Descricao: imprime o estado final do dinheiro de cada jogador apos todas as rodadas. A impressao é feita em ordem descendente
* do dinheiro dos jogadores
* Requer: table (lista de jogadores)
*/
void print_result(player *table)
{
    outfile << std::endl << "####" << std::endl;
    int maior;
    for (int i = 0; i < TOTAL_PLAYERS; i++)
    {
        maior = i;
        for (int j = 0; j < TOTAL_PLAYERS; j++)
        {
            if (table[maior].get_money() < table[j].get_money())
                maior = j;
        }
        outfile << table[maior].get_name() << " " << table[maior].get_money() << std::endl;
        table[maior].set_money(-table[maior].get_money());
    }
}

/*
* Descricao: imprime o nome de cada vencedor da rodada
* Requer: num_players (numero de jogadores na rodada), winner (lista com os indices dos vencedores da rodada), table (lista de jogadores)
*/
void print_winner(int num_players, int *winner, player *table)
{
    for (int i = 0; i < num_players; i++)
    {
        while (winner[i] >= 0)
        {
            int menor = i;
            for (int j = 0; j < num_players; j++)
            {
                if (winner[j] < 0)
                    continue;
                if (table[winner[j]].get_name() < table[winner[i]].get_name())
                    menor = j;
            }
            outfile << table[winner[menor]].get_name() << std::endl; 
            winner[menor] = -1;
        }
    }
}

/*
* Descricao: busca remover um dos jogadores da lista de vencedores usando os criterios de desempate
* Requer: f (indice de um jogador), s (indice do outro jogador), table (lista de jogadores)
* Modifica: f.main_tie_breaker, f.sec_tie_breaker, f.third_tie_breaker, s.main_tie_breaker, s.sec_tie_breaker, s.third_tie_breaker
* Retorna: o numero do jogador a ser desempatado ou -1 caso nao haja desempate
*/
int desempata(const int &f, const int &s, player *table)
{
    // criterios de desempate dos jogadores
    int first_tb[3]; 
    int second_tb[3];

    // le os criterios de desempate
    table[f].hand.get_tb(first_tb);
    table[s].hand.get_tb(second_tb);

    // compara os criterios
    for (int i = 0; i < 3; i++)
    {
        if (first_tb[i] != second_tb[i])
            return (first_tb[i] < second_tb[i])? 1 : 2;
    }
    // se todos os criterios forem iguais
    return -1;
}

/*
* Descricao: encontra de que jogador os dados sao e os interpreta
* Requer: p (numero da iteracao em que foi feito o chamado), table (lista de jogadores)
* Modifica: p.hand[], p.hand_value, p.current_bet
* Retorna: o numero do jogador cujos dados foram lidos
*/
int parse_input(int p, player *table)
{
    std::string aux; // auxilio para pegar os dados da entrada
    std::string name; // nome do jogador 

    // le o nome do jogador 
    infile >> aux;
    name += aux;
    infile >> aux;
    while(!std::isdigit(aux[0]))
    {
        name += " " + aux;
        infile >> aux;
    }
    while (!std::isdigit(aux[0]));

    // inicializa o nome do jogador caso seja a primeira rodada
    if (table[p].get_name().empty()) 
        table[p].set_name(name);
    
    // encontra a que jogador a linha se refere
    p = -1;
    for (int k = 0; k < TOTAL_PLAYERS; k++) 
    {
        if (name == table[k].get_name())
            p = k;
    }
    if (p == -1)
        erro_num();

    table[p].set_bet(std::stoi(aux));
    table[p].set_hand(infile);

    return p;
}

#endif