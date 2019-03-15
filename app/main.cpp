#include "abin.hpp"
#include "ioabin.hpp"
#include <iostream>

using namespace std;
using namespace Enlazada;

int main() {
  Abin<int> A;
  A.insertarRaizB(5);
  A.insertarHijoIzqdoB(A.raizB(), 20);
  A.insertarHijoDrchoB(A.raizB(), 21);
  cout << A.altura(A.raizB()) << endl;
  std::cout << A << std::endl;
}
