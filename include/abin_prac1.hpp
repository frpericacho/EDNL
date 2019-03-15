#ifndef ABIN_PRAC1
#define ABIN_PRAC1
#include <cassert>
#include <iostream>
#include <fstream>
#include "abin.hpp"
#include <algorithm>

using std::istream;
using std::ostream;
using std::cin;
using std::cout;
using std::endl;


// y el maximo?
namespace Enlazada{
    /*template <typename T>
    int numN(const Abin<T> A){
    /*int difHijos;
    if(r == NULL)
        return 0;
    else{
        difHijos = desRec(hijoIzquierdo(n),A) - desRec(hijoDerecho(n),A);
        return max(difHijos,desRec(hijoIzquierdo,A),desRec(hijoDerech,A));
    }*/

    /*return fnumN(A.raiz(),A);
    }*/
    template <typename T>
    int fnumN(typename Abin<T>::nodo n, const Abin<T> A){
        if(n == Abin<T>::NODO_NULO){
            return 0;
        }else{
            return 1 + fnumN(A.hijoIzquierdo(n),A) + fnumN(A.hijoDerecho(n),A);
        }
    }

    template <typename T>
    int altura(const Abin<T> A){
        return faltura(A.raiz(),A);
    }

    template <typename T>
    int max(int a,int b){
        if(a < b)
            return b;
        else
            return a;
    }

    template <typename T>
    int faltura(typename Abin<T>::nodo n,const Abin<T> A){
        if(n == Abin<T>::NODO_NULO){
            return -1;
        }else{
            return 1 + max(faltura(A.hijoIzquierdo(n),A),faltura(A.hijoDerecho(n),A));
        }
    }

    template <typename T>
    int profundidad(const Abin<T> A){
        return fprofundidad(typename Abin<T>::nodo n, const Abin<T> A);
    }

    template <typename T>
    int fprofundidad(typename Abin<T>::nodo n, const Abin<T> A){
        if(n == Abin<T>::NODO_NULO)
            return 1;
        else{
            return 1 + fprofundidad(A.padreB(n),A);
        }
    }

    template <typename T>
    int desequilibrio(const Abin<T> A){
        return fdesequilibrio(typename Abin<T>::nodo n, const Abin<T> A);
    }

    template <typename T>
    int fdesequilibrio(typename Abin<T>::nodo n, const Abin<T> A){
        if(n == Abin<T>::NODO_NULO)
            return 0;
        else{
            return std::max({abs(altura(A.hijoIzqdoB())-altura(A.hijoDrchoB())),fdesequilibrio(A.hijoIzqdoB(),A),fdesequilibrio(A.hijoDrchoB(),A)})
        }
    }

    template <typename T>
    int buscaProf(const Abin<T> A){
        return fbuscaProf(typename Abin<T>::nodo n, const Abin<T> A)
    }

    template <typename T>
    int fbuscaProf(typename Abin<T>::nodo n, const Abin<T> A){
        if(n == Abin<T>::NODO_NULO)
            return 0;
        else{
            
        }
    }
}

#endif