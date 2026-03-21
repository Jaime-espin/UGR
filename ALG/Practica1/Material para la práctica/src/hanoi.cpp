/**
   @file Solucion del problema de las Torres de Hanoi
*/

#include <iostream>
#include <chrono>
#include <string>
#include <ctime>
#include <cstdlib>
using namespace std;

/**
   @brief Resuelve el problema de las Torres de Hanoi
   @param M: numero de discos. M > 1.
   @param i: numero de columna en que estan los discos.
             i es un valor de {1, 2, 3}. i != j.
   @param j: numero de columna a que se llevan los discos.
             j es un valor de {1, 2, 3}. j != i.

   Esta funcion imprime en la salida estandar la secuencia de 
   movimientos necesarios para desplazar los M discos de la
   columna i a la j, observando la restriccion de que ningun
   disco se puede situar sobre otro de tamaño menor. Utiliza
   una unica columna auxiliar.
*/
void hanoi (int M, int i, int j);

void hanoi (int M, int i, int j)
{
  if (M > 0)
    {
      hanoi(M-1, i, 6-i-j);
      //cerr << i << " -> " << j << endl;  // Movimientos a stderr para no contaminar stdout
      hanoi (M-1, 6-i-j, j);
  }
}

int main(int argc, char * argv[])
{
  
    if (argc != 2)
    {
      cerr << "Formato " << argv[0] << " <num_discos>" << endl;
      return -1;
    }

  int M = atoi(argv[1]);

  auto inicio = chrono::high_resolution_clock::now();
  hanoi(M, 1, 2);
  auto fin = chrono::high_resolution_clock::now();
  
  chrono::duration<double> duracion = fin - inicio;
  double tiempo = duracion.count();

  string tiempo_str = to_string(tiempo);
  for(auto& c : tiempo_str) if(c == '.') c = ',';
  cout << M << ";" << tiempo_str << endl;

  return 0;
}
