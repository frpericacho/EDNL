#ifndef PILA_DINAMICA_HPP
#define PILA_DINAMICA_HPP
#include <cassert>
#include <iostream>
template <typename T>
class Pila {
public:
    Pila(): tope_(0) {} // constructor
    Pila(const Pila<T>& p); // ctor. de copia
    Pila<T>& operator =(const Pila<T>& p); // asignación
    bool vacia() const;
    T tope() const;
    void pop();
    void push(const T& x);
    ~Pila(); // destructor
private:
    struct nodo {
        T elto;
        nodo* sig;
        nodo(const T& e, nodo* p = 0): elto(e), sig(p) {}
    };
    nodo* tope_;
    void copiar(const Pila<T>& p);
};

template <typename T>
void Pila<T>::copiar(const Pila<T>& p){
    tope_ = new nodo(p.tope()); // copiar el primer elto
    // Copiar el resto de elementos hasta el fondo de la pila.
    nodo* q = tope_; // recorre la pila destino
    nodo* r = p.tope_->sig; // recorre la pila origen
    while (r) {
        q->sig = new nodo(r->elto);
        q = q->sig;
        r = r->sig;
    }
}

template <typename T>
Pila<T>::Pila(const Pila<T>& p) : tope_(0) {
    if (!p.vacia())
        copiar(p);
}

template <typename T>
Pila<T>& Pila<T>::operator =(const Pila<T>& p){
    if (this != &p){ // evitar autoasignación
        this->~Pila(); // vaciar la pila actual
        if (!p.vacia())
            copiar(p);
    }
    return *this;
}

template <typename T>
inline bool Pila<T>::vacia() const {
    return (!tope_);
}

template <typename T>
inline T Pila<T>::tope() const{
    assert(!vacia());
    return tope_->elto;
}

template <typename T>
inline void Pila<T>::pop(){
    assert(!vacia());
    nodo* q = tope_;
    tope_ = q->sig;
    delete q;
}

template <typename T>
inline void Pila<T>::push(const T& x){
    tope_ = new nodo(x, tope_);
}

template <typename T>
Pila<T>::~Pila() {
    nodo* q;
    while (tope_){
        q = tope_->sig;
        delete tope_;
        tope_ = q;
    }
}

template <typename T>
std::ostream& operator << (std::ostream& os,Pila<T> p){
    while(!p.vacia()){
        os << p.tope();
        p.pop();
    }
    return os;
}
#endif
