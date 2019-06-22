#ifndef GRF_PRAC1_HPP
#define GRF_PRAC1_HPP
#include <algorithm>
#include <iostream>
#include "alg.hpp"

using grafos::pmc::GrafoP;

/*
1.  Añadir    una    función    genérica,    llamada DijkstraInv,
    en    el    fichero alg_grafoPMC.h para  resolver  el  problema  inverso  al
de  Dijkstra, con  los  mismos tipos  de  parámetros  y  de  resultado  que  la
función ya  incluida  para  éste.  La  nueva función, por  tanto,  debe  hallar
el  camino  de  coste mínimo  hasta  un  destino desde  cada vértice del grafo y
su correspondiente coste.
*/
/*
template <typename T>
vector<T> DijkstraInv(const GrafoP<T> &G, typename GrafoP<T>::vertice destino,
vector<typename GrafoP<T>::vertice> &P)
{
    typedef typename GrafoP<tCoste>::vertice vertice;
    vertice v, w;
    const T n = G.numVert();
    vector<bool> S(n, false); // Conjunto de vértices vacío.
    vector<tCoste> D;         // Costes mínimos desde destino.
    // Iniciar D y P con caminos directos desde el vértice destino.
    for (vertice<T> i = 0; i < n; i++)
    {
        D[i] = G[i][destino];               //VER PORQUE
    }
    //  D = G[destino];
    D[destino] = 0; // Coste destino-destino es 0.
    P = vector<vertice>(n, destino);
    S[destino] = true; // Incluir vértice destino en S.
    for (T i = 1; i <= n - 2; i++)
    { // Localizar vértice w no incluido en S con menor coste desde destino
        tCoste costeMin = GrafoP<tCoste>::INFINITO;
        for (v = 0; v <= n - 1; v++)
            if (!S[v] && D[v] <= costeMin)
            {
                costeMin = D[v];
                w = v;
            }
        S[w] = true; // Incluir vértice w en S.
        // Recalcular coste hasta cada v no incluido en S, a través de w.
        for (v = 0; v <= n - 1; v++)
            if (!S[v])
            {
                tCoste Owv = suma(D[w], G[w][v]);
                if (Owv < D[v])
                {
                    D[v] = Owv;
                    P[v] = w;
                }
            }
    }
    return D;
}

template <typename tCoste>
tCoste suma(tCoste x, tCoste y)
{
    const tCoste INFINITO = GrafoP<tCoste>::INFINITO;
    if (x == INFINITO || y == INFINITO)
        return INFINITO;
    else
        return x + y;
}
*/
/*
2.  Definiremos  el pseudocentro  de  un  grafo  conexo  como  el  nodo
del  mismo  que minimiza la suma de las distancias mínimas a sus dos nodos más
alejados. Definiremos el diámetro  del  grafo  como  la  suma  de  las
distancias mínimas  a  los  dos  nodos  más alejados del pseudocentro del grafo.
Dado  un  grafo  conexo  representado  mediante  matriz de  costes,
implementa  un subprograma que devuelva la longitud de su diámetro.
*/

template <typename T>
T pseudocentro(const GrafoP<T> &G) {
  const int n = G.numVert();
  grafos::matriz<grafos::pmc::alg::vertice<T>> P;
  grafos::matriz<T> F = grafos::pmc::alg::Floyd(G, P);
  vector<T> aux(n);
  for (int i = 0; i < n; i++) {
    T max1 = 0, max2 = 0;
    for (int j = 0; j < n; j++) {
      std::cout << F[i][j] << ", ";
      if (F[i][j] != GrafoP<T>::INFINITO) {
        if (F[i][j] > max1) {
          max2 = max1;
          max1 = F[i][j];
        } else if (F[i][j] < max1 && F[i][j] > max2) {
          max2 = F[i][j];
        }
      }
    }
    std::cout << "\n";
    aux[i] = max1 + max2;
  }

  return *std::max_element(aux.begin(), aux.end());
}

