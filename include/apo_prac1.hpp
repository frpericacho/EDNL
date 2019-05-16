#ifndef APO_PRAC1
#define APO_PRAC1
#include <iostream>
#include "apo.hpp"
#include "abin.hpp"
#include "agen.hpp"

/*EJERCICIO 1*/
template <typename T>
Enlazada::Abin<T> fun1(const Enlazada::Abin<T> &A)
{
    Apo<T> P;
    if (!A.vacio())
        comprueba(A, P, A.raizB());
    return A;
}

template <typename T>
void comprueba(const Enlazada::Abin<T> &A, Apo<T> P, typename Enlazada::Abin<T>::nodo n)
{
    if (n == Enlazada::Abin<T>::NODO_NULO)
    {
        P.insertar(A.elemento(n));
        comprueba(A, P, A.hijoIzqdoB(n));
        comprueba(A, P, A.hijoDrchoB(n));
    }
}

/*EJERCICIO 2*/

/*EJERCICIO 4*/
template <typename T>
bool fun4(const Agen<T> &A)
{
    if (!A.vacio())
    {
        if (ternario(A, A.raiz()) != false)
            return true;
    }
    else
    {
        return false;
    }
}

template <typename T>
bool ternario(const Agen<T> &A, typename Agen<T>::nodo n)
{
    bool auxi = true;
    if (n != Agen<T>::NODO_NULO)
    {
        int aux = numHijos(A, n);
        if (aux != 3 || aux != 0){
            auxi = false;
        }
        n = A.hijoIzqdo(n);
        while (n != Agen<T>::NODO_NULO && auxi){
            auxi = ternario(A, n);
            n = A.hermDrcho(n);
        }
    }
    return auxi;
}

template <typename T>
int numHijos(const Agen<T> &A, typename Agen<T>::nodo n)
{
    int cont = 0;
    n = A.hijoIzqdo(n);
    while (n != Agen<T>::NODO_NULO)
    {
        cont++;
        n = A.hermDrcho(n);
    }
    return cont;
}

/*EJERCICIO 5*/

template<typename T>
bool llamada(const Agen<T> &A){
    if(!A.arbolVacio())
        return cuarter(A,A.raiz());
    else
        return false;
}

template<typename T>
bool cuarter(const Agen<T> &A, typename Agen<T>::nodo n){
    bool auxi = true;
    if(n != Agen<T>::NODO_NULO){
        int aux = numHijos(A,n);
        if(aux != 4 || aux != 0)
            auxi = false;
        n = A.hijoIzqdo(n);
        while(n != Agen<T>::NODO_NULO){
            auxi = cuarter(A, n);
            n = A.hermDrcho(n);
        }
    }
    return auxi;
}

template<typename T>
Agen<T> fun(const Agen<T> &A){
    if(!cuarter(A,A.raiz()))
        return Agen<T>::NODO_NULO;
    else{

    }
}

/*ALTURA AGEN*/

template<typename T>
int altura(const Agen<T> &A, typename Agen<T>::nodo n){
    if(n != Agen<T>::NODO_NULO){
        n = A.hijoIzqdo(n);
        
    }
}

#endif