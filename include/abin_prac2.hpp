#ifndef ABIN_PRAC2
#define ABIN_PRAC2
#include <cassert>
#include <iostream>
#include <fstream>
#include "abin.hpp"
#include <algorithm>
#include "OP.hpp"

using std::cin;
using std::cout;
using std::endl;
using std::istream;
using std::ostream;

namespace Enlazada
{

template <typename T>
int similar(const Abin<T> &A, const Abin<T> &B)
{
    if (A.arbolVacioB() && B.arbolVacioB())
        return true;
    else if (!A.arbolVacioB() && !B.arbolVacioB())
        return fsimilar(A.raizB(), A, B.raizB(), B);
    return false;
}

template <typename T>
int fsimilar(typename Abin<T>::Nodo n, const Abin<T> &A, typename Abin<T>::Nodo n2, const Abin<T> &B)
{
    if (A.raizB() == Abin<T>::NODO_NULO && B.raizB() == Abin<T>::NODO_NULO)
    {
        return true;
    }
    else if (A.raizB() != Abin<T>::NODO_NULO && B.raizB() != Abin<T>::NODO_NULO)
    {
        return fsimilar(A.hijoIzqdoB(n), A, B.hijoIzqdoB(n2), B) && fsimilar(A.hijoDrchoB(n), A, B.hijoDrchoB(n2), B);
    }
    return false;
}

template <typename T>
Abin<T> espejo(const Abin<T> &A)
{
    Abin<T> B;
    B.insertarRaizB(A.elemento(A.raizB()));
    fespejo(B, B.raizB(), A, A.raizB());
    return B;
}

template <typename T>
void fespejo(Abin<T> &B, typename Abin<T>::Nodo na, const Abin<T> &A, typename Abin<T>::Nodo nb)
{
    if (A.hijoIzqdoB(na) != Abin<T>::NODO_NULO)
    {
        B.insertarHijoDrchoB(nb, A.elemento(A.hijoIzqdoB(na)));
        fespejo(B, B.hijoDrchoB(nb), A, A.hijoIzqdoB(na));
    }
    else if (A.hijoDrchoB(na) != Abin<T>::NODO_NULO)
    {
        B.insertarHijoIzqdoB(nb, A.elemento(A.hijoDrchoB(na)));
        fespejo(B, B.hijoIzqdoB(nb), A, A.hijoDrchoB(na));
    }
}

double foperacion(Abin<Op>::Nodo n, const Abin<Op> &A)
{
    if (A.hijoDrchoB(n) == Abin<Op>::NODO_NULO && A.hijoIzqdoB(n) == Abin<Op>::NODO_NULO)
        return A.elemento(n).operando;
    else
    {
        switch (A.elemento(n).operador)
        {
        case '+':
            return foperacion(A.hijoIzqdoB(n), A) + foperacion(A.hijoDrchoB(n), A);
        case '-':
            return foperacion(A.hijoIzqdoB(n), A) - foperacion(A.hijoDrchoB(n), A);
        case '/':
            return foperacion(A.hijoIzqdoB(n), A) / foperacion(A.hijoDrchoB(n), A);
        case '*':
            return foperacion(A.hijoIzqdoB(n), A) * foperacion(A.hijoDrchoB(n), A);
        default:
            return 0;
        }
    }
}

double operacion(const Abin<Op> &A)
{
    return foperacion(A.raizB(), A);
}



} // namespace Enlazada

#endif