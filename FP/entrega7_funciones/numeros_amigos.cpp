/**
  * @file numeros_amigos.cpp
  * @brief Comprueba si dos números son amigos
  *
  * @author Fulanito...
  * @date Mes-Año
  *
  * Escriba un programa que lea dos números enteros positivos y escriba en la
  * salida estándar si son amigos.
  *
  * Dos números a y b se dicen amigos si a es la suma de los divisores propios
  * de b y b es la suma de los divisores propios de a. Los divisores propios
  * de un número n son todos sus divisores, incluido el uno, salvo el propio n.
  *
  * Una posible ejecución sería la siguiente:
  *      Introduzca un número entero positivo: 220
  *      Introduzca un número entero positivo: 284
  *      Los números 220 y 284 son amigos
  *
  * Otro ejemplo es:
  *      Introduzca un número entero positivo: -10
  *      Error, no es positivo. Inténtelo de nuevo: 30
  *      Introduzca un número entero positivo: 20
  *      Los números 30 y 20 no son amigos.
  *
  * El problema debe diseñarse con funciones. Debe incluir al menos las siguientes:
  *    - Una función para leer un entero hasta que sea positivo.
  *    - Una función para sumar los divisores propios de un entero positivo.
  *    - Una función para comprobar si dos números son amigos.
  *
  */
#include <iostream>

using namespace std;

bool EsPositivo(int n){
  if(n<0){
    cout<<"Error, no es positivo. Inténtelo de nuevo: ";
    return false;
  }else{
    return true;
  }
}
int SumaDiv(int n){
  int suma=0;
  for(int i = 1; i<=n/2; i++){
    if(n%i==0){
      suma=suma+i;
    }
  }
  return suma;
}
bool SonAmigos(int a, int b){
  int sumaA=SumaDiv(a);
  int sumaB=SumaDiv(b);

  if(sumaA==b && sumaB==a){
    return true;
  }else{
    return false;
  }
}

int main(){
  int a, b;

  cout<<"Introduzca un número entero positivo: ";
  cin>>a;
  while(!EsPositivo(a)){
    cin>>a;
  }
  cout<<"Introduzca un número entero positivo: ";
  cin>>b;
  while(!EsPositivo(b)){
    cin>>b;
  }
  if(SonAmigos(a,b)){
    cout<<"Los números "<< a <<" y "<< b <<" son amigos";
  }else{
    cout<<"Los números "<< a <<" y "<< b <<" no son amigos";
  }
}