/**
  * @file numero_digitos.cpp
  * @brief Imprime el número de dígitos de un entero positivo
  *
  * @author Fulanito...
  * @date Mes-Año
  * 
  * El programa implementa la lectura de un número entero positivo desde la
  * entrada estándar. Deberá repetir la lectura de un número entero en caso
  * de que no sea positivo.
  * 
  * Una vez leído un número positivo, el programa cuenta el número de dígitos
  * que lo componen. El cálculo deberá realizarse mediante operaciones
  * matemáticas, evitando herramientas de otro tipo como las cadenas o
  * algoritmos ya implementados en la biblioteca estándar.
  * 
  * El resultado final será escribir en la salida estándar el número de dígitos
  * del número.
  * 
  * Un ejemplo de ejecución es el siguiente:
  * 
  *    Introduzca un valor entero positivo: -5
  *    No válido. Debe ser positivo, introduzca otro: 27
  *    El número de dígitos de 27 es 2
  * 
  * En la solución, el problema de calcular el número de dígitos de un número
  * entero positivo debe encapsularse en una función.
  * 
  */
#include <iostream>
using namespace std;

int ContarDig(int n){
  int digitos = 0;
  while(n>0){
    n=n/10;
    digitos++;
  }
  return digitos;
}

int main(){
  int n, digitos;
  cout<<"Introduzca un valor entero positivo: ";
  cin>>n;
  digitos = ContarDig(n);
  while (digitos<=0){
    cout<<"No válido. Debe ser positivo, introduzca otro: ";
    cin>>n;
    digitos = ContarDig(n);
  }

  cout << "El numero de digitos de "<<n<<" es "<<digitos;
}