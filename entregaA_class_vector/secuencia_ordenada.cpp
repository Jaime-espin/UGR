/**
  * @file secuencia_ordenada.cpp
  * @brief Lee una secuencia de enteros y la imprime ordenada
  *
  * @author Fulanito...
  * @date Mes-Año
  *
  * Escriba un programa que obtenga en la salida estándar los mismos enteros
  * hemos introducido pero ordenados de menor a mayor.
  *
  * Para resolver el problema, se determina que se va a diseñar un nuevo tipo
  * secuencia que nos permita almacenar la secuencia de enteros para una futura
  * ampliación o modificación.
  *
  * El diseño propuesto consiste en declarar un vector-C con un tamaño suficiente
  * y controlar el número de enteros que se usen. Las operaciones que debe
  * añadir son:
  *    - Constructor por defecto que inicializa la secuencia vacía.
  *    - capacity: devuelve la capacidad máxima de almacenamiento del objeto.
  *    - size: devuelve el número de posiciones usadas, las que almacenan un dato.
  *    - add: añade un elemento a la secuencia.
  *    - get: consulta el valor de un elemento almacenado en la posición i.
  *    - erase: elimina el valor de un elemento almacenado en una posición i.
  *
  * Como condiciones para que el objeto sea válido se debe cumplir que:
  *    - add no es válido si size==capacity
  *    - get de una posición i debe cumplir que 0 <= i < size
  *    - erase no es válido si no cumple que 0 <= i < size
  *
  * Estas condiciones se deben cumplir siempre. Por tanto el usuario de la clase
  * debe tener cuidado de usarlas correctamente. Para que la clase garantice que el
  * usuario no ha violado ninguna de las condiciones, el programador de la clase
  * insertará condiciones con assert para parar el programa en caso de este uso
  * incorrecto.
  *
  * La función main deberá declarar un objeto de la clase y a través de su interfaz
  * resolver el problema de ordenar una secuencia de enteros.
  *
  * La entrada consiste en un entero que indica el número de datos seguido de dichos
  * datos. Un ejemplo de ejecución es:
  *     9   3 5 4 2 1 8 5 7 6
  *     9   1 2 3 4 5 5 6 7 8
  *
  * donde la primera línea es la entrada y la segunda la salida.
  *
  * Tenga en cuenta que si la entrada es un valor demasiado grande (mayor que la
  * capacidad) deberá indicar el error. Un ejemplo de ejecución es:
  *     100000
  *     Error, el tamaño excede la capacidad (1000)
  *
  * donde hemos supuesto una capacidad del tipo de 1000 posiciones y se ha introducido
  * un número de elementos superior.
  *
  */
#include <iostream>
#include <cassert>

using namespace std;

class Secuencia{
  static const int MAX=100;
  int v[MAX];

  public:
  Secuencia(){
    for(int i=0; i<MAX; i++){
      v[i]=0;
    }
    int i=0;
  };
  int capacity(){return MAX;};
  int size(){
    int i=0;
    while (v[i]!=0){
      i++;
    }
    return i;
  };
  void add(int n){
    assert(size()!=capacity());
    int i=size();
    v[i++]=n;
  };
  void erase(int i){
    assert(i <= 0 || i < size());
    v[i] = 0;
  };
  int get(int i){
    assert(i >= 0 || i > size());
    return v[i];
  };
  void ordenar() {
    for (int i = 0; i < size() - 1; ++i) {
      for (int j = 0; j < size() - i - 1; ++j) {
        if (v[j] > v[j + 1]) {
          int temp = v[j];
          v[j] = v[j + 1];
          v[j + 1] = temp;
        }
      }
    }
  }
  void escribir(){
    cout<<size()<<"   ";
    for (int i = 0; i < size(); ++i) {
      cout << v[i] << " ";
    }
    cout <<endl;
  }
};

int main(){
  Secuencia s;
  int n, max;
  
  cin>>max;
  if (max >= s.capacity()) {
    cout << "Error, el tamaño excede la capacidad (" << s.capacity() << ")" << endl;
    assert(false);
  }  
  for(int i=0; i<max;i++){
    cin>>n;
    s.add(n);
  }

  s.ordenar();

  s.escribir();
}