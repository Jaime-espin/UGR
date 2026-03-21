#include <iostream>
#include <cmath>
using namespace std;

int main() {
  int h, m, s;
  char c;
  int total_s;
  double porcentaje;
  cout << "Introduzca la hora actual (h:m:s): ";
  cin >> h;
  cin >> c;
  cin >> m;
  cin >> c;
  cin >> s;
  total_s = h * 3600 + m * 60 + s;
  cout << "El tiempo transcurrido de este día es: " << total_s << " segundos" << endl;
  porcentaje = (total_s / 86400.0) * 100;
  cout << "Ha comsumida el " << porcentaje << " % de este día." << endl;
  return 0;
}