#ifndef PRUEBA_HPP
#define PRUEBA_HPP
#include <cassert>
#include <iostream>
#include <fstream>
#include "abin.hpp"
#include <algorithm>
#include "pila_dinamica.hpp"

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

    template<typename T>
    bool pseudo(const Abin<T> &A){
        return fpseudo(A.raizB(),A);
    }

    template<typename T>
    bool fpseudo(typename Abin<T>::Nodo n, const Abin<T> &A){
        if(A.altura(A.raizB()) - 1 == A.profundidad(n)){
            return (A.hijoDrchoB(n) == Abin<T>::NODO_NULO && A.hijoIzqdoB(n) == Abin<T>::NODO_NULO) || (A.hijoDrchoB(n) != Abin<T>::NODO_NULO && A.hijoIzqdoB(n) != Abin<T>::NODO_NULO);
        }
        else if(n == Abin<T>::NODO_NULO){
            return 0;
        }
        else{
            return fpseudo(A.hijoDrchoB(n),A) && fpseudo(A.hijoIzqdoB(n),A);
        }
    }

    //PRACTICA 2

    template<typename T>
    bool similar(const Abin<T> &A, const Abin<T> &B){
        if(A.arbolVacioB() && B.arbolVacioB())
            return true;
        else if(!A.arbolVacioB() && !B.arbolVacioB())
            return fsimilar(A.raizB(),A,B.raizB(),B);
        return false;
    }

    template<typename T>
    bool fsimilar(typename Abin<T>::Nodo na, const Abin<T> &A, typename Abin<T>::Nodo nb, const Abin<T> &B){
        if(na == Abin<T>::NODO_NULO && nb == Abin<T>::NODO_NULO)
            return true;
        else if(na != Abin<T>::NODO_NULO && nb != Abin<T>::NODO_NULO)
            return fsimilar(A.hijoIzqdoB(na),A,B.hijoIzqdoB(nb),B) && fsimilar(A.hijoDrchoB(na),A,B.hijoDrchoB(nb),B);
        return false;
    }

    template<typename T>
    Abin<T> reflejo(const Abin<T> &A){
        Abin<T> B;
        B.insertarRaizB(A.elemento(A.raizB()));
        freflejo(A.raizB(),A,B.raizB(),B);
        return B;
    }

    template<typename T>
    void freflejo(typename Abin<T>::Nodo na, const Abin<T> &A, typename Abin<T>::Nodo nb, const Abin<T> &B){
        if(A.hijoIzqdoB(na) != Abin<T>::NODO_NULO){
            B.insertarHijoDrchoB(nb,A.elemento(A.hijoIzqdoB(na)));
            freflejo(A.hijoIzqdoB(na),A,B.hijoDrchoB(nb),B);
        }else if(A.hijoDrchoB(na) != Abin<T>::NODO_NULO){
            B.insertarHijoIzqdoB(nb,A.elemento(A.hijoDrchoB(na)));
            freflejo(A.hijoDrchoB(na),A,B.hijoIzqdoB(nb),B);
        }
    }

    //cuantos nodos tienen tres nietos

    template<typename T>
    int nietos(const Abin<T> &A){
        if(A.arbolVacioB())
            return 0;
        else
            return fun_nietos(A.raizB(),A);
    }
    
    template<typename T>
    int fun_nietos(typename Abin<T>::Nodo n, const Abin<T> &A){
        if(n == Abin<T>::NODO_NULO)
            return 0;
        else if(A.hijoIzqdoB(n) != Abin<T>::NODO_NULO && A.hijoDrchoB(n) != Abin<T>::NODO_NULO)
            if(A.hijoIzqdoB(A.hijoIzqdoB(n)) != Abin<T>::NODO_NULO && A.hijoDrchoB(A.hijoIzqdoB(n)) != Abin<T>::NODO_NULO && (!(A.hijoDrchoB(A.hijoDrchoB(n)) != Abin<T>::NODO_NULO) != !(A.hijoIzqdoB(A.hijoDrchoB(n)) != Abin<T>::NODO_NULO)))
                return 1 + fun_nietos(A.hijoDrchoB(n),A) + fun_nietos(A.hijoIzqdoB(n),A);
            else if(A.hijoDrchoB(A.hijoDrchoB(n)) != Abin<T>::NODO_NULO && A.hijoIzqdoB(A.hijoDrchoB(n)) != Abin<T>::NODO_NULO && (!(A.hijoIzqdoB(A.hijoIzqdoB(n)) != Abin<T>::NODO_NULO) != !(A.hijoDrchoB(A.hijoIzqdoB(n)) != Abin<T>::NODO_NULO)))
                return 1 + fun_nietos(A.hijoDrchoB(n),A) + fun_nietos(A.hijoIzqdoB(n),A);
        return fun_nietos(A.hijoDrchoB(n),A) + fun_nietos(A.hijoIzqdoB(n),A);
    }

    //dado dos nodos comprobar que son primos
    template<typename T>
    bool primo(typename Abin<T>::Nodo na, typename Abin<T>::Nodo nb, const Abin<T> &A){
        if(A.arbolVacioB())
            return false;
        else
            return fun_primo(na,nb,A);
    }

    template<typename T>
    bool fun_primo(typename Abin<T>::Nodo na, typename Abin<T>::Nodo nb, const Abin<T> &A){
        if(na == Abin<T>::NODO_NULO || nb == Abin<T>::NODO_NULO)
            return false;
        else if(A.padreB(na) == A.padreB(nb))
            return false;
        else if(A.padreB(A.padreB(na)) == A.padreB(A.padreB(nb)) == Abin<T>::NODO_NULO)
            return false;
        else if(A.padreB(A.padreB(na)) == A.padreB(A.padreB(nb)))
            return true;
        return false;
    }

    /*6.- Se dice de nodo rebelde aquel cuyas ideas son diferentes a la de la mayoría de sus ancestros.
    Dado un árbol binario cualquiera calcular el número de nodos rebeldes de dicho árbol.
    Ejemplo si el nodo vale "1" y tiene tres ancestros que valen "1" y seis que valen "0", es rebelde.
    */
    template<typename T>
    int rebeldes(const Abin<T> &A){
        if(A.arbolVacioB())
            return 0;
        else
            return fun_rebeldes(A.raizB(),A);
    }

    template<typename T>
    int fun_rebeldes(typename Abin<T>::Nodo n, const Abin<T> &A){
        if(n == Abin<T>::NODO_NULO)
            return 0;
        if(comprueba(n,A.elemento(n),A))
            return 1 + fun_rebeldes(A.hijoIzqdoB(n),A) + fun_rebeldes(A.hijoDrchoB(n),A);
        return fun_rebeldes(A.hijoIzqdoB(n),A) + fun_rebeldes(A.hijoDrchoB(n),A);
    }

    template<typename T>
    bool comprueba(typename Abin<T>::Nodo n, T elemento, const Abin<T> &A){
        int tipo1=0, tipo2=0;
        while(n != Abin<T>::NODO_NULO){
            if(A.elemento(n) == elemento)
                tipo1++;
            else
                tipo2++;
            n = A.padreB(n);
        }
        return tipo1 < tipo2;
    }

}

#endif