#ifndef GRAFOS_ALG_HPP
#define GRAFOS_ALG_HPP
#include <algorithm>
#include <cassert>
#include <tuple>
#include "grafos/apo.hpp"
#include "grafos/cola.hpp"
#include "grafos/matriz.hpp"
#include "grafos/particion.hpp"
#include "grafos/pila.hpp"
#include "grafos/pla.hpp"
#include "grafos/pmc.hpp"
namespace grafos {
namespace pmc::alg {

template <typename T>
using vertice = typename GrafoP<T>::vertice;

template <typename T>
using tCamino = typename GrafoP<T>::tCamino;

template <typename T>
using arista = typename GrafoP<T>::arista;

template <typename C>
std::tuple<size_t, C> min_with_index(const vector<C>& v) {
  auto index = std::min_element(v.begin(), v.end());
  return {std::distance(v.begin(), index), *index};
}

template <typename C>
std::tuple<size_t, C> max_with_index(const vector<C>& v) {
  auto index = std::max_element(v.begin(), v.end());
  return {std::distance(v.begin(), index), *index};
}

template <typename T>
GrafoP<T> BigGrafo(const vector<GrafoP<T>>& graphs,
                   const vector<vector<T>>& costes) {
  const size_t m{graphs.size()}, n{graphs[0].numVert()};
  GrafoP<T> BG(m * n);
  vertice<T> v, w, bgv, bgw;
  for (size_t i = 0, g = 0, d = 0; i < m; ++i, g += (m - i), d = 0) {
    for (v = 0; v < n; ++v) {
      bgv = v + n * i;
      for (w = v; w < n; ++w) {
        bgw = w + n * i;
        BG[bgv][bgw] = BG[bgw][bgv] = graphs[i][v][w];
        if (v == w && i < m - 1) {
          for (size_t j = n * (i + 1), k = g; j < m * n; j += n, ++k) {
            BG[bgv][j + w] = BG[j + w][bgv] = costes[k][d];
          }
          ++d;
        }
      }
    }
  }
  return BG;
}

template <typename T>
GrafoP<T> BigGrafo(const vector<GrafoP<T>>& graphs,
                   const vector<vector<T>>& costes_sup,
                   const vector<vector<T>>& costes_inf) {
  const size_t m{graphs.size()}, n{graphs[0].numVert()};
  GrafoP<T> BG(m * n);
  vertice<T> v, w, bgv, bgw;
  for (size_t i = 0, g = 0, d = 0; i < m; ++i, g += (m - i), d = 0) {
    for (v = 0; v < n; ++v) {
      bgv = v + n * i;
      for (w = v; w < n; ++w) {
        bgw = w + n * i;
        BG[bgv][bgw] = BG[bgw][bgv] = graphs[i][v][w];
        if (v == w && i < m - 1) {
          for (size_t j = (n * (i + 1)) + w, k = g; j < m * n; j += n, ++k) {
            BG[bgv][j] = costes_sup[k][d];
            BG[j][bgv] = costes_inf[k][d];
          }
          ++d;
        }
      }
    }
  }
  return BG;
}

template <typename T>
GrafoP<T> BigGrafo(const vector<GrafoP<T>>& graphs, T coste) {
  const size_t m{graphs.size()}, n{graphs[0].numVert()};
  const size_t mn{m * n};
  GrafoP<T> BG(mn);
  vertice<T> v, w, bgv, bgw;
  for (size_t i = 0; i < m; ++i) {
    for (v = 0; v < n; ++v) {
      bgv = v + n * i;
      for (w = v; w < n; ++w) {
        bgw = w + n * i;
        BG[bgw][bgv] = BG[bgv][bgw] = graphs[i][v][w];
        if (v == w && i < m - 1) {
          for (size_t j = (n * (i + 1)) + w; j < mn; j += n) {
            BG[bgv][j] = BG[j][bgv] = coste;
          }
        }
      }
    }
  }
  return BG;
}

template <typename T>
/**
 * Suma de costes. Devuelve GrafoP<tCoste>::INFINITO si alguno de los
 * dos parámetros vale GrafoP<tCoste>::INFINITO.
 */
T suma(T x, T y, bool signedinf = false) {
  const T INFINITO =
      ((signedinf) ? GrafoP<T>::INFINITO * -1 : GrafoP<T>::INFINITO);
  if (x == INFINITO || y == INFINITO)
    return INFINITO;
  else
    return x + y;
}

template <typename tCoste>
/**
 * Calcula los caminos de coste mínimo entre origen y todos los
 * vértices del grafo G. Devuelve un vector de tamaño G.numVert()
 * con estos costes mínimos y un vector P, también de tamaño
 * G.numVert(), tal que P[i] es el último vértice del camino de
 * coste mínimo de origen a i.
 */
vector<tCoste> Dijkstra(const GrafoP<tCoste>& G, vertice<tCoste> origen,
                        vector<vertice<tCoste>>& P) {
  vertice<tCoste> v, w;
  const std::size_t n = G.numVert();
  vector<bool> S(n, false);
  vector<tCoste> D;
  D = G[origen];
  D[origen] = 0;
  P = vector<vertice<tCoste>>(n, origen);
  S[origen] = true;
  for (std::size_t i = 1; i <= n - 2; ++i) {
    tCoste costeMin = GrafoP<tCoste>::INFINITO;
    for (v = 0; v < n; ++v) {
      if (!S[v] && D[v] <= costeMin) {
        costeMin = D[v];
        w = v;
      }
    }
    S[w] = true;
    for (v = 0; v < n; v++) {
      if (!S[v]) {
        tCoste Owv = suma(D[w], G[w][v]);
        if (Owv < D[v]) {
          D[v] = Owv;
          P[v] = w;
        }
      }
    }
  }
  return D;
}

template <typename tCoste>
/**
 * Dijkstra Inverso
 */
vector<tCoste> DijkstraInv(const GrafoP<tCoste>& G, vertice<tCoste> destino,
                           vector<vertice<tCoste>>& P) {
  GrafoP<tCoste> Gt{G};
  const size_t n{G.numVert()};
  for (vertice<tCoste> v = 0; v < n; ++v) {
    for (vertice<tCoste> w = 0; w < n; ++w) {
      Gt[w][v] = G[v][w];
    }
  }
  return Dijkstra(Gt, destino, P);
}

template <typename T>
/**
 * Devuelve el camino de coste mínimo entre los vértices orig  y v
 * a partir de un vector P obtenido mediante la función Dijkstra().
 */
tCamino<T> camino(vertice<T> orig, vertice<T> v, const vector<vertice<T>>& P) {
  tCamino<T> C;
  C.insertar(v, C.primera());
  do {
    C.insertar(P[v], C.primera());
    v = P[v];
  } while (v != orig);
  return C;
}

template <typename T>
tCamino<T> caminoInv(vertice<T> destino, vertice<T> v,
                     const vector<vertice<T>>& P) {
  tCamino<T> C;
  C.insertar(v, C.fin());
  do {
    C.insertar(P[v], C.fin());
    v = P[v];
  } while (v != destino);
  return C;
}

template <typename C>
vertice<C> visitar(const GrafoP<C>& G, vector<bool>& visitado,
                   vector<vertice<C>>& orden, vertice<C> index, vertice<C> u) {
  if (visitado[u]) {
    return index;
  }
  visitado[u] = true;
  for (vertice<C> v = 0; v < G.numVert(); ++v) {
    index = visitar(G, visitado, orden, index, v);
  }
  orden[index--] = u;
  return index;
}

template <typename C>
vector<vertice<C>> OrdenTopologico(const GrafoP<C>& G) {
  const size_t n{G.numVert()};
  vector<bool> visitado(n, false);
  vector<vertice<C>> orden(n);
  vertice<C> index{n - 1};
  for (vertice<C> u = 0; u < n; ++u) {
    if (!visitado[u]) {
      index = visitar(G, visitado, orden, index, u);
    }
  }
  return orden;
}

template <typename tCoste>
/**  Calcula los caminos de coste mínimo entre cada par de vértices
 * del grafo G. Devuelve una matriz de costes mínimos de tamaño
 * n x n, con n = G.numVert(), y una matriz de vértices P de
 * tamaño n x n, tal que P[i][j] es el vértice por el que pasa el
 * camino de coste mínimo de i a j, si este vértice es i el camino
 * es directo.
 */
matriz<tCoste> Floyd(const GrafoP<tCoste>& G, matriz<vertice<tCoste>>& P) {
  const std::size_t n = G.numVert();
  matriz<tCoste> A(n);
  P = matriz<vertice<tCoste>>(n, -1);
  for (vertice<tCoste> i = 0; i < n; ++i) {
    A[i] = G[i];
    A[i][i] = 0;
    for (vertice<tCoste> j = 0; j < n; ++j) {
      if (G[i][j] != GrafoP<tCoste>::INFINITO) {
        P[i][j] = i;
      }
    }
  }

  for (vertice<tCoste> k = 0; k < n; ++k) {
    for (vertice<tCoste> i = 0; i < n; ++i) {
      for (vertice<tCoste> j = 0; j < n; ++j) {
        if (tCoste ikj = suma(A[i][k], A[k][j]); ikj < A[i][j]) {
          A[i][j] = ikj;
          P[i][j] = P[k][j];
        }
      }
    }
  }
  return A;
}

template <typename tCoste>
matriz<tCoste> FloydMax(const GrafoP<tCoste>& G, matriz<vertice<tCoste>>& P) {
  const std::size_t n = G.numVert();
  matriz<tCoste> A(n);
  P = matriz<vertice<tCoste>>(n, -1);
  for (vertice<tCoste> i = 0; i < n; ++i) {
    A[i] = G[i];
    A[i][i] = 0;
    for (vertice<tCoste> j = 0; j < n; ++j) {
      if (G[i][j] != GrafoP<tCoste>::INFINITO) {
        P[i][j] = i;
      } else {
        A[i][j] *= -1;
      }
    }
  }

  for (vertice<tCoste> k = 0; k < n; ++k) {
    for (vertice<tCoste> i = 0; i < n; ++i) {
      for (vertice<tCoste> j = 0; j < n; ++j) {
        if (tCoste ikj = suma(A[i][k], A[k][j], true); ikj > A[i][j]) {
          A[i][j] = ikj;
          P[i][j] = P[k][j];
        }
      }
    }
  }
  return A;
}

template <typename tCoste>
tCamino<tCoste> caminoAux(vertice<tCoste> v, vertice<tCoste> w,
                          const matriz<vertice<tCoste>>& P) {
  tCamino<tCoste> C1, C2;
  vertice<tCoste> u = P[v][w];
  if (u != v) {
    C1 = caminoAux<tCoste>(v, u, P);
    C1.insertar(u, C1.fin());
    C2 = caminoAux<tCoste>(u, w, P);
    C1 += C2;
  }
  return C1;
}

template <typename tCoste>
/**
 * Devuelve el camino de coste mínimo desde i hasta j a partir
 * de una matriz P obtenida mediante la función Floyd().
 */
tCamino<tCoste> camino(vertice<tCoste> v, vertice<tCoste> w,
                       const matriz<vertice<tCoste>>& P) {
  tCamino<tCoste> C = caminoAux<tCoste>(v, w, P);
  C.insertar(v, C.primera());
  C.insertar(w, C.fin());
  return C;
}

template <typename tCoste>
/**
 * Devuelve un árbol generador de coste mínimo
 * de un grafo no dirigido ponderado y conexo G.
 */
GrafoP<tCoste> Prim(const GrafoP<tCoste>& G) {
  assert(!G.esDirigido());
  const tCoste INFINITO = GrafoP<tCoste>::INFINITO;
  arista<tCoste> a;
  const std::size_t n = G.numVert();
  GrafoP<tCoste> g(n);
  vector<bool> U(n, false);
  Apo<arista<tCoste>> A(n * (n - 1) / 2 - n + 2);
  U[0] = true;
  for (vertice<tCoste> v = 1; v < n; ++v)
    if (G[0][v] != INFINITO) A.insertar(arista<tCoste>(0, v, G[0][v]));
  for (std::size_t i = 1; i <= n - 1; ++i) {
    do {
      a = A.cima();
      A.suprimir();
    } while (U[a.dest]);
    g[a.orig][a.dest] = g[a.dest][a.orig] = a.coste;
    vertice<tCoste> u = a.dest;
    U[u] = true;
    for (vertice<tCoste> v = 0; v < n; ++v)
      if (!U[v] && G[u][v] != INFINITO)
        A.insertar(arista<tCoste>(u, v, G[u][v]));
  }
  return g;
}

template <typename tCoste>
/**
 * Devuelve un árbol generador de coste mínimo
 * de un grafo no dirigido ponderado y conexo G.
 */
GrafoP<tCoste> Kruskall(const GrafoP<tCoste>& G) {
  assert(!G.esDirigido());
  const tCoste INFINITO = GrafoP<tCoste>::INFINITO;
  const std::size_t n = G.numVert();
  GrafoP<tCoste> g(n);
  Particion P(n);
  Apo<arista<tCoste>> A(n * n);
  for (vertice<tCoste> u = 0; u < n; ++u)
    for (vertice<tCoste> v = u + 1; v < n; ++v)
      if (G[u][v] != INFINITO) A.insertar(arista<tCoste>(u, v, G[u][v]));
  std::size_t i = 1;
  while (i <= n - 1) {
    arista<tCoste> a = A.cima();
    A.suprimir();
    vertice<tCoste> u = P.encontrar(a.orig);
    vertice<tCoste> v = P.encontrar(a.dest);
    if (u != v) {
      P.unir(u, v);
      g[a.orig][a.dest] = g[a.dest][a.orig] = a.coste;
      i++;
    }
  }
  return g;
}

}  // namespace pmc::alg
namespace ma::alg {
using vertice = Grafo::vertice;
enum visitas { NO_VISITADO, VISITADO };
matriz<bool> Warshall(const Grafo& G) {
  const std::size_t n = G.numVert();
  matriz<bool> A(n);
  for (vertice i = 0; i < n; ++i) {
    A[i] = G[i];
    A[i][i] = true;
  }
  for (vertice k = 0; k < n; ++k)
    for (vertice i = 0; i < n; ++i)
      for (vertice j = 0; j < n; ++j)
        if (!A[i][j]) A[i][j] = A[i][k] && A[k][j];
  return A;
}

static Lista<vertice> Profun(const Grafo& G, vertice v,
                             vector<visitas>& marcas) {
  const std::size_t n = G.numVert();
  Lista<vertice> Lv;

  marcas[v] = VISITADO;
  Lv.insertar(v, Lv.fin());
  for (vertice w = 0; w < n; ++w)
    if (G[v][w] && marcas[w] == NO_VISITADO) Lv += Profun(G, w, marcas);
  return Lv;
}

Lista<vertice> Profundidad(const Grafo& G, vertice v) {
  const std::size_t n = G.numVert();
  vector<visitas> marcas(n, NO_VISITADO);
  Lista<vertice> Lv;
  vertice i = v;

  do {
    if (marcas[i] == NO_VISITADO) Lv += Profun(G, i, marcas);
    i = (i + 1) % n;
  } while (i != v);
  return Lv;
}

Lista<vertice> Profundidad2(const Grafo& G, vertice u) {
  const std::size_t n = G.numVert();
  vector<visitas> marcas(n, NO_VISITADO);
  Pila<vertice> P;
  Lista<vertice> Lv;
  vertice i = u;
  do {
    if (marcas[i] == NO_VISITADO) {
      P.push(i);
      do {
        vertice v = P.tope();
        P.pop();
        if (marcas[v] == NO_VISITADO) {
          marcas[v] = VISITADO;
          Lv.insertar(v, Lv.fin());
          for (vertice w = n; w > 0; --w)
            if (G[v][w - 1] && marcas[w - 1] == NO_VISITADO) P.push(w - 1);
        }
      } while (!P.vacia());
    }
    i = (i + 1) % n;
  } while (i != u);
  return Lv;
}

Lista<vertice> Anchura(const Grafo& G, vertice u) {
  const std::size_t n = G.numVert();
  vector<visitas> marcas(n, NO_VISITADO);
  Cola<vertice> C;
  Lista<vertice> Lv;
  vertice i = u;
  do {
    if (marcas[i] == NO_VISITADO) {
      C.push(i);
      do {
        vertice v = C.frente();
        C.pop();
        if (marcas[v] == NO_VISITADO) {
          marcas[v] = VISITADO;
          Lv.insertar(v, Lv.fin());
          for (vertice w = n; w > 0; --w)
            if (G[v][w - 1] && marcas[w - 1] == NO_VISITADO) C.push(w - 1);
        }
      } while (!C.vacia());
    }
    i = (i + 1) % n;
  } while (i != u);
  return Lv;
}

}  // namespace ma::alg
}  // namespace grafos
#endif