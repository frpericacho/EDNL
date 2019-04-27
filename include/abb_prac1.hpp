#ifndef ABB_PRAC1
#define ABB_PRAC1

#include <cassert>
#include <iostream>
#include <fstream>
#include "abb.hpp"
#include "abin.hpp"
#include <vector>
#include <algorithm>
#include <functional>

template <typename T>
void poda(T t, Abb<T> &A)
{
    if (!A.vacio())
        fpoda(A, t);
}

template <typename T>
void fpoda(Abb<T> &A, T t)
{
    if (!A.vacio())
    {
        if (A.elto > r->elto)
        {
            r->der.fpodar(A.elto);
        }
        else
        {
            if (A.elto < r->elto)
            {
                r->izq.podar(A.elto);
            }
            else
            {
                ~Abb();
            }
        }
    }
}

/*EJERCICIO 3*/

template <typename T>
void inOrder(const Abb<T> &a, std::function<void(const Abb<T> &)> func) {
  if (!a.vacio()) {
    inOrder(a.izquierdo(), func);
    func(a);function
    inOrder(a.derecho(), func);
  }
}

template <typename T> void equilibrar(Abb<T> &a) {
  std::vector<T> v;
  inOrder<T>(a, [&v](const Abb<T> &e) { v.push_back(e.elemento()); });
  a.~Abb();
  equilibrar_r(a, v, v.size(), 0);
}

template <typename T>
void equilibrar_r(Abb<T> &a, std::vector<T> &v, int n, int ini) {
  if (ini != n) {
    int pos{((n - ini) / 2) + ini};
    a.insertar(v[pos]);
    equilibrar_r(a, v, pos, ini);
    equilibrar_r(a, v, n, pos + 1);
  }
}

#endif