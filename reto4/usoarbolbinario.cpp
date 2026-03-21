#include <iostream>
#include "bintree.h"
#include<queue>
#include<list>
#include<algorithm>
#include <limits>

using namespace std;


//Esquema de un arbol
template <class T>
void Esquema(const bintree<T>& a, 
             const typename bintree<T>::node n, string& pre){
  int i;
  
  if (n.null())
    cout << pre << "-- x" << endl;
  else {
    cout << pre << "-- " << *n << endl;
    if (n.right()!=0 || n.left()!=0) {// Si no es una hoja
      pre += "   |";
      Esquema(a, n.right(), pre);
      pre.replace(pre.size()-4, 4, "    ");
      Esquema (a, n.left(), pre);
      pre.erase(pre.size()-4, 4);    
    }
  }
}
//función altura.
template <class T>
int Altura(const bintree<T>& a, 
           const typename bintree<T>::node n){
  int iz,de;
  if (n.null())
    return -1;
  else {
    iz= Altura(a,n.left());
    de= Altura(a,n.right());
    return 1+(iz>de?iz:de);
  }
}

template <class T>
bool esHoja(const bintree<T> & A, const typename bintree<T>::node &v)
{
  return ( v.left().null()  && v.right().null() );
}



template <class T>
bool esInterno(const bintree<T> & A, const typename bintree<T>::node &v)
{
  return ( !v.left().null() || !v.right().null() );
}

template <class T>
void PreordenBinario(const bintree<T> & A,
typename bintree<T>::node v) {
  if (!v.null()) {
       cout << *v; // acción sobre el nodo v.
       PreordenBinario(A, v.left());
       PreordenBinario(A, v.right());
  }
}

template <class T>
void InordenBinario(const bintree<T> & A,
 typename bintree<T>::node v)
{
  if (!v.null()) {
       InordenBinario(A, v.left());
       cout << *v; //acción sobre el nodo v.
       InordenBinario(A, v.right());
  }
}

template <class T>
void PostordenBinario(const bintree<T> & A,
 typename bintree<T>::node v)
{
  if (!v.null()) {
       PostordenBinario(A, v.left());
       PostordenBinario(A, v.right());
       cout << *v; // acción sobre el nodo v.
  }
}

template <class T>
void ListarPostNiveles(const bintree<T> &A, typename bintree<T>::node n) {
  queue<typename bintree<T>::node> nodos;
  if (!n.null()) {
    nodos.push(n);
    while (!nodos.empty()) {
      n = nodos.front(); nodos.pop();
      cout << *n;
      if (!n.left().null()) nodos.push(n.left());
      if (!n.right().null())
         nodos.push(n.right());
    }
  }
}


template <class T>
ostream & operator << (ostream & os, bintree<T> &arb)
{
  
cout << "Preorden:";

for (typename bintree<T>::preorder_iterator i = arb.begin_preorder(); i!=arb.end_preorder(); ++i)
  cout << *i << " ";

cout << endl;
return os;
}

int numerocaminos (bintree<int> &ab, int k, bintree<int>::node n)
{
    
    if (n.left().null() && n.right().null())
        if (*n==k) return 1;
        else return 0;
    else{
           int contador=0;
           if (!n.left().null())
               contador+=numerocaminos(ab, k-*n, n.left());
           if (!n.right().null())
               contador+=numerocaminos(ab, k-*n, n.right());
           return contador;
        }
    
}



void Imprimir (list<int> & l){
    list<int>::iterator it;
   for (it=l.begin();it!=l.end();++it){
       cout<<*it<<" ";
   }
   cout<<endl;
}   

pair<int,list<int>> caminomen_nodo(bintree<int>::node n){
	
	if (n.null())
	 return pair<int,list<int>>(numeric_limits<int>::max(),list<int>());
	else
	 if (n.left().null() && n.right().null())//Paramos en la hoja
	  return pair<int,list<int>>(*n,list<int>(1,*n));
	else{
		pair<int,list<int>> li=caminomen_nodo(n.left());
		pair<int,list<int>> ld=caminomen_nodo(n.right());
		if (li.first<ld.first){
			li.second.push_front(*n);
			li.first+=*n;
			return li;
        }
        else{
			ld.second.push_front(*n);
			ld.first+=*n;
			return ld;
        }
	}				
	
}	
list<int> caminodemenores(bintree<int> &ab){
    return caminomen_nodo(ab.root()).second;
}

