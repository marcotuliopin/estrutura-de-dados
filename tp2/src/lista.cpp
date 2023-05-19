#ifndef LISTA_CPP
#define LISTA_CPP

#include "lista.hpp"

template<class T>
void lista<T>::add(std::string& s)
{
    node<std::string>* n = new node(s);

    // se a lista estiver vazia, a inicia
    if (tam == 0)
    {
        primeiro = n;
        tam++;
        return;
    }

    node<T>* it = primeiro; // iterador

    // encontra o fim da lista
    while (it->prox != nullptr)
        it = it->prox;
    
    it->prox = n; // adiciona o node a lista
    tam++; 
}

template <class T>
lista<T>::~lista()
{
    node<T>* it = primeiro->prox;
    while (it != nullptr)
    {
        delete primeiro;
        primeiro = it;
        it = it->prox;
    }
    delete primeiro;
}

#endif