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
    for (size_t i = 1; i <= n - 2; i++)
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

/*
2.  Definiremos  el pseudocentro  de  un  grafo  conexo  como  el  nodo
del  mismo  que minimiza la suma de las distancias mínimas a sus dos nodos más alejados. 
Definiremos el diámetro  del  grafo  como  la  suma  de  las  distancias 
mínimas  a  los  dos  nodos  más alejados del pseudocentro del grafo.
Dado  un  grafo  conexo  representado  mediante  matriz de  costes, 
implementa  un subprograma que devuelva la longitud de su diámetro. 
*/

template <typename T>
size_t pseudocentro(const GrafoP<T> &G)
{
    size_t diametro = 0;
    const size_t n = G.numVert();
    matriz<vertice<T>> P;
    matriz<coste> F = Floyd(G, P);
    for(int i = 0; i < n; i++){
        size_t max1 = 0,max2 = 0;
        for(int j = 0; j < n; j++){
            if(F[i][j] > max1){
                max2 = max1;
                max1 = F[i][j];
            }else if(F[i][j] > max2){
                max2 = F[i][j];
            }
            if(diametro < (max1 + max2))
                diametro = max1 + max2;
        }
    }

    return diametro;
}

/*
3.  Tu  empresa  de  transportes  “PEROTRAVEZUNGRAFO  S.A.”  
acaba  de  recibir  la lista  de  posibles  subvenciones  del  Ministerio  
de  Fomento  en  la  que  una  de  las  más jugosas  se  concede  a  las  empresas  
cuyo  grafo  asociado  a  su  matriz  de  costes  sea acíclico. 
¿Puedes pedir esta subvención? Implementa un subprograma que a partir de la 
matriz de costes nos indique si tu empresa tiene derecho a dicha subvención.
*/

template <typename T>
void funcion()
{
}

#endif