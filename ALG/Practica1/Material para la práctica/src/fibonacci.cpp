/**
   @file C�lculo de la sucesi�n de Fibonacci
*/

   
#include <iostream>
#include <chrono>
#include <string>
using namespace std;
#include <ctime>


/**
   @brief Calcula el t�rmino n-�simo de la sucesi�n de Fibonacci.

   @param n: n�mero de orden del t�rmino buscado. n >= 1.

   @return: t�rmino n-�simo de la sucesi�n de Fibonacci.
*/
int fibo(int n)
{
  if (n < 2)
    return 1;
  else
    return fibo(n-1) + fibo(n-2);
}


int main(int argc, char * argv[])
{

  if (argc != 2) {
    cerr << "Formato " << argv[0] << " <n>" << endl;
    return -1;
  }

  int n = atoi(argv[1]);
  int f;
 
  auto inicio = chrono::high_resolution_clock::now();
  f = fibo(n);
  auto fin = chrono::high_resolution_clock::now();
  
  chrono::duration<double> duracion = fin - inicio;
  double tiempo = duracion.count();

  string tiempo_str = to_string(tiempo);
  for(auto& c : tiempo_str) if(c == '.') c = ',';
  cout << n << ";" << tiempo_str << endl;

  return 0;
}
