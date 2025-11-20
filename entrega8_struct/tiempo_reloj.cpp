/**
  * @file tiempo_reloj.cpp
  * @brief Ordena dos tiempos introducidos por el teclado
  *
  * @author Fulanito...
  * @date Mes-Año
  * 
  * El formato de escritura de un tiempo consiste en una tripleta con las horas,
  * minutos y segundos. Los tres datos de tipo entero.
  *
  * El formato de escritura de un tiempo consiste en escribir los tres números
  * separados por ':'. Además, en caso de un solo dígito se escriben con un cero
  * adicional a la izquierda.
  *
  * Escriba un programa C++ que lea dos tiempos con el formato anterior y los
  * vuelva a escribir ordenados, primero el menor de ellos. Por ejemplo, si
  * leemos los siguientes tiempos:
  *    7:52:13 5 : 32 : 14
  * 
  * el programa deberá escribir:
  *    05:32:14 07:52:13
  * 
  * Note que la lectura no necesita que los datos estén sin separadores blancos
  * entre los datos ni que se tengan ceros extra a la izquierda. Sólo es necesario
  * que haya un carácter que separa cada uno de los tres componentes.
  * 
  * En el programa deberá incluir:
  *    - Una estructura para almacenar los datos de un tiempo en 3 campos.
  *    - Una función para leer un tiempo según el formato anterior.
  *    - Una función para escribir un tiempo según el formato anterior.
  *    - Una función que devuelva si un tiempo es menor que otro.
  * 
  * Puede suponer que el usuario introduce el formato indicado. No será necesario,
  * por tanto, controlar posibles errores de entrada.
  *
  * Un ejemplo de ejecución es:
  *    Introduzca dos tiempos: 8:1:0 8:0:19
  *    Los tiempos ordenados son: 08:00:19 08:01:00
  * 
  */
#include <iostream>

using namespace std;

struct Tiempo{
  int h;
  int min;
  int s;
};

Tiempo LeerTiempo(){
  Tiempo t;
  char c;
  cin >> t.h >> c >> t.min >> c >> t.s;
  return t;
}
void EscribirTiempo(Tiempo t){
  cout<<t.h<<":"<<t.min<<":"<<t.s<<" ";
}

bool Menor(Tiempo t1, Tiempo t2){
  int t1_total, t2_total;
  t1_total=t1.h*3600+t1.min*60+t1.s;
  t2_total=t2.h*3600+t2.min*60+t2.s;
  if (t1_total < t2_total){
    return true;
  }else{
    return false;
  }
}

int main(){
  Tiempo t1=LeerTiempo();
  Tiempo t2=LeerTiempo();
  if(Menor(t1,t2)){
    EscribirTiempo(t1);
    EscribirTiempo(t2);
  }else{
    EscribirTiempo(t2);
    EscribirTiempo(t1);
  }

}