#ifndef ABIN_VEC_HPP
#define ABIN_VEC_HPP
#include <algorithm>
#include <cassert>
#include <cstdio>
#include <iostream>
namespace Vectorial {
template <typename T> class Abin {
public:
  using Nodo = int;
  inline static const Nodo NODO_NULO = -1;
  explicit Abin(int max);
  Abin(const Abin<T> &a);
  Abin<T> &operator=(const Abin<T> &a);
  void insertarRaiz(const T &e);
  void insertarHijoIzquierdo(Nodo n, const T &e);
  void insertarHijoDerecho(Nodo n, const T &e);
  void eliminarRaiz();
  void eliminarHijoIzquierdo(Nodo n);
  void eliminarHijoDerecho(Nodo n);
  bool vacio() const { return size == 0; }
  const T &elemento(Nodo n) const;
  T &elemento(Nodo n);
  Nodo _raiz() { return (size > 0) ? 0 : NODO_NULO; }
  Nodo padre(Nodo n) const;
  Nodo hijoIzquierdo(Nodo n) const;
  Nodo hijoDerecho(Nodo n) const;
  ~Abin() { delete[] nodos; }
  template <typename U>
  friend std::ostream &operator<<(std::ostream &os, const Abin<U> &a);

private:
  int max_size;
  int size;
  struct Celda {
    Celda() = default;
    explicit Celda(const T &elto, Nodo p = NODO_NULO, Nodo h_d = NODO_NULO,
                   Nodo h_i = NODO_NULO)
        : elemento{elto}, padre{p}, h_izq{h_i}, h_dch{h_d} {}
    T elemento;
    Nodo padre, h_izq, h_dch;
  };
  Celda *nodos;
  int printAbin(Nodo n, bool isLeft, int offset, int depth,
                char[20][255]) const;
};

template <typename T>
inline Abin<T>::Abin(int max) : max_size{max}, size{0}, nodos{new Celda[max]} {}

template <typename T>
inline Abin<T>::Abin(const Abin<T> &a)
    : max_size{a.max_size}, size{a.size}, nodos{new Celda[max_size]} {
  std::copy(a.nodos, a.nodos + a.size, nodos);
}

template <typename T> void Abin<T>::insertarRaiz(const T &e) {
  assert(size == 0);
  nodos[size++] = Celda(e);
}

template <typename T> void Abin<T>::insertarHijoIzquierdo(Nodo n, const T &e) {
  assert(n >= 0 && n < size);
  assert(nodos[n].h_izq == NODO_NULO);
  assert(size < max_size);
  nodos[n].h_izq = size;
  nodos[size++] = Celda(e, n);
}

template <typename T> void Abin<T>::insertarHijoDerecho(Nodo n, const T &e) {
  assert(n >= 0 && n < size);
  assert(nodos[n].h_dch == NODO_NULO);
  assert(size < max_size);
  nodos[n].h_dch = size;
  nodos[size++] = Celda(e, n);
}

template <typename T> inline void Abin<T>::eliminarRaiz() {
  assert(size == 1);
  size = 0;
}

template <typename T> void Abin<T>::eliminarHijoIzquierdo(Nodo n) {
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

template <typename T> void Abin<T>::eliminarHijoDerecho(Nodo n) {
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

template <typename T> inline const T &Abin<T>::elemento(Nodo n) const {
  assert(n >= 0 && n < size);
  return nodos[n].elemento;
}

template <typename T> inline T &Abin<T>::elemento(Nodo n) {
  assert(n >= 0 && n < size);
  return nodos[n].elemento;
}

template <typename T>
inline typename Abin<T>::Nodo Abin<T>::padre(Nodo n) const {
  assert(n >= 0 && n < size);
  return nodos[n].padre;
}

template <typename T>
inline typename Abin<T>::Nodo Abin<T>::hijoIzquierdo(Nodo n) const {
  assert(n >= 0 && n < size);
  return nodos[n].h_izq;
}

template <typename T>
inline typename Abin<T>::Nodo Abin<T>::hijoDerecho(Nodo n) const {
  assert(n >= 0 && n < size);
  return nodos[n].h_dch;
}

template <typename T> Abin<T> &Abin<T>::operator=(const Abin<T> &a) {
  if (this != &a) {
    if (max_size < a.max_size) {
      delete[] nodos;
      max_size = a.max_size;
      nodos = new Celda[max_size];
    }
    size = a.size;
    std::copy(a.nodos, a.nodos + a.size, nodos);
  }
  return *this;
}

template <typename T>
int Abin<T>::printAbin(Nodo n, bool isLeft, int offset, int depth,
                       char s[20][255]) const {
  char b[20];
  int width{5};
  if (n == NODO_NULO) {
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
namespace Enlazada {
template <typename T> class Abin {
  struct Celda;

public:
  using Nodo = Celda *;
  inline static const Nodo NODO_NULO = nullptr;

  Abin();
  Abin(const Abin<T> &a);
  Abin<T> &operator=(const Abin<T> &a);

  void insertarRaiz(const T &e);
  void insertarHijoIzquierdo(Nodo n, const T &e);
  void insertarHijoDerecho(Nodo n, const T &e);
  void eliminarRaiz();
  void eliminarHijoIzquierdo(Nodo n);
  void eliminarHijoDerecho(Nodo n);
  bool vacio() const { return _raiz == nullptr; }
  const T &elemento(Nodo n) const;
  T &elemento(Nodo n);
  Nodo raiz() { return _raiz; }
  Nodo padre(Nodo n) const;
  Nodo hijoIzquierdo(Nodo n) const;
  Nodo hijoDerecho(Nodo n) const;
  ~Abin() { destruirNodos(_raiz); }

  template <typename U>
  friend std::ostream &operator<<(std::ostream &os, const Abin<U> &a);

private:
  struct Celda {
    Celda(const T &elto, Nodo p = NODO_NULO)
        : elemento(elto), padre(p), h_izq(NODO_NULO), h_dch(NODO_NULO) {}
    T elemento;
    Nodo padre, h_izq, h_dch;
  };
  void destruirNodos(Nodo &n);
  Nodo copiar(Nodo n);
  int printAbin(Nodo n, bool isLeft, int offset, int depth,
                char[20][255]) const;
  Nodo _raiz;
};

template <typename T> void Abin<T>::destruirNodos(Nodo &n) {
  if (n != NODO_NULO) {
    destruirNodos(n->h_izq);
    destruirNodos(n->h_dch);
    delete n;
    n = NODO_NULO;
  }
}

template <typename T> typename Abin<T>::Nodo Abin<T>::copiar(Nodo n) {
  Nodo m = NODO_NULO;
  if (n != NODO_NULO) {
    m = new Celda(n->elto);
    m->h_izq = copiar(n->h_izq);
    if (m->h_izq != NODO_NULO) {
      m->h_izq->padre = m;
    }
    m->h_dch = copiar(n->h_dch);
    if (m->h_dch != NODO_NULO) {
      m->h_dch->padre = m;
    }
  }
  return m;
}

template <typename T>
int Abin<T>::printAbin(Nodo n, bool isLeft, int offset, int depth,
                       char s[20][255]) const {
  char b[20];
  int width{5};
  if (n == NODO_NULO) {
    return 0;
  }
  sprintf(b, "(%03d)", n->elemento);
  int left = printAbin(n->h_izq, true, offset, depth + 1, s);
  int right = printAbin(n->h_dch, false, offset + left + width, depth + 1, s);
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

template <typename T> inline Abin<T>::Abin() : _raiz(NODO_NULO) {}

template <typename T>
inline Abin<T>::Abin(const Abin<T> &a) : _raiz(copiar(a._raiz)) {}

template <typename T> Abin<T> &Abin<T>::operator=(const Abin<T> &a) {
  if (this != &a) {
    this->~Abin();
    _raiz = copiar(a._raiz);
  }
  return *this;
}

template <typename T> void Abin<T>::insertarRaiz(const T &e) {
  assert(_raiz == NODO_NULO);
  _raiz = new Celda(e);
}

template <typename T> void Abin<T>::insertarHijoIzquierdo(Nodo n, const T &e) {
  assert(n != NODO_NULO);
  assert(n->h_izq == NODO_NULO);
  n->h_izq = new Celda(e, n);
}

template <typename T> void Abin<T>::insertarHijoDerecho(Nodo n, const T &e) {
  assert(n != NODO_NULO);
  assert(n->h_dch == NODO_NULO);
  n->h_dch = new Celda(e, n);
}

template <typename T> inline void Abin<T>::eliminarRaiz() {
  assert(_raiz != NODO_NULO);
  assert(_raiz->h_izq == NODO_NULO && _raiz->h_dch == NODO_NULO);
  delete _raiz;
  _raiz = NODO_NULO;
}

template <typename T> void Abin<T>::eliminarHijoIzquierdo(Nodo n) {
  assert(n != NODO_NULO);
  assert(n->h_izq != NODO_NULO);
  assert(n->h_izq->h_izq == NODO_NULO && n->h_izq->h_dch == NODO_NULO);
  delete n->h_izq;
  n->h_izq = NODO_NULO;
}

template <typename T> void Abin<T>::eliminarHijoDerecho(Nodo n) {
  assert(n != NODO_NULO);
  assert(n->h_dch != NODO_NULO);
  assert(n->h_dch->h_izq == NODO_NULO && n->h_dch->h_dch == NODO_NULO);
  delete (n->h_dch);
  n->h_dch = NODO_NULO;
}

template <typename T> inline const T &Abin<T>::elemento(Nodo n) const {
  assert(n != NODO_NULO);
  return n->elemento;
}

template <typename T> inline T &Abin<T>::elemento(Nodo n) {
  assert(n != NODO_NULO);
  return n->elemento;
}

template <typename T>
inline typename Abin<T>::Nodo Abin<T>::padre(Nodo n) const {
  assert(n != NODO_NULO);
  return n->padre;
}

template <typename T>
inline typename Abin<T>::Nodo Abin<T>::hijoIzquierdo(Nodo n) const {
  assert(n != NODO_NULO);
  return n->h_izq;
}

template <typename T>
inline typename Abin<T>::Nodo Abin<T>::hijoDerecho(Nodo n) const {
  assert(n != NODO_NULO);
  return n->h_dch;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const Abin<T> &a) {
  char s[20][255];
  for (int i = 0; i < 20; i++) {
    sprintf(s[i], "%80s", " ");
  }
  a.printAbin(a._raiz, 0, 0, 0, s);
  for (int i = 0; i < 20; i++) {
    os << s[i] << std::endl;
  }
  return os;
}

} // namespace Enlazada
#endif