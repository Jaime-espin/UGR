
#include <iostream>
#include <cmath>
using namespace std;

int main () {
    double masaP, radioP, grosorAtm, hNave, Vorbita, mAstronauta;
    double densidadP;
    const double pi = 3.14159265358979323846;
    const double dmin = 10;
    double volumenP;

    cout <<"Introduzca la masa del planeta (kg) y su radio (m): ";
    cin >> masaP >> radioP;
    volumenP = (4/3) * pi * pow(radioP, 3);
    densidadP = masaP / volumenP;
    if (masaP <= 0 || radioP <= 0) {
        cout << "Error: los valores negativos no son validos. Fin del programa" << endl;
    } else if (densidadP < dmin) {
        cout << "Error: la densidad es demasiado baja. Fin del programa" << endl;
    } else {
        cout << "La densidad media del planeta es: " << densidadP << " kg/m3" << endl;
        cout << "Introduzca la altura de la linea de Karman en metros (0 si no hay atmosfera: ";
        cin >> grosorAtm;
        if (grosorAtm <0) {
            grosorAtm = grosorAtm * -1;
        }
        cout << "La altura se establece en: " << grosorAtm << " m" << endl;
    }
}


