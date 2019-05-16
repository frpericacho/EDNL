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

template<typename T>
vector<T> DijkstraInv(const GrafoP<T> &G, typename GrafoP<T>::vertice destino, vector<typename GrafoP<T>::vertice>&P){
    
}

#endif