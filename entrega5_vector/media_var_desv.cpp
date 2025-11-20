/**
  * @file media_var_desv.cpp
  * @brief Programa para calcular la media, desviación media y varianza de 
  *        una secuencia de valores
  *
  * @author Fulanito...
  * @date Mes-Año
  *
  * Escriba un programa que lee una secuencia de valores en un vector
  * y calcula la media, desviación media y varianza de los valores introducidos.
  * 
  * La entrada de datos consisten en un número entero (el número de datos)
  * seguido de tantos valores reales como indica dicho número.
  * 
  * Corresponde al ejercicio 4.4 del libro de ejercicios, donde puede consultar 
  * las fórmulas que se desean utilizar.
  * 
  * Algunos ejemplos de ejecución son:
  * 
  *     Introduzca secuencia: 5  2.5 3 6 7.1 1 
  *     Media: 3.92
  *     Varianza: 5.1656
  *     Media de desv.: 2.104
  * 
  *     Introduzca secuencia: 0
  *     No hay datos.
  * 
  * Para resolverlo, escriba el código completamente en la función main, sin otras
  * funciones auxiliares. La función main tendrá dos partes, la primera
  * para cargar los datos en un vector y la segunda para resolver el problema.
  */
 #include <iostream>
 #include <cmath>

 using namespace std;

 int main(){
    const int MAX = 100;
    int n;
    double vector[MAX];

    cout << "Introduzca secuencia: ";
    cin >> n;

    if (n<0){
        cout <<"0"<<endl;
    }

    for (int i = 0; i < n; i++) {
        cin >> vector[i];
    }
    cout << endl;

    double suma = 0;
    double media;
    for(int i = 0; i<n;i++){
      suma += vector[i];
    }
    media = suma / n;
    cout << "Media: " << media << endl;

    double sumaVar = 0;
    double var;
    for(int i = 0; i<n;i++){
      sumaVar += (vector[i]-media)*(vector[i]-media);
    }
    var = sumaVar / n;
    cout << "Varianza: " << var << endl;

    double sumaDesv = 0;
    double desv;
    for(int i = 0; i<n;i++){
      sumaDesv += abs(vector[i]-media);
    }
    desv = sumaDesv / n;
    cout << "Media de desviaccion: " << desv << endl;


 }