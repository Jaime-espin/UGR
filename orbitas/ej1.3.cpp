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

    double h, Galtura, Vescaltura, Vorbital;
    cout << "Introduzca altura del objeto respecto a la superficie(km): ";
    cin >> h;

    Galtura = G * Mtierra / pow(Rtierra*pow(10,3)+ h, 2);
    Vescaltura = sqrt(2 * Galtura * (Rtierra*pow(10,3) + h));
    Vorbital = sqrt(G * Mtierra / (Rtierra*pow(10,3) + h));

    cout << "La gravedad a altura " << h << " es: " << Galtura << " m/s2" << endl;
    cout << "La velocidad de escape a altura " << h << " es " << Vescaltura << " m/s" << endl;
    cout << "La velocidad orbital a altura " << h << " es " << Vorbital << " m/s" << endl;
}
