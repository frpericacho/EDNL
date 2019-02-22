#ifndef ABIN_VEC_HPP
#define ABIN_VEC_HPP
#include <algorithm>
#include <cassert>
#include <cstdio>
#include <iostream>
namespace Vectorial {
template <typename T> class Abin {
public:
  typedef int nodo;
  inline static const nodo NODO_NULO = -1;
  explicit Abin(int max);
  Abin(const Abin<T> &a);
  Abin<T> &operator=(const Abin<T> &a);
  void insertarRaiz(const T &e);
  void eliminarRaiz();
  void insertarHijoIzquierdo(nodo n, const T &e);
  void insertarHijoDerecho(nodo n, const T &e);
  void eliminarHijoIzquierdo(nodo n);
  void eliminarHijoDerecho(nodo n);
  bool vacio() const { return size == 0; }
  const T &elemento(nodo n) const;
  T &elemento(nodo n);
  nodo raiz() { return (size > 0) ? 0 : NODO_NULO; }
  nodo padre(nodo n) const;
  nodo hijoIzquierdo(nodo n) const;
  nodo hijoDerecho(nodo n) const;
  ~Abin() { delete[] nodos; }
  template <typename U>
  friend std::ostream &operator<<(std::ostream &os, const Abin<U> &a);

private:
  int max_size;
  int size;
  struct celda {
    celda() = default;
    explicit celda(const T &elto, nodo p = NODO_NULO, nodo h_d = NODO_NULO,
                   nodo h_i = NODO_NULO)
        : elemento{elto}, padre{p}, h_izq{h_i}, h_dch{h_d} {}
    T elemento;
    nodo padre, h_izq, h_dch;
  };
  celda *nodos;
  int printAbin(nodo n, bool isLeft, int offset, int depth, char[20][255]) const;
};

template <typename T>
Abin<T>::Abin(int max) : max_size{max}, size{0}, nodos{new celda[max]} {}

template <typename T>
Abin<T>::Abin(const Abin<T> &a)
    : nodos{new celda[a.max_size]}, max_size{a.max_size}, size{a.size} {
  std::copy(a.nodos, a.nodos + (a.size - 1), nodos);
}

template <typename T> void Abin<T>::insertarRaiz(const T &e) {
  assert(size == 0);
  nodos[size++] = celda(e);
}

template <typename T> void Abin<T>::insertarHijoIzquierdo(nodo n, const T &e) {
  assert(n >= 0 && n < size);
  assert(nodos[n].h_izq == NODO_NULO);
  assert(size < max_size);
  nodos[n].h_izq = size;
  nodos[size++] = celda(e, n);
}

template <typename T> void Abin<T>::insertarHijoDerecho(nodo n, const T &e) {
  assert(n >= 0 && n < size);
  assert(nodos[n].h_dch == NODO_NULO);
  assert(size < max_size);
  nodos[n].h_dch = size;
  nodos[size++] = celda(e, n);
}

template <typename T> void Abin<T>::eliminarHijoIzquierdo(nodo n) {
  auto h_izq = nodos[n].h_izq;
  assert(n >= 0 && n < size);
  assert(h_izq != NODO_NULO);
  assert(nodos[h_izq].h_izq == NODO_NULO && nodos[h_izq].h_dch == NODO_NULO);
  if (h_izq != size - 1) {
    nodos[h_izq] = nodos[size - 1];
    if (nodos[nodos[h_izq].padre].h_izq == size - 1)
      nodos[nodos[h_izq].padre].h_izq = h_izq;
    else
      nodos[nodos[h_izq].padre].h_dch = h_izq;
    if (nodos[h_izq].h_izq != NODO_NULO)
      nodos[nodos[h_izq].h_izq].padre = h_izq;
    if (nodos[h_izq].h_dch != NODO_NULO)
      nodos[nodos[h_izq].h_dch].padre = h_izq;
  }
  nodos[h_izq] = NODO_NULO;
  --size;
}

template <typename T> void Abin<T>::eliminarHijoDerecho(nodo n) {
  auto h_dch = nodos[n].h_dch;
  assert(n >= 0 && n < size);
  assert(h_dch != NODO_NULO);
  assert(nodos[h_dch].h_dch == NODO_NULO && nodos[h_dch].h_izq == NODO_NULO);
  if (h_dch != size - 1) {
    nodos[h_dch] = nodos[size - 1];
    if (nodos[nodos[h_dch].padre].h_dch == size - 1)
      nodos[nodos[h_dch].padre].h_dch = h_dch;
    else
      nodos[nodos[h_dch].padre].h_izq = h_dch;
    if (nodos[h_dch].h_izq != NODO_NULO)
      nodos[nodos[h_dch].h_izq].padre = h_dch;
    if (nodos[h_dch].h_dch != NODO_NULO)
      nodos[nodos[h_dch].h_dch].padre = h_dch;
  }
  nodos[h_dch] = NODO_NULO;
  --size;
}

template <typename T> inline void Abin<T>::eliminarRaiz() {
  assert(size == 1);
  size = 0;
}

template <typename T> inline const T &Abin<T>::elemento(nodo n) const {
  assert(n >= 0 && n < size);
  return nodos[n].elemento;
}

template <typename T> inline T &Abin<T>::elemento(nodo n) {
  assert(n >= 0 && n < size);
  return nodos[n].elemento;
}

template <typename T>
inline typename Abin<T>::nodo Abin<T>::padre(nodo n) const {
  assert(n >= 0 && n < size);
  return nodos[n].padre;
}

template <typename T>
inline typename Abin<T>::nodo Abin<T>::hijoIzquierdo(nodo n) const {
  assert(n >= 0 && n < size);
  return nodos[n].h_izq;
}

template <typename T>
inline typename Abin<T>::nodo Abin<T>::hijoDerecho(nodo n) const {
  assert(n >= 0 && n < size);
  return nodos[n].h_dch;
}

template <typename T> Abin<T> &Abin<T>::operator=(const Abin<T> &a) {
  if (this != &a) {
    if (max_size < a.max_size) {
      delete[] nodos;
      max_size = a.max_size;
      nodos = new celda[max_size];
    }
    size = a.size;
    std::copy(a.nodos, a.nodos + (a.size - 1), nodos);
  }
  return *this;
}

template <typename T>
int Abin<T>::printAbin(nodo n, bool isLeft, int offset, int depth,
                       char s[20][255]) const {
  char b[20];
  int width{5};
  if (n == -1) {
    return 0;
  }
  sprintf(b, "(%03d)", nodos[n].elemento);
  int left = printAbin(nodos[n].h_izq, true, offset, depth + 1, s);
  int right =
      printAbin(nodos[n].h_dch, false, offset + left + width, depth + 1, s);
  for (int i = 0; i < width; i++) {
    s[2 * depth][offset + left + i] = b[i];
  }
  if (depth && isLeft) {
    for (int i = 0; i < width + right; i++) {
      s[2 * depth - 1][offset + left + width / 2 + i] = '-';
    }

    s[2 * depth - 1][offset + left + width / 2] = '+';
    s[2 * depth - 1][offset + left + width + right + width / 2] = '+';

  } else if (depth && !isLeft) {

    for (int i = 0; i < left + width; i++) {
      s[2 * depth - 1][offset - width / 2 + i] = '-';
    }
    s[2 * depth - 1][offset + left + width / 2] = '+';
    s[2 * depth - 1][offset - width / 2 - 1] = '+';
  }
  return left + width + right;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const Abin<T> &a) {
  char s[20][255];
  for (int i = 0; i < 20; i++) {
    sprintf(s[i], "%80s", " ");
  }
  a.printAbin(0, 0, 0, 0, s);
  for (int i = 0; i < 20; i++) {
    os << s[i] << std::endl;
  }
  return os;
}
} // namespace Vectorial
#endif