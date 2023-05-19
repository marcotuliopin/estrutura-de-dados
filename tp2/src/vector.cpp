#ifndef VECTOR_CPP
#define VECTOR_CPP

#include "vector.hpp"

template<class T>
inline vector<T>::vector() : item(new T), tam(0), capacidade(1) {}

template<class T>
inline vector<T>::~vector()
{
    delete item;
}

template<class T>
inline const int vector<T>::end()
{
    return tam;
}

template<class T>
void vector<T>::push_back(T novo)
{
    // caso o vetor esteja cheio
    if (tam == capacidade)
    {
        // cria um vetor com o dobro da capacidade
        capacidade *= 2;
        T* aux = new T[capacidade];

        // copia os elementos do vetor antigo para o novo
        for (int i = 0; i < capacidade/2; i++)
            aux[i] = item[i];

        // define o ponteiro item para o novo vetor
        delete item;
        item = aux;
    }

    // coloca o novo elemento no vetor
    aux[tam] = novo;
    tam++;
}

template<class T>
void vector<T>::sort()
{

}

template<class T>
void vector<T>::sort(int inicio, int fim)
{

}

#endif