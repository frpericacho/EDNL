#ifndef GRF_PRAC2_HPP
#define GRF_PRAC2_HPP
#include <vector>
#include "alg.hpp"

using grafos::Lista;
using grafos::matriz;
using grafos::pmc::GrafoP;
using grafos::pmc::alg::arista;
using grafos::pmc::alg::BigGrafo;
using grafos::pmc::alg::camino;
using grafos::pmc::alg::caminoInv;
using grafos::pmc::alg::Dijkstra;
using grafos::pmc::alg::FloydMax;
using grafos::pmc::alg::min_with_index;
using grafos::pmc::alg::tCamino;
using grafos::pmc::alg::vertice;
using std::size_t;

/*
1. Tu agencia de viajes “OTRAVEZUNGRAFO S.A.”  se enfrenta a un curioso cliente.
Es  un  personaje  sorprendente,  no  le  importa  el  dinero  y  quiere  hacer
el  viaje más  caro  posible  entre  las  ciudades  que  ofertas. Su  objetivo
es  gastarse  la  mayor  cantidad  de  dinero posible (ojalá todos los clientes
fueran así), no le importa el origen ni el destino del viaje.

Sabiendo que es imposible pasar dos veces por la misma ciudad,
ya que casualmente el grafo de tu agencia de viajes resultó ser acíclico,
devolver el coste, origen y destino de tan curioso viaje.
Se parte de la matriz de costes directos entre las ciudades del grafo.
*/

template <typename T>
grafos::pmc::alg::arista<T> ejercicio1(const GrafoP<T> &G) {
  grafos::matriz<grafos::pmc::alg::vertice<T>> P;
  grafos::matriz<T> F = grafos::pmc::alg::FloydMax(G, P);
  const size_t n = F.dimension();
  grafos::pmc::alg::arista<T> max_c(-1, -1, GrafoP<T>::INFINITO * -1);
  for (grafos::pmc::alg::vertice<T> v = 0; v < n; ++v)
    for (grafos::pmc::alg::vertice<T> w = 0; w < n; ++w)
      if (F[v][w] > max_c.coste) {
        max_c = grafos::pmc::alg::arista<T>(v, w, F[v][w]);
      }
  return max_c;
}

/*
2. Se dispone de un laberinto de NxN  casillas del que se conocen las casillas
de entrada y salida del mismo. Si te encuentras en una casilla sólo puedes
moverte en las siguientes cuatro direcciones (arriba, abajo, derecha,
izquierda). Por otra parte, entre algunas de las casillas hay una pared que
impide moverse entre las dos casillas que separa dicha pared (en caso contrario
no sería un verdadero laberinto).
Implementa un subprograma que dados
- N (dimensión del laberinto),
- la lista de paredes del laberinto,
- la casilla de entrada, y
- la casilla de salida,
calcule el camino más corto para ir de la entrada a la salida y su longitud.
 */

template <typename T>
arista<T> ejercicio2(const size_t tam, const Lista<arista<T>> &pared,
                     const vertice<T> ent, const vertice<T> sal, T &longitud) {
  GrafoP<T> G(tam * tam);
  for (vertice<T> i = 0; v < dim * dim; ++i) {
    if (v < dim * (dim - 1)) {
      L[v][v + dim] = L[v + dim][v] = 1;
    }
    if (v % dim != dim - 1) {
      L[v][v + 1] = L[v + 1][v] = 1;
    }
  }

  for (auto it = paredes.primera(); it != paredes.fin();
       it = paredes.siguiente(it)) {
    const arista<tCoste> &p = paredes.elemento(it);
    L[p.orig][p.dest] = L[p.dest][p.orig] = GrafoP<tCoste>::INFINITO;
  }

  vector<vertice<tCoste>> P;
  vector<tCoste> D{Dijkstra(L, inicio, P)};
  return {D[fin], camino<tCoste>(inicio, fin, P)};
}

/*
5.  Se  dispone  de  tres  grafos  que  representan  la  matriz  de  costes para
viajes  en  un  determinado país pero por diferentes medios de transporte, por
supuesto todos los grafos tendrán  el  mismo  número  de  nodos.  El  primer
grafo  representa  los  costes  de  ir  por  carretera, el segundo en tren y el
tercero en avión. Dado un viajero que dispone de una determinada cantidad de
dinero, que es alérgico a uno de los tres medios de transporte, y que  sale  de
una  ciudad  determinada,  implementar  un  subprograma  que  determine  las
ciudades a las que podría llegar nuestro infatigable viajero.
 */

/*template <typename T>
vector<T> ejercicio5(const GrafoP<T> &Ca, const GrafoP<T> &Tr,
                     const GrafoP<T> &Av, T dinero,
                     grafos::pmc::alg::vertice<T> alergia,
                     grafos::pmc::alg::vertice<T> ori) {
  const size_t n = Ca.numVert();

}*/

#endif