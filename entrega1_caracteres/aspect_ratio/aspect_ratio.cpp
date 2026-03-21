#include <iostream>
#include <cmath>
using namespace std;

int main() {
  int ancho, alto;
  double anchoCM, altoCM;
  double anchoPulg, altoPulg;
  double diagonal, diagonalCM;
  double x;
  char c;
  cout << "Relación de aspecto. Ancho y alto (por ejemplo 4:3): ";
  cin >> ancho;
  cin >> c;
  cin >> alto;
  cout << "Diagonal (pulgadas): ";
  cin >> diagonal;
  diagonalCM = diagonal * 2.54;
  x = diagonalCM / sqrt(ancho * ancho + alto * alto);
  anchoCM = ancho * x;
  altoCM = alto * x;
  anchoPulg = anchoCM / 2.54;
  altoPulg = altoCM / 2.54;

  cout << "Ancho: " << anchoPulg << " pulgadas, " << anchoCM << " cms" << endl;
  cout << "Alto: " << altoPulg << " pulgadas, " << altoCM << " cms" << endl;
  return 0;
}
