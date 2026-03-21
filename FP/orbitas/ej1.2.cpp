/* Modifique el ejercicio 1.1 añadiendo algunos datos relativos a las velocidades relacionadas:
• Velocidad máxima de una persona en la superficie (use la ecuación 1.2).
• Velocidad de escape en la superficie (use la ecuación 1.3).

Confirme que la solución que obtiene es aproximadamente:

Consola
    Longitud del ecuador: 4.00742e+07 metros
    Volumen del planeta: 1.08678e+21 m3
    La densidad media del planeta es: 5495.31 kg/m3
    La gravedad en la superficie es: 9.79876 m/s2
    La velocidad máxima en la superficie es: 463.821 m/s
    La velocidad de escape en la superficie es: 11180 m/s
*/
#include <iostream>
#include <cmath>
using namespace std;

int main() {
    const double pi = 3.14159265358979323846;
    const double G = 6.6743 * pow(10, -11);
    const double Mtierra = 5.9722 * pow(10, 24);
    const double Rtierra = 6378;
    double LongEc, Vtierra, Dtierra, Gtierra;
    LongEc = (2 * pi * Rtierra)*pow(10, 3);
    Vtierra = (4.0/3.0) * pi * pow(Rtierra * pow(10, 3), 3);
    Dtierra = Mtierra / Vtierra;
    Gtierra = G * Mtierra / pow(Rtierra * pow(10,3), 2);
    cout << "Longitud del ecuador: " << LongEc << " metros" << endl;
    cout << "Volumen del planeta: " << Vtierra << " m3" << endl;
    cout << "La densidad media del planeta es: " << Dtierra << " kg/m3" << endl;
    cout << "La gravedad en la superficie es: " << Gtierra << " m/s2" << endl;

    double Vmax, Vesc;
    Vmax = LongEc/(24*3600);
    Vesc = sqrt((2 * G * Mtierra)/(Rtierra*pow(10,3)));
    cout << "La velocidad máxima en la superficie es: " << Vmax << " m/s" << endl;
    cout << "La velocidad de escape en la superficie es: " << Vesc << " m/s" << endl;

    return 0;
}