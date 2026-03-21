/**
  * @file separar_pares_impares.cpp
  * @brief Programa para separar los pares/impares de una secuencia
  *
  * @author Fulanito...
  * @date Mes-Año
  *
  * Escriba un programa que lee una secuencia de números enteros y una vez cargada
  * muestra dos listas de números, primero los pares y luego los impares. 
  *
  * Un ejemplo de ejecución es:
  *    Introduzca secuencia: 6  2 6 7 1 3 5
  *    2   2 6
  *    4   7 1 3 5
  * 
  * donde las dos últimas líneas son la salida, la primera la lista de pares y la
  * segunda la de los impares.
  *
  * Otro ejemplo es:
  *    Introduzca secuencia: 5  2 8 6 4 2
  *    5  2 8 6 4 2
  *    0
  * 
  * Para resolver el problema deberá crear una clase que permita almacenar una
  * secuencia de enteros. El diseño propuesto consiste en declarar un vector-C con un 
  * tamaño suficiente y controlar el número de posiciones que se usen. Las operaciones
  * que debe añadir son:
  *    - Constructor por defecto que inicializa la secuencia vacía.
  *    - capacity: devuelve la capacidad máxima de almacenamiento del objeto.
  *    - size: devuelve el número de posiciones usadas, las que almacenan un entero.
  *    - push_back: añade un elemento al final de la secuencia.
  *    - pop_back: elimina el último elemento de la secuencia.
  *    - set: cambia el valor de un elemento almacenado en una posición i.
  *    - get: consulta el valor de un elemento almacenado en una posición i.
  *
  * Como condiciones para que el objeto sea válido se debe cumplir que:
  *    - push_back no es válido si size==capacity
  *    - pop_back no es válido si size==0
  *    - set en una posición i debe cumplir que 0 <= i < size
  *    - get de una posición i debe cumplir que 0 <= i < size
  *
  * Estas condiciones se deben cumplir siempre. Por tanto el usuario de la clase
  * debe tener cuidado de usarlas correctamente. Para que la clase garantice que el
  * usuario no ha violado ninguna de las condiciones, el programador de la clase
  * insertará condiciones con assert para parar el programa en caso de este uso
  * incorrecto. 
  * 
  * Observe que habrá que imprimir dos listas, por tanto será recomendable crear una
  * función de escritura de una secuencia para llamarla dos veces.
  *
  */
#include <iostream>
#include <cassert>

using namespace std;

class Lista{
  static const int MAX=100;
  int v[MAX];

  public:
  Lista(){
    for(int i=0; i<MAX; i++){
      v[i]=0;
    }
    int i=0;
  };
  void set(int n, int i){ 
    assert(i >= 0 || i < size());
    v[i]=n;
  };
  int capacity(){return MAX;};
  int size(){
    int i=0;
    while (v[i]!=0){
      i++;
    }
    return i;
  };
  void push_back(int n){
    assert(size()!=capacity());
    int i=size();
    v[i++]=n;
  };
  void pop_back(){
    assert(size()!=0);
    int i=size();
    v[i--] = 0;
  };
  int get(int i){
    assert(i >= 0 || i > size());
    return v[i];
    };
  void escribir(){
    cout<<size()<<"   ";
    for (int i = 0; i < size(); ++i) {
      cout << v[i] << " ";
    }
    cout <<endl;
  }
};

int main(){
  int n, max;
  Lista pares;
  Lista impares;
  cout<<"Introduzca secuencia: ";
  cin>>max;
  for(int i=0; i<max;i++){
    cin>>n;
    if(n%2==0){
      pares.push_back(n);
    }else if(n%2!=0){
      impares.push_back(n);
    }
  }

  pares.escribir();
  impares.escribir();
}