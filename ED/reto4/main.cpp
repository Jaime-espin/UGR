/*Arcvivo para porbar la clase ABB*/
#include "abb.h"
#include <iostream>
using namespace std;

void imprimir_abb( ABB<int> arbol) {
    for(ABB<int>::iterator it = arbol.begin(); it != arbol.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
}

// Función para imprimir el árbol gráficamente (de usoarbolbinario.cpp)
template <class T>
void Esquema(const bintree<T>& a, 
             const typename bintree<T>::node n, string& pre){
  if (n.null())
    cout << pre << "-- x" << endl;
  else {
    cout << pre << "-- " << *n << endl;
    if (!n.right().null() || !n.left().null()) {// Si no es una hoja
      pre += "   |";
      Esquema(a, n.right(), pre);
      pre.replace(pre.size()-4, 4, "    ");
      Esquema (a, n.left(), pre);
      pre.erase(pre.size()-4, 4);    
    }
  }
}

void imprimir_grafico(ABB<int>& arbol, const string& mensaje) {
    cout << "\n" << mensaje << ":" << endl;
    string pre = "";
    Esquema(arbol.getArbol(), arbol.getArbol().root(), pre);
}

int main(){
    ABB<int> arbol;

    arbol.insertar(50);
    arbol.insertar(30);
    arbol.insertar(70);
    arbol.insertar(60);
    arbol.insertar(80);
    arbol.insertar(40);

    string pre = "";
    imprimir_abb(arbol);
    cout<<endl;
    Esquema(arbol.getArbol(), arbol.getArbol().root(), pre);

    arbol.borrar(80);
    pre = "";
    imprimir_abb(arbol);
    cout<<endl;
    Esquema(arbol.getArbol(), arbol.getArbol().root(), pre);

    arbol.borrar(70); 
    pre = "";
    imprimir_abb(arbol);
    cout<<endl;
    Esquema(arbol.getArbol(), arbol.getArbol().root(), pre);

    arbol.borrar(50);
    pre = "";
    imprimir_abb(arbol);
    cout<<endl;
    Esquema(arbol.getArbol(), arbol.getArbol().root(), pre);
    
    // Prueba de búsqueda
    cout << "Existe 30? " << (arbol.Existe(30) ? "Sí" : "No") << endl;
    cout << "Existe 50? " << (arbol.Existe(50) ? "Sí" : "No") << endl;

    return 0;
}