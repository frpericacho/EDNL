#ifndef PRUEBA_HPP
#define PRUEBA_HPP
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

namespace Enlazada{

    //PRACTICA 1
    template<typename T>
    int numNodos(typename Abin<T>::Nodo n, const Abin<T> &A){
        if(n == Abin<T>::NODO_NULO)
            return 0;
        else{
            return 1 + numNodos(A.hijoIzqdoB(n),A) + numNodos(A.hijoDrchoB(n),A);
        }
    }

    template<typename T>
    int altura(const Abin<T> &A){
        return faltura(A.raizB(),A);
    }

    template<typename T>
    int faltura(typename Abin<T>::Nodo n, const Abin<T> &A){
        if(n == Abin<T>::NODO_NULO)
            return -1;
        else{
            return 1 + max(faltura(A.hijoDrchoB(n),A),faltura(A.hijoIzqdoB(n),A));
        }
    }

    template<typename T>
    int max(int a,int b){
        if(a < b)
            return b;
        else
            return a;
    }

    template<typename T>
    int profundidad(const Abin<T> &A){
        return fprofundidad(A.raizB(),A);
    }

    template<typename T>
    int fprofundidad(typename Abin<T>::Nodo n, const Abin<T> &A){
        if(n == Abin<T>::NODO_NULO)
            return 1;
        else{
            return 1 + fprofundidad(A.padreB(n),A);
        }

    }

    template<typename T>
    int desequilibrio(const Abin<T> &A){
        return fdesequilibrio(A.raizB(),A);
    }

    template<typename T>        // HACER EN LA PIZARRA PARA VER COMO FUNCIONA
    int fdesequilibrio(typename Abin<T>::Nodo n, const Abin<T> &A){
        if(n == Abin<T>::NODO_NULO)
            return 0;
        else{
            return std::max({abs(faltura(A.hijoDrchoB(n),A) - faltura(A.hijoIzqdoB(n),A)), fdesequilibrio(A.hijoDrchoB(n),A), fdesequilibrio(A.hijoIzqdoB(n),A)});
        }
    }

    //PRACTICA 2


    //EXAMENES PASADOS

    /*  ENUNCIADO EJERCICIO 1:
        Un nodo de un árbol se llama nostálgico si tiene más pasado que futuro, es decir, si tiene más
        ancestros (los cuales representan su pasado) que descendientes (que representan su futuro). Se define
        índice de nostalgia de un árbol como la ratio de nodos nostálgicos del árbol.
        Programe una función que devuelva el índice de nostalgia de un árbol general de elementos de un tipo
        genérico T.
    */
        

}

#endif