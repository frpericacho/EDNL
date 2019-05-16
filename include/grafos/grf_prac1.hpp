#ifndef GRF_PRAC1_HPP
#define GRF_PRAC1_HPP
#include "alg.hpp"

using grafos::pmc::GrafoP;

/*
1.  Añadir    una    función    genérica,    llamada DijkstraInv, 
    en    el    fichero alg_grafoPMC.h para  resolver  el  problema  inverso  al  de  Dijkstra, 
    con  los  mismos tipos  de  parámetros  y  de  resultado  que  la  función 
    ya  incluida  para  éste.  La  nueva función,  
    por  tanto,  debe  hallar  el  camino  de  coste mínimo  hasta  un  destino  
    desde  cada vértice del grafo y  su correspondiente coste.
*/

template <typename T>
vector<T> DijkstraInv(const GrafoP<T> &G, typename GrafoP<T>::vertice destino, vector<typename GrafoP<T>::vertice> &P)
{
    typedef typename GrafoP<tCoste>::vertice vertice;
    vertice v, w;
    const size_t n = G.numVert();
    vector<bool> S(n, false); // Conjunto de vértices vacío.
    vector<tCoste> D;         // Costes mínimos desde origen.
    // Iniciar D y P con caminos directos desde el vértice origen.
    D = G[origen];
    D[origen] = 0; // Coste origen-origen es 0.
    P = vector<vertice>(n, origen);
    S[origen] = true; // Incluir vértice origen en S.
    for (size_t i = 1; i <= n - 2; i++)
    { // Localizar vértice w no incluido en S con menor coste desde origen
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

#endif