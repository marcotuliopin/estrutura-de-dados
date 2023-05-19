/*
Arquivo: Hand.cpp
Conteudo: implementacao do TAD Hand 
Autor: Marco Tulio Tristao
Data de criacao: 27-05-2022 - arquivo criado
                 31-05-2022 - comenta o codigo
                 02-06-2022 - criacao do TAD hand
                 03-06-2022 - separacao das funcoes do main para functions.cpp
*/

#ifndef HAND_CPP
#define HAND_CPP

#include "Hand.hpp"

/*
* Descricao: inicializa o objeto hand
* Modifica: hand
*/
Hand::Hand() : value{-1}
{
    tiebreaker[0] = -1;
    tiebreaker[1] = -1;
    tiebreaker[2] = -1;
};

/*
* Descricao: le a entrada referente as cartas do jogador e as guarda no vetor card[].
*   Apos isso, é chamado funcoes que ordenam o vetor e definem o valor da jogada.
* Modifica: hand.card, hand.value
*/
void Hand::set_card(std::ifstream &infile)
{
    char c;
    // le as cartas do jogador
    for (int i = 0; i < HANDTAM; i++)
    {
        infile >> c;
        card[i][0] = c - '0';
        if (infile >> c && isdigit(c))
        {
            card[i][0] = card[i][0]*10 + c - '0';
            infile >> c;
        }
        card[i][1] = c;
    }

    // inicializa os criterios de desempate
    for (int i = 0; i < 3; i++)
        tiebreaker[i] = -1;

    // ordena a mao em ordem crescente do valor das cartas
    sort();    
    // define qual a jogada de maior valor do jogador
    set_value();
}

/*
* Descricao: ordena a mao do jogador em ordem crescente do valor das cartas
* Modifica: hand.card
*/
void Hand::sort()
{
    int menor;
    int aux;
    for (int i = 0; i < HANDTAM; i++)
    {
        menor = i;
        for (int j = i + 1; j < HANDTAM; j++)
        {
            if (card[menor][0] > card[j][0]) 
                menor = j;
        }
        // troca a menor carta e a da posicao i de lugar
        for (int j = 0; j < 2; j++)
        {
            aux = card[i][j];
            card[i][j] = card[menor][j];
            card[menor][j] = aux;
        }
    }
}


/*
* Descricao: categoriza a mao do jogador dentre as possiveis jogadas no poker
* Modifica: hand.value
*/
void Hand::set_value()
{
    // checa se as cartas formam uma sequencia crescente
    int biggest_sequence = check_sequence();
    // checa se todas as cartas pertencem ao mesmo naipe
    bool same_suits = check_suits();
    // checa o numero maximo de cartas iguais 
    int same_number = check_numbers();
    // checa o numero de cartas diferentes
    int dif_number = different_numbers();


    // todas do mesmo naipe e cinco cartas em uma sequencia crescente
    if (biggest_sequence == 5 && same_suits)
    {
        if (card[0][0] == 1 && card[1][0] == 10) // é RSF se for a maior sequencia possivel
            value =  10;
        else  // é SF se começar a sequencia antes de 10
            value =  9;
    }
    if (same_number >= 4) // é FK 
        value = 8;
    else if (same_number == 3 && dif_number == 2) // é FH
        value = 7;
    else if (biggest_sequence < 5 && same_suits) // é F
        value = 6;
    else if (biggest_sequence == 5) // é S
        value = 5;
    else if (same_number == 3 && dif_number == 3) // é TK
        value = 4;
    else if (same_number == 2 && dif_number == 3) // é TP
        value = 3;
    else if (same_number == 2 && dif_number == 4) // é OP
        value = 2;
    else // é HC
        value = 1;
}

/*
* Descricao: retorna o valor da jogada
*/
int Hand::get_value()
{
    return value;
}

/*
* Descricao: verifica se as cartas formam uma sequencia crescente e qual o comprimento
* dessa sequencia
* Retorna: comprimento da maior sequencia crescente
*/
int Hand::check_sequence()
{
    int biggest_sequence = 1;
    int sequence = 1;
    for (int i = 1; i < HANDTAM; i++)
    {
        if (card[i][0] != card[i - 1][0] + 1)
            sequence = 0;
        sequence++;    
        biggest_sequence = std::max(biggest_sequence, sequence);
    }
    return biggest_sequence;
}

