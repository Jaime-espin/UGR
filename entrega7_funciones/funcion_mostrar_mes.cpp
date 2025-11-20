/**
  * @file funcion_mostrar_mes.cpp
  * @brief Muestra en la salida estándar el mes de un determinado año
  *
  * @author Fulanito...
  * @date Mes-Año
  *
  * Escriba un programa que lea dos números, el mes y el año, y que muestre
  * en la salida estándar un esquema formateado del mes.
  *
  * Para resolverlo, puede usar el número juliano para determinar qué
  * día de la semana corresponde al primero de mes. El número se puede
  * obtener con la siguiente fórmula:
  *
  * Día juliano = ( 1461 * ( año + 4800 + ( mes - 14 ) / 12 ) ) / 4 +
  *               ( 367 * ( mes - 2 - 12 * ( ( mes - 14 ) / 12 ) ) ) / 12 -
  *               ( 3 * ( ( año + 4900 + ( mes - 14 ) / 12 ) / 100 ) ) / 4 +
  *               día - 32075
  *
  * Para un determinado día/mes/año se puede calcular el día juliano de forma
  * que si hacemos módulo 7 obtendremos un valor de 0 a 6 que corresponde al
  * día de la semana (de lunes a domingo). Observe que para poder dibujar
  * el mes es necesario saber el día de la semana del día 1 (lo que determina
  * dónde se sitúan el resto de números hasta el final de mes).
  *
  * Para resolver el problema, debería incluir al menos las siguientes funciones:
  *   - Una función que dado un año devuelve si es bisiesto.
  *   - Una función que dado un mes y año devuelve el número de días del mes.
  *   - Una función que dado un mes y año válidos escribe en la salida estándar
  *     el mes formateado.
  * 
  * Una posible ejecución sería la siguiente:
  *      Introduzca mes y año: 2 2020
  *      Lu Ma Mi Ju Vi Sá Do
  *                      1  2
  *       3  4  5  6  7  8  9
  *      10 11 12 13 14 15 16
  *      17 18 19 20 21 22 23
  *      24 25 26 27 28 29
  *
  * Otra ejecución:
  *      Introduzca mes y año: 2 2100
  *      Lu Ma Mi Ju Vi Sá Do
  *       1  2  3  4  5  6  7
  *       8  9 10 11 12 13 14
  *      15 16 17 18 19 20 21
  *      22 23 24 25 26 27 28
  *
  * Para que la función de escritura del mes sea más robusta, se ha decidido que
  * escriba en la salida estándar un error en caso de que el mes y año no estén en
  * el rango válido. Un mes es válido si está en el rango [1,12] y un año es válido
  * si vale al menos 1583.
  *
  * Por ejemplo, una ejecución podría ser:
  *      Introduzca mes y año: 13 2100
  *      El mes 13/2100 no se puede mostrar, valores incorrectos.
  *
  * Otro ejemplo:
  *      Introduzca mes y año: 1 1500
  *      El mes 1/1500 no se puede mostrar, valores incorrectos.
  *
  *
  */
#include <iostream>

using namespace std;

bool EsBisiesto(int año){
  return (año % 4 == 0 && (año % 100 != 0 || año % 400 == 0));
}
int DiasMes(int mes, int año){
  switch (mes) {
    case 1: case 3: case 5: case 7: case 8: case 10: case 12:
      return 31;
    case 4: case 6: case 9: case 11:
      return 30;
    case 2:
      if (EsBisiesto(año)) {
        return 29;
      } else {
        return 28;
      }
  }
}
void MostrarMes(int mes, int año){
  int diaJuliano;
  int dia = 1;
  diaJuliano = ((1461*(año+4800+(mes-14)/12))/4+(367*(mes-2-12*((mes-14)/12)))/12-(3*((año+4900+(mes-14)/12)/100))/4+dia-32075)%7;
  int diasMes = DiasMes(mes, año);
  cout<<"Lu Ma Mi Ju Vi Sá Do"<<endl;
  for(int i = 0; i < diaJuliano; i++){
    cout<<"   ";
  }
  for (int i = 1; i <= diasMes; i++) {
    if (i < 10) {
        cout << " " << i << " ";
    } else {
        cout << i << " ";
    }
    if ((i + diaJuliano) % 7 == 0) {
      cout << endl;
    }
  }
}
int main (){
  int mes, año;
  cout<<"Introduzca mes y año: ";
  cin>>mes>>año;
  if(mes<1 || mes>12 || año<1583){
    cout<<"El mes "<<mes<<"/"<<año<<" no se puede mostrar, valores incorrectos.";
  }else{
    MostrarMes(mes,año);
  }
}