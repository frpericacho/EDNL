#include <iostream>
//#include "grafos/grf_prac2.hpp"
//#include "grafos/io.hpp"
#include "abin_prac1.hpp"


//using namespace grafos::pmc;
using namespace std;
using namespace Enlazada;

typedef unsigned tCoste;

int main() {

  Abin<int> A,B;
  A.insertarRaizB(1);
  A.insertarHijoIzqdoB(A.raizB(), 0);
  A.insertarHijoDrchoB(A.raizB(), 1);
  A.insertarHijoDrchoB(A.hijoIzqdoB(A.raizB()),0);
  A.insertarHijoIzqdoB(A.hijoIzqdoB(A.raizB()),17);
  A.insertarHijoDrchoB(A.hijoDrchoB(A.raizB()),1);
  A.insertarHijoIzqdoB(A.hijoDrchoB(A.raizB()),0);
  A.insertarHijoIzqdoB(A.hijoDrchoB(A.hijoDrchoB(A.raizB())),1);
  A.insertarHijoDrchoB(A.hijoDrchoB(A.hijoDrchoB(A.raizB())),1);
  A.insertarHijoDrchoB(A.hijoIzqdoB(A.hijoDrchoB(A.raizB())),0);
  B.insertarHijoIzqdoB(B.hijoDrchoB(B.raizB()),10);
  cout << A.altura(A.raizB()) << endl;
  cout << busca(A) << endl;
  std::cout << A << std::endl;
  //std::cout << rebeldes(A) << std::endl;
//   std::cout <<
// primo(A.hijoIzqdoB(A.hijoDrchoB(A.raizB())),A.hijoDrchoB(A.hijoDrchoB(A.raizB())),A)
// << std::endl;
  // std::cout << nietos(A) << std::endl;
  // std::cout << rama(A) << std::endl;
  //rama(A);
  
  /*
   Agen<int> A;
   A.insertarRaiz(5);
   A.insertarHijoIzqdo(A.raiz(),1);
   A.insertarHijoIzqdo(A.raiz(),2);

   std::cout << A;
   */
  /*
    GrafoP<short> G("files/matriz.txt");
    bool aux = subvencion(G);
    if(aux)
      std::cout << "aciclico";
    else
      std::cout << "nope";
      */

  // GrafoP<short> G("files/aciclico.txt");

  // grafos::pmc::alg::arista<short> res = ejercicio1(G);

  // cout << "origen: " << res.orig << "\ndestino: " << res.dest << "\ncostes: " << res.coste <<  endl;

}