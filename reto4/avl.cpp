#include "avl.h"
#include "bintree.h"

template <class T>
void AVL<T>::ajustarArbol (typename bintree<T>::node & n){
    int aIzda, aDcha;
    bintree<T>::node hIzda, hDcha;

    //Ajustamos desde n hasta la raíz del árbol
    while(!n.null()){
        aIzda = altura(n.left());
        aDcha = altura(n.right());
        if(abs(aIzda-aDcha)>1){ //Hay que ajustar
            if(aIzda>aDcha){
                hIzda = n.left();
                if(altura(hIzda.left())>altura(hIzda.right())){
                    rotarHijoIzda(n);
                }else{
                    rotarHijoDrcha(hIzda);
                    rotarHijoIzda(n);
                }
            }else{
                hDcha = n.right();
                if(altura(hDcha.left())>altura(hDcha.right())){
                    rotarHijoIzda(hDcha);
                    rotarHijoDrcha(n);
                }else{
                    rotarHijoDrcha(n);
                }
            }
            n=n.parent();
        }
    }
}

template <class T>
int AVL<T>::altura (typename bintree<T>::node & n){
    if(n.null()){
        return 0;
    }else{
        return 1+max(altura(n.left()), altura(n.right()));
    }  
}

template <class T>
void AVL<T>::rotarHijoDrcha (typename bintree<T>::node & n){
    assert(!n.null());
    char que_hijo;
    bintree<T>::node & padre = n.parent();

    //Aislamos el nodo desequilibarado y a su hijo
    //Determinamos la posición del nodo desequilibrado respecto a su padre
    //para la reconexión final.
    bintree<T> A;
    arbolavl.prune_right(n, A);
    bintree<T> Aux;
    if(!padre.null()){
        if(padre.left()==n){
            arbolavl.prune_left(padre, Aux);
            que_hijo = IZDA;
        }else{
            arbolavl.prune_right(padre, Aux);
            que_hijo = DCHA;
        }
    }else{
        Aux = arbolavl;
    }

    //Reesctructuración de ramas
    bintree<T> B;
    A.prune_left(A.root(), B);
    Aux.insert_right(Aux.root(), B);
    A.insert_left(A.root(), Aux);

    //Reenlace final al árbol principal
    if(!padre.null()){
        if(que_hijo==IZDA){
            arbolavl.insert_left(padre, A);
            n = padre.left();
        }else{
            arbolavl.insert_right(padre, A);
            n = padre.right();
        }
    }else{
        arbolavl = A;
        n = arbolavl.root();
    }
}

template <class T>
typename AVL<T>::iterator AVL<T>::begin(){
    return iterator(arbolavl.begin());
}

template <class T>
typename AVL<T>::iterator AVL<T>::end(){
    return iterator(arbolavl.end());
}

template <class T>
AVL<T>::~AVL(){}