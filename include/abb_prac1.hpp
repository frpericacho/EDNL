#ifndef ABB_PRAC1
#define ABB_PRAC1

#include <cassert>
#include <iostream>
#include <fstream>
#include "abb.hpp"
#include <algorithm>

template<typename T>
void poda(T t, Abb<T> &A){
    if(!A.vacio()){
        Abb<T>::nodo n = A.buscar(t);
        return fpoda(n,A);
    }
}

template<typename T>
void fpoda(typename Abb<T>::nodo n, Abb<T> &A){
    while(!A.drcho().vacio() && !A.izqdo().vacio()){
        A.eliminar();
    }
    A.eliminar();
} 

#endif