/*
* Descricao: checa se todas as cartas sao do mesmo naipe
* Retorna: se todas as cartas pertencem ao mesmo naipe
*/
bool Hand::check_suits()
{
    bool same_suits = true;
    int f_suit = card[0][1];
    for (int i = 1; i < HANDTAM; i++)
    {
        if (card[i][1] != f_suit)
        {
            same_suits = false;
            break;
        }
    }
    return same_suits;
}

/*
* Descricao: checa o numero maximo de cartas iguais (par, tripla, etc)
* Retorna: o maior numero de cartas iguais
*/
int Hand::check_numbers()
{
    int same_number = 1;
    int sequence = 1;
    for (int i = 1; i < HANDTAM; i++)
    {
        if (card[i][0] != card[i - 1][0])
            sequence = 0;
        sequence++;
        same_number = std::max(same_number, sequence);
    }
    return same_number;
}

/*
* Descricao: descobre quantidade de cartas com diferentes numeros. Por exemplo, uma mao
* com um par teria 4 cartas diferentes.
* Retorna: o numero de cartas diferentes
*/
int Hand::different_numbers()
{
    int dif_number = 5;
    for (int i = 1; i < HANDTAM; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (card[i][0] == card[j][0])
            {
                dif_number--;
                break;
            }
        }
    }
    return dif_number;
}

/*
* Descricao: interpreta a mao do jogador e define seus criterios de desempate de acordo com a jogada que ele tem
* Modifica: hand.tiebreaker
*/
void Hand::set_tb()
{
    switch (value)
    {
        // nao se desempata dois RSF
        case 10:
            tiebreaker[0] = -1;
        // em caso de SF ganha o que tiver a sequecia maior
        case 9:
            tiebreaker[0] = card[0][0];
            break;
        // FK desempata pela maior quadra, ou a maior carta que nao faz parte da quadra
        case 8:
            tiebreaker[0] = card[1][0];
            if (card[0][0] != tiebreaker[0])
                tiebreaker[1] = card[0][0];
            else
                tiebreaker[1] = card[HANDTAM - 1][0];
            break;
        // FH sao desempatados pela tripla mais alta, ou pelo par mais alto
        case 7:
            tiebreaker[0] = card[2][0];
            if (card[1][0] != tiebreaker[0])
                tiebreaker[1] = card[1][0];
            else   
                tiebreaker[1] = card[HANDTAM - 1][0];
            break;
        // F, S e HC sao desempatados pela carta de maior valor
        case 6: 
        case 5:
        case 1:
            tiebreaker[0] = card[HANDTAM - 1][0];
            break;
        // TK sao desempatados pela maior tripla, ou pela maior carta fora da tripla
        case 4:
            tiebreaker[0] = card[2][0];
            if (card[HANDTAM - 1][0] != tiebreaker[0])
                tiebreaker[1] = card[HANDTAM - 1][0];
            else
                tiebreaker[1] = card[1][0];
            break;
        // TP sao desempatados pelos maiores pares, ou pela maior carta que nao tem par
        case 3:
            tiebreaker[0] = card[HANDTAM - 2][0]; 
            tiebreaker[1] = card[1][0];
            if (card[0][0] != tiebreaker[1])
                tiebreaker[2] = card[0][0];
            else if (card[HANDTAM - 1][0] != tiebreaker[0])
                tiebreaker[2] = card[HANDTAM - 1][0];
            else    
                tiebreaker[2] = card[2][0];
            break;
        // OP sao desempatados pelo maior par, ou pela maior carta
        case 2:
            if (card[1][0] == card[0][0] || card[1][0] == card[2][0])
            {
                tiebreaker[0] = card[1][0];
                tiebreaker[1] = card[HANDTAM - 1][0];
            }
            else
            {
                tiebreaker[0] = card[3][0];
                if (card[HANDTAM - 1][0] == tiebreaker[0])
                    tiebreaker[1] = card[2][0];     
                else
                    tiebreaker[1] = card[HANDTAM - 1][0];
            }
    }
}

/*
* Descricao: retorna os criterios de desempate do jogador
* Requer: e (vetor de inteiros que armazenara os criterios de desempate)
* Modifica: e
*/
int* Hand::get_tb(int* e)
{
    // define os criterios de desempate
    set_tb();
    // copia os criterios para o vetor e
    e[0] = tiebreaker[0];
    e[1] = tiebreaker[1];
    e[2] = tiebreaker[2];
    return e;
}

#endif