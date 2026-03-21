/**
  * @file racional_basico.cpp
  * @brief Leer y escribir un número racional
  *
  * @author Fulanito...
  * @date Mes-Año
  * 
  * El formato de lectura/escritura de un racional consta de:
  *    - Número entero correspondiente al numerador.
  *    - Carácter '/'.
  *    - Número entero correspondiente al denominador.
  * 
  * admitiendo, opcionalmente, separadores blancos en medio de dichos componentes.
  * 
  * Escriba un programa en C++ que lea un racional desde la entrada estándar y
  * vuelva a escribirlo en la salida estándar.
  *
  * En la solución debe definir una clase para almacenar un número racional. Se
  * debe proteger el acceso a los valores del numerador y denominador para que sólo
  * puedan modificarse mediante las funciones miembro.
  *
  * Al proteger la representación, podremos garantizar que cualquier racional:
  *    - Tiene un valor con un denominador distinto de cero.
  *    - El denominador nunca será negativo. El signo siempre aparece en el numerador.
  *    - El racional es irreducible.
  *
  * Para poder garantizar estas condiciones, deberá crear las siguientes funciones
  * miembro:
  *    - Una función que devuelve el valor del numerador.
  *    - Una función que devuelve el valor del denominador.
  *    - Una función "set" que recibe dos números que representan un racional y
  *      modifica el valor del objeto para almacenar el correpondiente racional.
  *
  * Para que cualquier racional cumpla las condiciones anteriores, debemos añadir
  * un constructor por defecto que garantice que un objeto no contendrá "basura".
  * Puede definir el constructor para inicializarlo al racional 0/1.
  *
  * Para modularizar el código, podemos crear una función miembro privada que
  * modifique los valores del numerador y denominador para que queden normalizados,
  * es decir, si es 0 quedará como 0/1 y si no, quedarán de forma irreducible y con
  * el signo en el numerador.
  *
  * Para probar la clase, se implementará un sencillo main donde básicamente se
  * lee un racional y se vuelva a escribir. Un ejemplo de ejecución sería:
  *
  *    Introduzca un racional: 3/0
  *    Error, el denominador debe ser distinto de cero. Introduzca otro: 4/2
  *    El racional es: 2/1.
  *
  * Para crear esta solución, implemente dos funciones de lectura/escritura. Note
  * que en la lectura debe leer dos variables enteras de forma repetitiva hasta
  * que el denominador sea válido. Después deberá inicializar un racional y
  * devolverlo como resultado.
  *
  * Las dos funciones de lectura y escritura puede realizarlas fuera de la clase,
  * es decir, como funciones globales.
  * 
  * Puede suponer que el usuario introduce el formato indicado. No será necesario,
  * por tanto, controlar posibles errores de entrada como que falte la '/' o se
  * introduzca una letra en lugar de un número.
  * 
  */
#include <iostream>
#include <cassert>

using namespace std;

class Racional{
  int num;
  int den;

  void simplificar(){
    assert(den!=0);
    int n=num;
    int d=den;
    int resto=num%den;
    while(resto!=0){
      n=d;
      d=resto;
      resto=n%d;
  }
  num=num/d;
  den=den/d;
  if(den<0){
    den=-den;
    num=-num;
  }
  }

  public:
    Racional(){
      num=0;
      den=1;
    }
    int getNum(){return num;};
    int getDen(){return den;};
    void set(int n, int d){
      num=n;
      den=d;
      simplificar();
    };
};

int main(){
  int n, d;
  char c;
  cout <<"Introduzca un racional: ";
  cin>> n >> c >> d;
  while(d==0){
    cout<<"Error, el denominador debe ser distinto de cero. Introduzca otro:";
    cin>> n >> c >> d;
  }
  Racional r;
  r.set(n,d);
  cout<<"El racional es: ";
  cout<<r.getNum() <<"/"<<r.getDen();
}