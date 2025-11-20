
#include <iostream>
#include <cmath>
using namespace std;

int main () {
    double masaP, radioP, grosorAtm, hNave, mAstronauta;
    double densidadP;
    const double pi = 3.14159265358979323846;
    const double Guniv = 6.6743*pow(10,-11);
    const double dmin = 10;
    double volumenP;
    double Vorbita, Vescape;

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
        cout << "Introduzca la altura de la linea de Karman en metros (0 si no hay atmosfera): ";
        cin >> grosorAtm;
        if (grosorAtm <0) {
            grosorAtm = grosorAtm * -1;
        }
        cout << "Introduzca la altura respecto a la superficie de la nave estelar (metros): ";
        cin >> hNave;
        if (hNave < 0) {
            cout << "Error: Viajando bajo tierra. Fin del programa" << endl;
        } else if (hNave < grosorAtm) {
            cout << "Aviso: No está garantizada la orbita. Fin del programa" << endl;
        }else {
            cout <<"La nave esta en el espacio exterior" << endl;
            Vescape = sqrt((2 * Guniv * masaP) / (radioP+hNave))*(36/10);
            Vorbita = sqrt((Guniv * masaP) / (radioP+hNave))*(36/10);
            cout << "La velocidad de orbita a altura " << hNave << " es: " << Vorbita << " km/h" << endl;
            cout << "La velocidad de escape a altura " << hNave << " es: " << Vescape << " km/h" << endl;
        }
    }
}