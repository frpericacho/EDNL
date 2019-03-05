#include "abin.hpp"
#include "abin_E-S.h"
#include "example.hpp"
#include <iostream>

using namespace std;

int main() {
  Abin<int> A;
  A.insertarRaiz(5);
  A.insertarHijoIzquierdo(A.raiz(), 20);
  A.insertarHijoDerecho(A.raiz(), 21);
  std::cout << A << std::endl;
  Dummy d = Dummy();

  return d.doSomething() ? 0 : -1;
}