/*
3.  Tu  empresa  de  transportes  “PEROTRAVEZUNGRAFO  S.A.”
acaba  de  recibir  la lista  de  posibles  subvenciones  del  Ministerio
de  Fomento  en  la  que  una  de  las  más jugosas  se  concede  a  las
empresas cuyo  grafo  asociado  a  su  matriz  de  costes  sea acíclico. ¿Puedes
pedir esta subvención? Implementa un subprograma que a partir de la matriz de
costes nos indique si tu empresa tiene derecho a dicha subvención.
*/

template <typename T>
T subvencion(const GrafoP<T> &G) {
  const size_t n = G.numVert();
  grafos::matriz<T> A(n);
  bool res = true;
  for (grafos::pmc::alg::vertice<T> i = 0; i < n; i++) A[i] = G[i];

  for (grafos::pmc::alg::vertice<T> k = 0; k < n; k++)
    for (grafos::pmc::alg::vertice<T> i = 0; i < n; i++)
      for (grafos::pmc::alg::vertice<T> j = 0; j < n; j++)
        if (T ijk = grafos::pmc::alg::suma(A[i][k], A[k][j]); ijk < A[i][j])
          A[i][j] = ijk;

  for (size_t i = 0; i < n && res; i++) res = A[i][i] == GrafoP<T>::INFINITO;

  return res;
}

/*
4.  Se  necesita  hacer  un  estudio  de  las  distancias  mínimas  necesarias
para  viajar  entre dos  ciudades  cualesquiera  de  un  país  llamado
Zuelandia.  El  problema  es  sencillo  pero hay que tener en cuenta unos
pequeños detalles:
a)La orografía de Zuelandia es un poco especial, las
carreteras son muy estrechas y por tanto solo permiten un sentido de la
circulación.
b)Actualmente  Zuelandia  es  un  país  en  guerra.  Y  de  hecho
hay  una  serie  de ciudades  del  país  que  han  sido  tomadas  por  los
rebeldes,  por  lo  que  no  pueden ser usadas para viajar.
c)Los  rebeldes  no sólo  se  han  apoderado  de  ciertas  ciudades  del  país,
sino  que también han cortado ciertas carreteras, (por lo que estas carreteras
no pueden ser usadas).
d)Pero  el  gobierno  no  puede  permanecer  impasible
ante  la situación  y  ha  exigido que absolutamente todos los viajes que se
hagan por el país pasen por la capital del mismo, donde se harán los controles
de seguridad pertinentes.
Dadas estas cuatro condiciones, se pide implementar un subprograma que dados
•el grafo (matriz de costes) de Zuelandia en situación
normal,
•la relación de las ciudades tomadas por los rebeldes,
•la relación de las carreteras cortadas por los rebeldes
•y la capital de Zuelandia,
calcule  la matriz  de  costes  mínimos  para  viajar  entre  cualesquiera  dos
ciudades zuelandesas en esta situación.
*/

// distra a la capital y distra inverso desde la capital
template <typename T>
T zuelandia(const GrafoP<T> &G, grafos::pmc::alg::vertice<T> cap,
            const vector<T> &ciudades,
            const vector<grafos::pmc::alg::arista<T>> &caminos) {
  const size_t n = G.numVert();
  grafos::matriz<T> A(n);
  vector<grafos::pmc::alg::vertice<T>> P;

  for (grafos::pmc::alg::vertice<T> i = 0; i < n; i++)
    for (const auto &c : ciudades)
     G[i][c] = GrafoP<T>::INFINITO;

  for(const auto &c : caminos)
    G[c.orig][c.dest] = GrafoP<T>::INFINITO;

  vector<T> dis = grafos::pmc::alg::Dijkstra(G, cap, P);
  vector<T> disin = grafos::pmc::alg::DijkstraInv(G, cap, P);

  return A;
}

#endif