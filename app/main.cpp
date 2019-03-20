#include "abin.hpp"
#include "ioabin.hpp"
//#include "abin_prac2.hpp"
#include "pruebas.hpp"
#include "OP.hpp"
#include <iostream>

using namespace std;
using namespace Enlazada;

int main() {
  Abin<int> A,B;
  A.insertarRaizB(5);
  A.insertarHijoIzqdoB(A.raizB(), 20);
  A.insertarHijoDrchoB(A.raizB(), 21);
  A.insertarHijoDrchoB(A.hijoIzqdoB(A.raizB()),17);
  A.insertarHijoDrchoB(A.hijoDrchoB(A.raizB()),15);
  A.insertarHijoIzqdoB(A.hijoDrchoB(A.raizB()),16);
  A.insertarHijoIzqdoB(A.hijoDrchoB(A.hijoDrchoB(A.raizB())),10);
  
  B.insertarRaizB(5);
  B.insertarHijoIzqdoB(B.raizB(), 20);
  B.insertarHijoDrchoB(B.raizB(), 21);
  B.insertarHijoDrchoB(B.hijoDrchoB(B.raizB()),10);
  //B.insertarHijoIzqdoB(B.hijoDrchoB(B.raizB()),10);
//  cout << A.altura(A.raizB()) << endl;
//  cout << busca(A) << endl;
  std::cout << A << std::endl;
  //std::cout << rama(A) << std::endl;
  //rama(A);
}
