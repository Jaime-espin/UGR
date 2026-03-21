#include "abb.h"
#include "bintree.h"

template <class T>
ABB<T>::ABB(){
    arbolbb.clear();
}

template <class T>
ABB<T>::ABB(const ABB<T> & a): arbolbb(a.arbolbb){}

template <class T>
ABB<T>::ABB(const T & e): arbolbb(e){}

template <class T>
bool ABB<T>::Buscar(typename bintree<T>::node n, const T & e) const{
        if(n.null()){
            return false;
        }else if(*n == e){
            return true;
        }else{
            if(e<*n){
                return Buscar(n.left(), e);
            }else{
                return Buscar(n.right(), e);
            }
        }
    }

template <class T>
bool ABB<T>::Existe (const T & e) const{
        /*Recursivamente: todas las etiquetas del subárbol izquierdo de
        un nodo x son menores que el elemento almacenado en x, y
        las etiquetas del subárbol derecho de un nodo x son mayores
        que él*/
        return Buscar(arbolbb.root(), e);       
    }

template <class T>
void ABB<T>::InsertarRecursivo(typename bintree<T>::node n, const T & e){
        if(*n == e){
            return;
        }else if(e<*n){
            if (n.left().null()) {
                arbolbb.insert_left(n, e);
            } else {
                InsertarRecursivo(n.left(), e);
            }
        }else{
            if(n.right().null()){
                arbolbb.insert_right(n, e);
            }else{
                InsertarRecursivo(n.right(), e);
            }
        }
    }

template <class T>
void ABB<T>::insertar (const T & e){
        if(arbolbb.empty()){
            arbolbb = bintree<T>(e);
        }else{
            InsertarRecursivo(arbolbb.root(), e);
        }
    }

template <class T>
void ABB<T>::borrar (const T & elem){
    if(arbolbb.empty()){
        return;
    }

        T e = elem;
        typename bintree<T>::node n = arbolbb.root();
        bool encontrado = false;
        while(!encontrado && !n.null()){
            if(e == *n){
                encontrado = true;
                if(n.left().null() && n.right().null()){//el nodo es una hoja 
                    bintree<T> dest;
                    if(n.parent().null()){ //el árbol solo tiene un nodo, Borra la raiz
                        arbolbb.clear();
                    }else if(n == n.parent().left()){ //Hoja izquierda
                        arbolbb.prune_left(n.parent(), dest);
                    }else{ //Hoja derecha
                        arbolbb.prune_right(n.parent(), dest);
                    }
                    return;
                }else if(n.left().null()){ //El nodo sólo tiene un hijo a la derecha
                    bintree<T> rama_hijo;
                    bintree<T> dest;
                    typename bintree<T>::node p = n.parent();
                    arbolbb.prune_right(n, rama_hijo);

                    if(n.parent().null()){
                        arbolbb = rama_hijo;
                    }else if(n == n.parent().left()){
                        arbolbb.prune_left(n.parent(), dest);
                        arbolbb.insert_left(p, rama_hijo);
                    }else{
                        arbolbb.prune_right(n.parent(), dest);
                        arbolbb.insert_right(p, rama_hijo);
                    }
                    return;
                }else if(n.right().null()){ //El nodo sólo tiene un hijo a la izquierda
                    bintree<T> rama_hijo;
                    bintree<T> dest;
                    typename bintree<T>::node p = n.parent();
                    arbolbb.prune_left(n, rama_hijo);

                    if(n.parent().null()){
                        arbolbb = rama_hijo;
                    }else if(n == n.parent().left()){
                        arbolbb.prune_left(n.parent(), dest);
                        arbolbb.insert_left(p, rama_hijo);
                    }else{
                        arbolbb.prune_right(n.parent(), dest);
                        arbolbb.insert_right(p, rama_hijo);
                    }
                    return;
                }else{ //el nodo tiene dos hijos
                    //Buscar el mayor hijo a la izquierda
                    typename bintree<T>::node mhi = n.left();
                    while(!mhi.right().null()){
                        mhi = mhi.right();
                    }
                    T valor_mhi = *mhi;
                    *n = valor_mhi;
                    // Ahora buscamos y eliminamos mhi (que es hoja o tiene solo hijo izquierdo)
                    n = n.left();
                    encontrado = false;
                    e = valor_mhi;
                }
            }else if(e < *n){
                n = n.left();
            }else{
                n = n.right();
            }
        }
}

template <class T>
ABB<T>::iterator::iterator() {}

template <class T>
ABB<T>::iterator::iterator(typename bintree<T>::inorder_iterator i) : it(i) {}

template <class T>
T & ABB<T>::iterator::operator*() {
    return *it; 
}

template <class T>
typename ABB<T>::iterator & ABB<T>::iterator::operator++() {
    ++it;
    return *this;
}

template <class T>
bool ABB<T>::iterator::operator==(const iterator &i) const {
    return it == i.it;
}

template <class T>
bool ABB<T>::iterator::operator!=(const iterator &i) const {
    return it != i.it;
}

template <class T>
typename ABB<T>::iterator ABB<T>::begin(){
    return iterator(arbolbb.begin_inorder());
}

template <class T>
typename ABB<T>::iterator ABB<T>::end(){
    return iterator(arbolbb.end_inorder());
}

template <class T>
ABB<T>::~ABB(){}

template class ABB<int>;