int contabiliza (bintree<int>::node n){
if (n.null())
return 0;
else{
return 1+contabiliza(n.left())+contabiliza(n.right());
}
}
list<int> knodos_n (bintree<int>::node n, int k){
   if (n.null())
       return list<int>();
   else{
          int ci=contabiliza(n.left());
          int cd=contabiliza(n.right());
          list<int> lout,li,ld;
          if (abs(ci-cd)>=k)
                lout.push_back(*n);
          li=knodos_n(n.left(),k);
          ld=knodos_n(n.right(),k);
          /*lout.merge(li);
          lout.merge(ld);*/
          lout.splice(lout.end(), li);
          lout.splice(lout.end(), ld);
return lout;
      }
}
list<int> knodos (bintree<int> & A, int k){
        return knodos_n(A.root(),k);
}




        
int main()
{ // Creamos el árbol:
  //        7
  //     /    \
  //    1      9
  //  /  \    /
  // 6    8  5
  //       \
  //       4
// Ejercicio 1 Crear otro arbol para leer.
  //Creamos el árbol:
  //        3
  //      /   \
  //     6     11
  //   /  \   / \
  //  7   10  5   4
  //      
  //              
typedef bintree<int> bti;
list<int> listanodos;
list<int> listaknodos;
bintree<int> Arb(3);
Arb.insert_left(Arb.root(), 6);
Arb.insert_right(Arb.root(), 11);

Arb.insert_left(Arb.root().left(), 7);
Arb.insert_right(Arb.root().left(), 10);


Arb.insert_left(Arb.root().right(), 5);
Arb.insert_right(Arb.root().right(),4);




string pre= " ";
Esquema(Arb,Arb.root(),pre);


cout << *Arb.root().left() << endl;

int longitud=4;

cout << "Num caminos:  " <<numerocaminos(Arb, longitud, Arb.root()) <<endl;
cout << "Altura: "<<Altura(Arb,Arb.root())<< endl;
//cout << "Num. Hojas: "<<ContarHojas(Arb)<< endl;

cout << "caminosminimos:" <<endl;
listanodos=caminodemenores(Arb);


Imprimir(listanodos);

cout << "listaknodos:" <<endl;

int k=2;
listaknodos= knodos(Arb, k);

Imprimir(listaknodos);
                    
cout << "Preorden:";

for (bintree<int>::preorder_iterator i = Arb.begin_preorder(); i!=Arb.end_preorder(); ++i)
  cout << *i << " ";

cout << endl;


cout << "Inorden:";

for (bintree<int>::inorder_iterator i = Arb.begin_inorder(); i!=Arb.end_inorder(); ++i)
  cout << *i << " ";

cout << endl;


cout << "Postorden:";

for (bintree<int>::postorder_iterator i = Arb.begin_postorder(); i!=Arb.end_postorder(); ++i)
  cout << *i << " ";

cout << endl;


cout << "Por Niveles:";

for (bintree<int>::level_iterator i = Arb.begin_level(); i!=Arb.end_level(); ++i)
  cout << *i << " ";

cout << endl;


bintree<int> original(3), copia;

  original.insert_left(original.root(), 2);
  original.insert_right(original.root(), 4);
  
  string pre2= " ";
  Esquema(original,original.root(),pre2);


  copia.replace_subtree(copia.root(), original, original.root());
  
  string pre3= " ";
  Esquema(copia,copia.root(),pre3);

  bintree <int> destino;
  
  original.prune_left(original.root(), destino);
  

  cout << "Preorden de la copia (hay 3 elementos): ";
  for_each(copia.begin_preorder(), copia.end_preorder(), [] (int n) { cout << n << " "; });
  cout <<  endl;


  cout << "Tamaño del bintree original: " << original.size() << endl;
  cout << "Tamaño copia: " << copia.size() << endl;
  

  string pre4= " ";
  Esquema(destino,destino.root(),pre4);
  
  cout << "Tamaño del bintree destino: " << destino.size() << endl;
  cout << "Tamaño original: " << original.size() << endl;
  
  
  bintree <int> asignac (Arb);
  
  
  cout << "Tamaño del bintree original: " << Arb.size() << endl;
  cout << "Tamaño copia: " << asignac.size() << endl;
  
  
  return 0; 
  
  

}

