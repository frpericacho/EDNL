#ifndef ABIN_PRAC1
#define ABIN_PRAC1
#include <cassert>
#include <iostream>
#include <fstream>
#include "abin.hpp"

using std::istream;
using std::ostream;
using std::cin;
using std::cout;
using std::endl;


// y el maximo?
template <typename T>
int numN(const Abin<T> A){
   /*int difHijos;
   if(r == NULL)
      return 0;
   else{
      difHijos = desRec(hijoIzquierdo(n),A) - desRec(hijoDerecho(n),A);
      return max(difHijos,desRec(hijoIzquierdo,A),desRec(hijoDerech,A));
   }*/

   return fnumN(A.raiz(),A);
} 

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
int faltura(typename Abin<T>::nodo n,const Abin<T> A){
    if(n == Abin<T>::NODO_NULO){
        return 1;
    }else{
        return 1 + max(faltura(A.hijoIzquierdo(n),A),faltura(A.hijoDerecho(n),A));
    }
}

template <typename T>
int faltura(int a,int b){
    if(a < b)
        return b;
    else
        return a;
}

#endif