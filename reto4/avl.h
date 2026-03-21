#ifndef __AVL_H__
#define __AVL_H__

#include "abb.h"
#include "bintree.h"

template <class T>
class AVL {
    private:
    ABB<T> arbolavl;
    //………………….
    void ajustarArbol (typename bintree<T>::node & n);
    void rotarHijoDrcha (typename bintree<T>::node & n);
    int altura (typename bintree<T>::node & n);
    public:
    AVL();
    AVL (const ABB<T> & a);
    AVL (const T & e);
    bool Existe (const T & e) const;
    void insertar (const T & e);
    void borrar (const T & e);
    //…………………………….
    class iterator {
        private:
        typename ABB<T>::iterator it;
        public:
        //……………
        //……………….
    };
    iterator begin();
    iterator end();
    ~AVL();
};

#endif