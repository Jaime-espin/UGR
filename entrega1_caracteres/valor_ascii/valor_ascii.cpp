#include <iostream>
using namespace std;

int main() {
  char character;
  int ascii;
  cout <<"introduzca un caracter: ";
    cin >> character;

  ascii = character;
  cout << "El valor ASCII de '" << character << "' es: " << ascii << endl;

  return 0;
}
