#include <iostream>
using namespace std;

int main() {
  int num;
  char letra;
  cout << "Introduzca un número de entero: ";
  cin >> num;
  letra = 'A' + num - 1;
  cout << "La letra en mayúscula es: " << letra << endl;
  letra = 'a' + num - 1;
  cout << "La letra en minúscula es: " << letra << endl;
  return 0;

}
