
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
    double Vnave, porcentaje;
    const double Mtierra = 5.9722 * pow(10, 24);
    const double Rtierra = 6378 * pow(10, 3);
    double pesoRel, pesoP;
    double Gtierra, Gplaneta;

    cout <<"Introduzca la masa del planeta (kg) y su radio (m): ";
    cin >> masaP >> radioP;
    volumenP = (4.0/3.0) * pi * pow(radioP, 3);
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
            Vescape = sqrt((2 * Guniv * masaP) / (radioP+hNave))*(3.6);
            Vorbita = sqrt((Guniv * masaP) / (radioP+hNave))*(3.6);
            cout << "La velocidad de orbita a altura " << Vorbita << " es: " << Vorbita << " km/h" << endl;
            cout << "La velocidad de escape a altura " << Vescape << " es: " << Vescape << " km/h" << endl;

            cout << "Introduzca la velocidad de la nave (km/h): ";
            cin >> Vnave;
            porcentaje = (Vnave / Vorbita) * 100 - 100;
            if (porcentaje > 2) {
                cout << "Su velocidad esta " <<porcentaje << " % por encima de la ideal" << endl;
                cout << "Su velocidad esta lejos de mantener la orbita"<< endl;
                cout << "Aviso: se aborta la exploracion del planeta" << endl;
            } else if (porcentaje < 0.8) {
                cout << "Su velocidad esta " <<porcentaje << " % por debajo de la ideal" << endl;
                cout << "Su velocidad esta lejos de mantener la orbita"<< endl;
                cout << "Aviso: se aborta la exploracion del planeta" << endl;
            }else if (porcentaje >= 1 && porcentaje < 2) {
                    cout << "Su velocidad esta " <<porcentaje << " % por encima de la ideal" << endl;
            } else if (porcentaje < 1 && porcentaje >= 0.8) {
                    cout << "Su velocidad esta " <<porcentaje << " % por debajo de la ideal" << endl;
            }
            cout << "Su velocidad esta en margenes aceptables: 2%... manteniendo orbita" << endl;
            cout << "Evaluando exploracion del planeta..." << endl;
            cout << "Introduzca el peso de la persona (kg): ";
            cin >> mAstronauta;
            if (mAstronauta <= 0) {
                cout << "Aviso: peso no positivo. Descartamos exploracion" << endl;
            } else {
                Gtierra = Guniv * (Mtierra / pow(Rtierra, 2));
                Gplaneta = Guniv * (masaP / pow(radioP, 2));
                pesoRel = Gplaneta / Gtierra;
                pesoP = mAstronauta * pesoRel;
                cout << "Peso relativo en el planeta: " << pesoRel << endl;
                cout << "La persona soportará un peso de " << pesoP << " kg." << endl;
            }
        }
    }
}
