#ifndef LISTA_HPP
#define LISTA_HPP

#include <string>

template <class T>
class node
{
    public:
        node(T v = T()) : valor{v}, prox(nullptr){};

        T valor;
        node* prox;
};

template <class T>
class lista
{
    public:
        lista() : primeiro(nullptr), tam{0}{};
        ~lista();
        void add(std::string& s);

        node<T>* primeiro;
        int tam;
};

#endif