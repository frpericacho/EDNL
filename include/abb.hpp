#ifndef ABB_H
#define ABB_H
#include <cassert>
#include "abin.hpp"
template <typename T>
class Abb
{
public:
    Abb(); // constructor
    const Abb &buscar(const T &e) const;
    void insertar(const T &e);
    void eliminar(const T &e);
    bool vacio() const;
    const T &elemento() const;
    const Abb &izqdo() const;
    const Abb &drcho() const;
    Abb(const Abb &A);            // ctor. de copia
    Abb &operator=(const Abb &A); // asig. árboles
    operator Enlazada::Abin<T>() const;
    
    ~Abb();

private:
    struct arbol
    {
        T elto;
        Abb izq, der;
        arbol(const T &e) : elto(e) {}
    };
    arbol *r; // raíz del árbol
    T borrarMin();
    void copiar(const Abb &A);
};

template <typename T>
inline Abb<T>::Abb() : r(0) {}

template <typename T>
inline bool Abb<T>::vacio() const
{
    return r == 0;
}

template <typename T>
const Abb<T> &Abb<T>::buscar(const T &e) const
{
    if (r == 0) // árbol vacío, e no encontrado
        return *this;
    else if (e < r->elto) // buscar en subárbol izqdo.
        return r->izq.buscar(e);
    else if (r->elto < e) // buscar en subárbol drcho.
        return r->der.buscar(e);
    else // encontrado e en la raíz
        return *this;
}

template <typename T>
void Abb<T>::insertar(const T &e)
{
    if (r == 0) // árbol vacío
        r = new arbol(e);
    else if (e < r->elto) // insertar en el subárbol izqdo.
        r->izq.insertar(e);
    else if (r->elto < e) // insertar en el subárbol drcho.
        r->der.insertar(e);
}

template <typename T>
void Abb<T>::eliminar(const T &e)
{
    if (r != 0)
    {                    // árbol no vacío
        if (e < r->elto) // quitar e del subárbol izqdo.
            r->izq.eliminar(e);
        else if (r->elto < e) // quitar e del subárbol drcho.
            r->der.eliminar(e);
        else // quitar e de la raíz
            if (r->izq.r == 0 && r->der.r == 0)
        { // 1. Raíz es hoja
            delete (r);
            r = 0; // el árbol queda vacío
        }
        else if (r->der.r == 0)
        { // 2. Raíz sólo tiene hijo izqdo.
            arbol *a = r->izq.r;
            r->izq.r = 0; // impide destruir el subárbol izqdo.
            delete (r);
            r = a;
        }
        else if (r->izq.r == 0)
        { // 3. Raíz sólo tiene hijo drcho.
            arbol *a = r->der.r;
            r->der.r = 0; // impide destruir el subárbol drcho.
            delete (r);
            r = a;
        }
        else // 4. Raíz tiene dos hijos
            // Eliminar el mínimo del subárbol derecho y sustituir
            // el elemento de la raíz por éste.
            r->elto = r->der.borrarMin();
    }
}

template <typename T>
T Abb<T>::borrarMin() // Elimina el nodo que almacena el menor elemento
// del árbol. Devuelve el elemento del nodo eliminado.
{
    if (r->izq.r == 0)
    { // subárbol izquierdo vacío
        T e = r->elto;
        arbol *hd = r->der.r;
        r->der.r = 0; // impide destruir el subárbol drcho.
        delete (r);
        r = hd; // sustituir r por el subárbol drcho.
        return e;
    }
    else
        return r->izq.borrarMin();
}

template <typename T>
inline const T &Abb<T>::elemento() const
{
    assert(r != 0);
    return r->elto;
}
template <typename T>
inline const Abb<T> &Abb<T>::izqdo() const
{
    assert(r != 0);
    return r->izq;
}
template <typename T>
inline const Abb<T> &Abb<T>::drcho() const
{
    assert(r != 0);
    return r->der;
}

template <typename T>
inline Abb<T>::Abb(const Abb<T> &A) : r(0)
{
    copiar(A);
}
template <typename T>
Abb<T> &Abb<T>::operator=(const Abb<T> &A)
{
    if (this != &A)
    {                 // evitar autoasignación
        this->~Abb(); // vaciar el árbol
        copiar(A);
    }
    return *this;
}

template <typename T>
Abb<T>::~Abb()
{
    if (r != 0)
    {             // árbol no vacío
        delete r; // llama a r->izq.~Abb() y a r->der.~Abb()
        r = 0;    // el árbol queda vacío
    }
}
// Método privado
template <typename T>
void Abb<T>::copiar(const Abb<T> &A) // Copia el árbol a en *this
{
    if (A.r != 0)
    {                             // árbol no vacío
        r = new arbol(A.r->elto); // copiar raíz
        r->izq.copiar(A.r->izq);  // copiar subárbol izqdo.
        r->der.copiar(A.r->der);  // copiar subárbol drcho.
    }
}

template <typename T>
Abb<T>::operator Enlazada::Abin<T>() const{
    if(!vacio()){
        Abin<T> n;
        n.insertarRaizB(elemento());
        copiar(n , this, n.raiz());
        return n;
    }
}

template<typename T>
void copiar(Enlazada::Abin<T> &abin, Abb<T> &abb, typename Enlazada::Abin<T>::nodo n){
    if(!abb.vacio()){
        if(!abb.izqdo().vacio()){
            abin.insertarHijoIzqdoB(n, abb.izqdo().elemento());
            copiar(abin , abb.izqdo(), abin.hijoIzqdoB(n));
        }
        if(!abb.drcho().vacio()){
            abin.insertarHijoDrchoB(n, abb.drcho().elemento());
            copiar(abin, abb.drcho(), abin.hijoDrchoB(n));
        }
    }
}

#endif