/**
  * @file poligono_regular.cpp
  * @brief Medidas desde polígono regular (Ej. 1.21)
  *
  * @author Fulanito...
  * @date Mes-Año
  *
  * Escriba un programa C++ para el análisis de polígonos regulares. Tiene como
  * entradas la longitud del lado (a), y el número de lados (k). Como salida
  * deberá escribir en la salida estándar los siguientes valores:
  *
  *   - El perímetro del polígono.
  *   - El ángulo entre dos lados consecutivos.
  *   - El radio del círculo inscrito.
  *   - El radio del círculo circunscrito.
  *   - El área.
  *
  * Las expresiones asociadas las puede consultar en el ejercicio 1.21.
  *
  */
  #include <iostream>
  #include <cmath>
  using namespace std;

  int main(){
    double a, k;
    double per, ang, rin, rci, area;

    cout<<"escribe la longitud de los lados: "<<endl;
    cin>>a;

    cout<<"escribe el numero de lados: "<<endl;
    cin>>k;

    per = a*k;
    cout<<"El perimetro del poligono regular es: "<<per<<endl;

    ang = ((k-2)*180)/k;
    cout<<"El angulo entre lados consecutivos es: "<<ang<<endl;

    double pi;
    pi = 3.1416;

    rin = (0.5)*a*(1/tan(pi/k));
    cout<<"El radio de la circunferencia inscrita en el poligono regular es: "<<rin<<endl;

    rci = (0.5)*a*(1/sin(pi/k));
    cout<<"El radio de la circunferencia circunscrita en el poligono regular es: "<<rci<<endl;

    area = k*pow(rin,2)*tan(pi/k);
    cout<<"El area del poligono regular es: "<<area<<endl;

    return 0;

  }
