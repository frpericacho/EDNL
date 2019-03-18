#ifndef ABIN_PRAC1
#define ABIN_PRAC1
#include <cassert>
#include <iostream>
#include <fstream>
#include "abin.hpp"
#include <algorithm>

using std::cin;
using std::cout;
using std::endl;
using std::istream;
using std::ostream;

namespace Enlazada
{

template <typename T>
int fnumN(typename Abin<T>::Nodo n, const Abin<T> &A)
{
    if (n == Abin<T>::NODO_NULO)
    {
        return 0;
    }
    else
    {
        return 1 + fnumN(A.hijoIzquierdo(n), A) + fnumN(A.hijoDerecho(n), A);
    }
}

template <typename T>
int altura(const Abin<T> &A)
{
    return faltura(A.raiz(), A);
}

template <typename T>
int max(int a, int b)
{
    if (a < b)
        return b;
    else
        return a;
}

template <typename T>
int faltura(typename Abin<T>::Nodo n, const Abin<T> &A)
{
    if (n == Abin<T>::NODO_NULO)
    {
        return -1;
    }
    else
    {
        return 1 + max(faltura(A.hijoIzquierdo(n), A), faltura(A.hijoDerecho(n), A));
    }
}

template <typename T>
int profundidad(const Abin<T> &A)
{
    return fprofundidad(A.raizB(), A);
}

template <typename T>
int fprofundidad(typename Abin<T>::Nodo n, const Abin<T> &A)
{
    if (n == Abin<T>::NODO_NULO)
        return 1;
    else
    {
        return 1 + fprofundidad(A.padreB(n), A);
    }
}

template <typename T>
int desequilibrio(const Abin<T> &A)
{
    return fdesequilibrio(A.raizB(), A);
}

template <typename T>
int fdesequilibrio(typename Abin<T>::Nodo n, const Abin<T> &A)
{
    if (n == Abin<T>::NODO_NULO)
        return 0;
    else
    {
        return std::max({abs(altura(A.hijoIzqdoB()) - altura(A.hijoDrchoB())), fdesequilibrio(A.hijoIzqdoB(), A), fdesequilibrio(A.hijoDrchoB(), A)});
    }
}

template <typename T>
int busca(const Abin<T> &A)
{
    if (A.arbolVacioB())
        return 0;
    else{
        return buscaProf(A.raizB(), A);    
    }
}

template <typename T>
int buscaProf(typename Abin<T>::Nodo n, const Abin<T> &A)
{
    if(A.altura(A.raizB()) - 1 == A.profundidad(n)){
        return (A.hijoIzqdoB(n) == Abin<T>::NODO_NULO && A.hijoDrchoB(n) == Abin<T>::NODO_NULO) || (A.hijoIzqdoB(n) != Abin<T>::NODO_NULO && A.hijoDrchoB(n) != Abin<T>::NODO_NULO);
    }
    else if(A.altura(A.hijoDrchoB(n)) > A.altura(A.hijoIzqdoB(n))){
        return buscaProf(A.hijoDrchoB(n), A);
    }else if(A.altura(A.hijoDrchoB(n)) < A.altura(A.hijoIzqdoB(n))){
        return buscaProf(A.hijoIzqdoB(n), A);
    }
        return buscaProf(A.hijoDrchoB(n),A) && buscaProf(A.hijoIzqdoB(n),A);
}

} // namespace Enlazada

#endif