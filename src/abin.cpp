#include <algorithm>
#include <cassert>
#include "abin.hpp"
template <typename T>
Vectorial::Abin<T>::Abin(int max) : max_size{max}, size{0}, nodos{new celda[max]} {}

template <typename T>
Vectorial::Abin<T>::Abin(const Abin<T> &a) : nodos{new celda[a.max_size]}, max_size{a.max_size}, size{a.size}
{
    std::copy(a.nodos, a.nodos + (a.size - 1), nodos);
}

template <typename T>
void Vectorial::Abin<T>::insertarRaiz(const T &e)
{
    assert(size == 0);
    nodos[size++] = celda(e);
}

template <typename T>
void Vectorial::Abin<T>::insertarHijoIzquierdo(nodo n, const T &e)
{
    assert(n >= 0 && n < size);
    assert(nodos[n].h_izq == NODO_NULO);
    assert(size < max_size);
    nodos[n].h_izq = size;
    nodos[size++] = celda(e, n);
}

template <typename T>
void Vectorial::Abin<T>::insertarHijoDerecho(nodo n, const T &e)
{
    assert(n >= 0 && n < size);
    assert(nodos[n].h_dch == NODO_NULO);
    assert(size < max_size);
    nodos[n].h_dch = size;
    nodos[size++] = celda(e, n);
}

template <typename T>
void Vectorial::Abin<T>::eliminarHijoIzquierdo(nodo n)
{
    auto h_izq = nodos[n].h_izq;
    assert(n >= 0 && n < size);
    assert(h_izq != NODO_NULO);
    assert(nodos[h_izq].h_izq == NODO_NULO &&
           nodos[h_izq].h_dch == NODO_NULO);
    if (h_izq != size - 1)
    {
        nodos[h_izq] = nodos[size - 1];
        if (nodos[nodos[h_izq].padre].h_izq == size - 1)
            nodos[nodos[h_izq].padre].h_izq = h_izq;
        else
            nodos[nodos[h_izq].padre].h_dch = h_izq;
        if (nodos[h_izq].h_izq != NODO_NULO)
            nodos[nodos[h_izq].h_izq].padre = h_izq;
        if (nodos[h_izq].h_dch != NODO_NULO)
            nodos[nodos[h_izq].h_dch].padre = h_izq;
    }
    nodos[h_izq] = NODO_NULO;
    --size;
}

template <typename T>
void Vectorial::Abin<T>::eliminarHijoDerecho(nodo n)
{
    auto h_dch = nodos[n].h_dch;
    assert(n >= 0 && n < size);
    assert(h_dch != NODO_NULO);
    assert(nodos[h_dch].h_dch == NODO_NULO &&
           nodos[h_dch].h_izq == NODO_NULO);
    if (h_dch != size - 1)
    {
        nodos[h_dch] = nodos[size - 1];
        if (nodos[nodos[h_dch].padre].h_dch == size - 1)
            nodos[nodos[h_dch].padre].h_dch = h_dch;
        else
            nodos[nodos[h_dch].padre].h_izq = h_dch;
        if (nodos[h_dch].h_izq != NODO_NULO)
            nodos[nodos[h_dch].h_izq].padre = h_dch;
        if (nodos[h_dch].h_dch != NODO_NULO)
            nodos[nodos[h_dch].h_dch].padre = h_dch;
    }
    nodos[h_dch] = NODO_NULO;
    --size;
}

template <typename T>
inline void Vectorial::Abin<T>::eliminarRaiz()
{
    assert(size == 1);
    size = 0;
}

template <typename T>
inline const T &Vectorial::Abin<T>::elemento(nodo n) const
{
    assert(n >= 0 && n < size);
    return nodos[n].elemento;
}

template <typename T>
inline T &Vectorial::Abin<T>::elemento(nodo n)
{
    assert(n >= 0 && n < size);
    return nodos[n].elemento;
}

template <typename T>
inline typename Vectorial::Abin<T>::nodo Vectorial::Abin<T>::padre(nodo n) const
{
    assert(n >= 0 && n < size);
    return nodos[n].padre;
}

template <typename T>
inline typename Vectorial::Abin<T>::nodo Vectorial::Abin<T>::hijoIzquierdo(nodo n) const
{
    assert(n >= 0 && n < size);
    return nodos[n].h_izq;
}

template <typename T>
inline typename Vectorial::Abin<T>::nodo Vectorial::Abin<T>::hijoDerecho(nodo n) const
{
    assert(n >= 0 && n < size);
    return nodos[n].h_dch;
}

template <typename T>
Vectorial::Abin<T> &Vectorial::Abin<T>::operator=(const Abin<T> &a)
{
    if (this != &a)
    {
        if (max_size < a.max_size)
        {
            delete[] nodos;
            max_size = a.max_size;
            nodos = new celda[max_size];
        }
        size = a.size;
        std::copy(a.nodos, a.nodos + (a.size - 1), nodos);
    }
    return *this;
}