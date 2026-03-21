/**
  * @file media_varianza.cpp
  * @brief Programa para calcular la media y varianza
  *
  * @author Fulanito...
  * @date Mes-Año
  *
  * Escriba un programa que lea un número entero que indica el número de datos a
  * analizar, a continuación lea tantos números reales como indique dicho entero
  * y finalmente escriba la media y la varianza de dichos datos.
  *
  * Consulte la formulación en el ejercicio 3.14 (Media y varianza)
  *
  * Un ejemplo de ejecución es:
  *    ¿Cuántos datos quiere analizar? 3
  *    Introduzca 3 datos: 4 6 8
  *    Media: 6
  *    Varianza: 2.66667
  *
  * donde las dos primeras líneas corresponden a la petición de datos y las dos
  * últimas al resultado.
  *
  */
#include <iostream>
#include <cmath>

using namespace std;

int main(){
    int Ndatos;
    double dato, media, var,sumaM, sumaVar ;
    sumaM = 0.0;
    sumaVar = 0.0;

    cout << "Cuantos datos quiere analizar? ";
    cin >> Ndatos;

    cout << "Introduzca "<<Ndatos << " datos: ";
    for (int i=1; i<= Ndatos; i++){
        cin >> dato;
        sumaM = sumaM + dato;
        sumaVar = sumaVar + pow(dato,2);
    }
    media=((sumaM)/Ndatos);
    cout << "Media: "<<media<<endl;
    var=(sumaVar/Ndatos)-media*media;
    cout << "Varianza: "<<var<<endl;
}
