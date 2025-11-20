/**
  * @file eliminar_char.cpp
  * @brief Programa para eliminar un carácter de un texto
  *
  * @author Fulanito...
  * @date Mes-Año
  *
  * La entrada del programa consiste en:
  *   - Un texto seguido del carácter delimitador '#'
  *   - Un carácter a eliminar.
  * 
  * El resultado del programa será el mismo texto pero donde se han eliminado todas las
  * ocurrencias del carácter a eliminar. En la solución debe:
  * 
  *   -# Cargar el texto en un vector de char.
  *   -# Realizar la eliminación del texto rellenando un segundo vector resultado.
  *   -# Escribir el vector resultado.
  * 
  * Un ejemplo de ejecución es:
  *     *Esto es un* ejemplo,* una frase que debe **salir sin el ***carácter extraño.#*
  *     Esto es un ejemplo, una frase que debe salir sin el carácter extraño.
  *
  * donde la primera línea es la entrada y la segunda la salida.
  */
#include <iostream>

using namespace std;

int main(){
    char c;
    char texto[1000];
    int tamaño = 0;
    int i=0;

    c = cin.get(); 
    while ( c != '#' && i < 1000) {
      if(c != '*'){
        texto[i] = c;
        i ++;
        tamaño++;
      }
      c= cin.get();
    }

    for (int i = 0; i < tamaño; i++) {
        cout << texto[i];
    }
}