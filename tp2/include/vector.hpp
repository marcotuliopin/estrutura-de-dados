#ifndef VECTOR_HPP
#define VECTOR_HPP

template<class T>
class vector
{
    private:
        T* item;
        int tam;
        int capacidade;
    public:
        inline vector();
        inline ~vector();
        inline const int end();
        void push_back(T novo);
        void sort();
        void sort(int inicio, int fim);
        void print();
};

#endif