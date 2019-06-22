#ifndef GRF_PRAC2_HPP
#define GRF_PRAC2_HPP
#include "alg.hpp"

using grafos::pmc::GrafoP;

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

template <typename tCoste>
grafos::pmc::alg::arista<tCoste> ejercicio1(const GrafoP<tCoste>& G) {
  grafos::matriz<grafos::pmc::alg::vertice<tCoste>> P;
  grafos::matriz<tCoste> F{grafos::pmc::alg::FloydMax(G, P)};
  const size_t n = F.dimension();
  grafos::pmc::alg::arista<tCoste> max_c(-1, -1, GrafoP<tCoste>::INFINITO * -1);
  for (grafos::pmc::alg::vertice<tCoste> v = 0; v < n; ++v) {
    for (grafos::pmc::alg::vertice<tCoste> w = 0; w < n; ++w) {
      if (F[v][w] > max_c.coste) {
        max_c = grafos::pmc::alg::arista<tCoste>(v, w, F[v][w]);
      }
    }
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

struct Casilla
{
    size_t x, y;
    Casilla(size_t x, size_t y) : x(x), y(y) {}
};

struct Pared
{
    Casilla c1, c2;
    Pared(const Casilla &c1, const Casilla &c2) : c1(c1), c2(c2) {}
};

template<typename tCoste>
vector<Casilla> ejercicio2(size_t N ){

}

#endif