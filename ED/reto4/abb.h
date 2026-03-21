#ifndef __ABB_H__
#define __ABB_H__

#include "bintree.h"

template <class T>
class ABB {
    private:
    bintree<T> arbolbb;
    bool Buscar(typename bintree<T>::node n, const T & e) const;
    void InsertarRecursivo(typename bintree<T>::node n, const T & e);
    //………………….
    public:
    ABB();
    ABB (const ABB<T> & a);
    ABB (const T & e);
    bool Existe (const T & e) const;
    void insertar (const T & e);
    void borrar (const T & e);
    bintree<T>& getArbol() { return arbolbb; }
    const bintree<T>& getArbol() const { return arbolbb; }
    //…………………………….
    class iterator {
        private:
        typename bintree<T>::inorder_iterator it;
        public:
        iterator();
        iterator(typename bintree<T>::inorder_iterator i);
        T & operator*();
        typename ABB<T>::iterator & operator++();
        bool operator==(const iterator &i) const;
        bool operator!=(const iterator &i) const;
        //…………..
    };
    iterator begin();
    iterator end();
    ~ABB();
};

#include "abb.cpp"

#endif