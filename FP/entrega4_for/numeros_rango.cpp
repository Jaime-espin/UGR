/**
  * @file numeros_rango.cpp
  * @brief Comprobación de números incluidos en un rango (ej. 3.16)
  *
  * @author Fulanito...
  * @date Mes-Año
  *
  * Escriba un programa que lea un entero y dos números reales: n, min y max.
  * Estos valores indican que hay n números de entrada y que deberían estar
  * en el intervalo [min,max].
  *
  * A continuación, deberá leer los n valores de entrada y confirmar que
  * todos están en el intervalo indicado. En caso de que uno de los valores
  * no lo esté, parará la lectura y terminará el programa indicando que hay
  * valores fuera de rango. Resuelva el ejercicio usando un ciclo for.
  *
  * A continuación se muestran dos posibles ejecuciones de este programa:
  *
  *      N, min, max: 3 0.0 5.0
  *      Introduzca valor 0: 2.3
  *      Introduzca valor 1: 2
  *      Introduzca valor 2: 5.0
  *      Los 3 valores introducidos están en el intervalo [0.0,5.0]
  *
  * Una ejecución en la que hay un valor fuera de rango:
  *
  *      N, min, max: 3 0.0 10.0
  *      Introduzca valor 0: 12
  *      Error. Finalización inesperada del programa: Valor fuera de rango.
  */
#include <iostream>
using namespace std;

int main(){
    int N, contador;
    double min, max;
    double valor;
    contador = 0;
    cout << "N, min, max: ";
    cin>>N>>min>>max;
    
    for (int i = 0; i < N; i++){
        cout<<"Introduzca un valor " << i << ": ";
        cin>> valor;
        if (valor < min || valor > max){
            cout << "Error. Finalizacion inesperada del programa: Valor fuera de rango." << endl;
            i = N;
       }
        contador ++;
    }
    if (contador == N){
    cout << "Los " << N << " valores introducidos estan en el intervalo [" << min << "," << max << "]" << endl;
    }
}

