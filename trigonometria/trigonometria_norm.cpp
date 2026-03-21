/**
  * @file trigonometria_norm.cpp
  * @brief Cálculos de trigonometría
  *
  * @author Fulanito...
  * @date Mes-Año
  *
  * Escriba un programa C++ que pruebe algunas funciones matemáticas de
  * trigonometría. Deberá usar el seno, coseno y arcotangente.
  *
  * El programa lee un ángulo en grados y muestra en la salida estándar
  * el seno y coseno correspondientes. Además, usará estos dos valores
  * calculados para obtener el valor original que se dio en la entrada
  * usando la arcotangente.
  *
  * Finalmente, escribe el valor original introducido y el valor
  * normalizado en el rango (-180, 180]. Para ello, consulte la función
  * fmod de la biblioteca estándar.
  *
  * Compruebe si son iguales el valor deducido y normalizado presentando
  * la diferencia entre los dos cálculos.
  *
  * Tenga en cuenta que también son válidos los ángulos mayores que 180
  * e incluso negativos. Además, el resultado deberá estar en el intervalo
  * semiabierto (-180,180], es decir, sin incluir -180.
  *
  * Un ejemplo de ejecución es:
  * 
  *   Introduzca ángulo: 30
  *   Seno: 0.5
  *   Coseno: 0.866025
  *   Original deducido desde seno/coseno: 30
  *   Original introducido: 30
  *   Original normalizado: 30
  *   Diferencia con el deducido: 0
  *
  * Otro ejemplo de ejecución:
  * 
  *   Introduzca ángulo: -110.011
  *   Seno: -0.939627
  *   Coseno: -0.342201
  *   Original deducido desde seno/coseno: -110.011
  *   Original introducido: -110.011
  *   Original normalizado: -110.011
  *   Diferencia con el deducido: 1.42109e-14
  * 
  * Observe que aunque el valor no es cero, es casi cero.
  *
  * Otro ejemplo de ejecución:
  * 
  *   Introduzca ángulo: -390
  *   Seno: -0.5
  *   Coseno: 0.866025
  *   Original deducido desde seno/coseno: -30
  *   Original introducido: -390
  *   Original normalizado: -30
  *   Diferencia con el deducido: 4.61853e-14
  * 
  * Otro ejemplo de ejecución:
  *   Introduzca ángulo: -180
  *   Seno: -1.22465e-16
  *   Coseno: -1
  *   Original deducido desde seno/coseno: -180
  *   Original introducido: -180
  *   Original normalizado: 180
  *   Diferencia con el deducido: 360
  * 
  * Otro ejemplo de ejecución:
  *   Introduzca ángulo: 180
  *   Seno: 1.22465e-16
  *   Coseno: -1
  *   Original deducido desde seno/coseno: 180
  *   Original introducido: 180
  *   Original normalizado: 180
  *   Diferencia con el deducido: 0
  *
  * Si necesita la constante pi, defina la constante directamente desde el
  * valor:
  *
  *    Valor de pi -> 3.14159265358979323846
  *
  */
#include <iostream>
#include <cmath>
using namespace std;

int main() {
  double angulo, angulo_rad;
  double seno, coseno;
  cout<<"ingrese un angulo: ";
  cin>>angulo;

  angulo_rad  = angulo * M_PI  / 180.0;
  seno = sin(angulo_rad);
  coseno = cos(angulo_rad);
  cout << "Seno: " << seno << endl;
  cout << "Coseno: " << coseno << endl;

  double deducido, normalizado, diferencia;

  deducido = (atan2(seno,coseno)*180)/M_PI;
  cout << "original deducido del seno/coseno: "<< deducido << endl;
  cout << "el angulo ingresado es: "<< angulo << endl;

  if(angulo>180) {
    normalizado= fmod(angulo+180,360);
    cout << "el angulo normalizado: "<<normalizado<<endl;
  }
  else if(angulo<180) {
    normalizado = fmod(180-angulo,360);
    cout << "el angulo normalizado: "<<normalizado<<endl;
  }
  else {
    normalizado = angulo;
    cout << "el angulo normalizado: "<<normalizado<<endl;
  }

  diferencia = deducido - normalizado;
  cout << "la diferencia es: "<< diferencia << endl;





}
