/**
  * @file numero_perfecto.cpp
  * @brief Comprueba si un número es perfecto
  *
  * @author Fulanito...
  * @date Mes-Año
  *
  * Escriba un programa que lea un número entero positivo y escriba en la
  * salida estándar si es un número perfecto.
  *
  * Un número se dice perfecto si es igual a la suma de sus divisores propios.
  * Los divisores propios de un número n son todos sus divisores, incluido el
  * uno, salvo el propio n.
  *
  * Una posible ejecución sería la siguiente:
  *
  *      Introduzca un número entero positivo: 496
  *      El número 496 es perfecto.
  *
  * Otro ejemplo es:
  *
  *      Introduzca un número entero positivo: -10
  *      Error, no es positivo. Inténtelo de nuevo: 30
  *      El número 30 no es perfecto.
  *
  * El problema deber resolverse en la función main, sin otras funciones.
  *
  */
  #include <iostream>

  using namespace std;

  int main(){
      int n, suma;
      suma = 0;

      cout<<"Introduzca un numero entero positivo: ";
      cin>>n;

      while(n<0){
        cout<<"Error, no es positivo. Intentelo de nuevo: ";
        cin>>n;
      }
      for (int i=1; i < n; i++){
        if (n%i == 0){
                suma=suma+i;
        }
      }
      if (suma==n){
            cout << "El numero "<<n<<" es perfecto"<<endl;
        }else{
            cout <<" El numero " <<n<<" no es perfecto"<<endl;
        }
  }
