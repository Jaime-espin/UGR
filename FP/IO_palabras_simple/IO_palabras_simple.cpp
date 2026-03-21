/**
  * @file IO_palabras_simple.cpp
  * @brief Lee palabras como string con un formato muy simple
  *
  * @author Fulanito...
  * @date Mes-Año
  *
  * Escriba un programa C++ que lea una lista de palabras y las escriba
  * de forma ordenada. Para este problema, deberá tener en cuenta:
  * 
  * - Una palabra se puede leer con cin >> s, con s un string
  * - Dos string se pueden comparar con operadores relacionales.
  * - Un string se puede escribir con cout << s
  * 
  * El programa deberá realizarse enteramente en la función main. Deberá
  * leer un formato compuesto por:
  * - Un entero que indica el número de palabras.
  * - Una secuencia de palabras separadas por "espacios blancos".
  * 
  * El resultado tiene el mismo formato, es decir, un entero con el número
  * de palabras y la secuencia con las palabras ordenadas lexicográficamente 
  * de menor a mayor (con los operadores relacionales del lenguaje).
  * 
  * No incluya ningún código que se refiera a procesamiento de caracteres ASCII
  * ni codificación particular. Suponga que las letras son del alfabeto inglés.
  * 
  * Un ejemplo de ejecución es:
  *    5 uno dos tres cuatro cinco
  *    5 cinco cuatro dos tres uno
  * 
  *
  */
 #include <iostream>
 #include <string>
 using namespace std;

 int main(){
  int n;
  string s[1000];
  string aux;

  cin>>n;
  for(int i=0; i<n; i++){
    cin>>s[i];
  }

  for (int i = 0; i < n - 1; i++) {
    for (int j = 0; j < n - i - 1; j++) {
      if (s[j] > s[j + 1]) {
        aux = s[j];
        s[j] = s[j + 1];
        s[j + 1] = aux;
      }
    }
  }

  for(int i=0; i < n; i++){
    cout<<s[i]<<" ";
  }

 }
