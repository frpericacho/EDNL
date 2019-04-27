#ifndef AGEN_PRAC2
#define AGEN_PRAC2

#include "agen_E-S.h"
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

//1. Implementa un subprograma que dado un árbol general nos calcule su grado. 
template <typename T>
void cal_gr(const Agen<T> &A){
    int cont = 0;
    if(!A.arbolVacio())
        cont = fun_cal_gr(A.raiz() , A);
}

template <typename T>
int cuenta(typename Agen<T>::nodo n, const Agen<T> &A){
    if(n != Agen<T>::NODO_NULO){
        int cont = 1;
        while (A.hermDrcho(n) != Agen<T>::NODO_NULO)
        {
            cont++;
            n = A.hermDrcho(n);
        }
        return cont;
    }
}

template <typename T>
int fun_cal_gr(typename Agen<T>::nodo n, const Agen<T> &A){
    if(n != Agen<T>::NODO_NULO){
        n = A.hijoIzqdo(n);
        while(n != Agen<T>::NODO_NULO){
            int maxi = cuenta(n, A);
            fun_cal_gr(n, A);
            return std::max(maxi, std::max(fun_cal_gr(A.hijoIzqdo(n),A), fun_cal_gr(A.hermDrcho(n),A)));
        }
    }
}

//2.Implementa un subprograma que dados un árbol y un nodo
//dentro de dicho árbol determine la profundidad de éste nodo en el árbol

template <typename T>
int profundidad(const Agen<T> &A, typename Agen<T>::nodo n){
    int cont = 0;
    
    while(n != A.raiz()){
        cont++;
        n = A.padre(n);
    }

    return cont;
}

/*4. Dado un árbol general de enteros A y un entero x, 
implementa un subprograma que realice la poda de A a partir de x.
Se asume que no hay elementos repetidos en A*/

// void llamada(Agen<int> &A, int aux){
//     if(!A.arbolVacio()){
//         poda(A, A.raiz(), aux);
//     }
// }

// void poda(Agen<int> &A, Agen<int>::Nodo n, int aux){
//     if(n != Agen<int>::NODO_NULO){
//         if(A.elemento(n) == aux)
//             A.destruirNodos(n);
//         else{
//             n = A.hijoIzqdo(n);
//             while(n != Agen<int>::NODO_NULO){
//                 poda(A,n,aux);
//                 n = A.hijoIzqdo(n);
//                 A.eliminarHijoIzqdo(n);
//             }
//         }
//     }
// }



#endif