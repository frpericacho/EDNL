#ifndef ABIN_VEC_HPP
#define ABIN_VEC_HPP
namespace Vectorial
{

const int NODO_NULO = -1;

template <typename T>
class Abin
{
public:
  typedef int nodo;
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

private:
  int max_size;
  int size;
  class celda
  {
  public:
    T elemento;
    nodo padre, h_izq, h_dch;
    celda(const T &elto, nodo p = NODO_NULO, nodo h_d = NODO_NULO, nodo h_i = NODO_NULO) : elemento{elto}, padre{p}, h_izq{h_i}, h_dch{h_d} {}
    celda(const celda &) = default;
    celda &operator=(const celda &) = default;
  };
  celda *nodos;
};
} // namespace Vectorial
#endif