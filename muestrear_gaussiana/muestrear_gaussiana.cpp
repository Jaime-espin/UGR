/**
  * @file muestrear_gaussiana.cpp
  * @brief Muestrear una gaussiana
  *
  * @author Fulanito...
  * @date Mes-Año
  *
  * Recuerde que la expresión que define una función gaussiana g(x) es la siguiente:
  *
  * (véase ejercicio 1.20)
  *
  * Escriba un programa C++ que muestree los valores de una gaussiana. El algoritmo debe
  * pedir la media, desviación, intervalo de muestreo y número de muestras. El resultado
  * son las parejas x g(x) que corresponden al muestreo.
  *
  * Por ejemplo, podemos introducir los siguientes valores:
  *    Introduzca media : 1
  *    Introduzca desviación: 2
  *    Intervalo de muestreo: 3 4
  *    Número de muestras: 2
  *    3 0.120985
  *    4 0.0647588
  *
  *  Otro ejemplo con valores x con decimales es:
  *    Introduzca media : 0
  *    Introduzca desviación: 3.5
  *    Intervalo de muestreo: -1 1
  *    Número de muestras: 5
  *    -1 0.109425
  *    -0.5 0.112826
  *    0 0.113984
  *    0.5 0.112826
  *    1 0.109425
  *
  * Tenga en cuenta que el programa para si alguno de los valores no tiene sentido. Las
  * condiciones son:
  *   - La desviación debe ser un valor positivo.
  *   - El intervalo son dos números distintos ordenados
  *   - El número de muestras debe ser al menos 2
  *
  * En cada uno de los tres casos, respectivamente, debe responder con el siguiente mensaje:
  *   - Error: la desviación debe ser positiva
  *   - Error: el extremo izqda debe ser menor que el derecha
  *   - Error: número de datos debe ser al menos 2
  *
  * Por ejemplo, una ejecución con un dato erróneo puede ser:
  *   Introduzca media : 0
  *   Introduzca desviación: -3
  *   Error: la desviación debe ser positiva
  *
  * Observe que el programa termina directamente si se introduce un valor incorrecto, es decir,
  * no sigue la ejecución con el resto de preguntas o los resultados.
  *
  * El diseño de la solución debe incluir una función que calcula el valor de una
  * gaussiana a partir de la media, la desviación y el punto x de evaluación.
  * Intente implementarla de forma eficiente para mejorar los programas que llamen
  * muchas veces a la función.
  *
  * Recuerde que en la solución no se admitirá terminar una función rompiendo el flujo
  * de control en medio del cuerpo de la función (por ejemplo, con return o llamadas
  * a funciones como "exit").
  * 
  */
#include <iostream>
#include <cmath>

using namespace std;

double Gaussiana(double media, double desv, double x){
  double gauss;
  const double PI=3.14159265359;
  gauss = (1 / (desv * sqrt(2 * PI))) * exp(-0.5 * pow((x - media) / desv, 2));
  return gauss;
}

int main(){
  double media, desv;
  int min, max, n;
  cout<<"Introduzca media: ";
  cin>> media;
  cout<<endl;
  cout<<"Introduzca desviacion: ";
  cin>> desv;
  if (desv<0){
    cout<<"Error: la desviación debe ser positiva"<<endl;
    cout<<endl;
  } else{
    cout<<"Intervalo de muestreo: ";
    cin>> min >> max;
    if (min>=max){
      cout<<"Error: el extremo izqda debe ser menor que el derecha"<<endl;
      cout<<endl;
    }else{
      cout<<"Numero de muestras: ";
      cin>> n;
      cout<<endl;
      if (n<2){
        cout<<"Error: número de datos debe ser al menos 2"<<endl;
      }else{
        for(int i=0; i<n ;i++){
          double x;
          x=min+(double(i)/(n-1))*(max-min);
          cout<<x<<" "<<Gaussiana(media,desv,x)<<endl;
        }
      }
    }
  }
}