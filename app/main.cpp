#include "abin.hpp"
#include "example.hpp"
#include <iostream>

using namespace Vectorial;

int main() {
  Abin<int> A(20);
  A.insertarRaiz(5);
  A.insertarHijoIzquierdo(A.raiz(), 20);
  A.insertarHijoDerecho(A.raiz(), 21);
  A.insertarHijoIzquierdo(1, 22);
  A.insertarHijoDerecho(1, 23);
  A.insertarHijoIzquierdo(2, 24);
  A.insertarHijoDerecho(2, 25);
  std::cout << A << std::endl;
  Dummy d = Dummy();
  return d.doSomething() ? 0 : -1;
}
