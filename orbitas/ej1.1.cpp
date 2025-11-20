/*Considere los valores que se han incluido más arriba para calcular algunos datos relativos a la tierra. Escriba
un programa que presente:
• La longitud del ecuador de la tierra en metros.
• El volumen del planeta tierra en metros cúbicos.
• La densidad media de la tierra.
• La gravedad en la superficie.

Para ello tenga en cuenta que el volumen de una esfera de radio r es:
Vesfera = (4/3) * πr^3

y que la densidad media ρ de un cuerpo de masa m y volumen V se puede obtener a partir de:
ρ = m/V

Confirme que la solución que obtiene es aproximadamente:
Consola
    Longitud del ecuador: 4.00742e+07 metros
    Volumen del planeta: 1.08678e+21 m3
    La densidad media del planeta es: 5495.31 kg/m3
    La gravedad en la superficie es: 9.79876 m/s2

Para obtener la gravedad en la superficie, use la ley de gravitación universal (ecuación 1.1). Es decir, la gravedad a una
distancia d del centro de la tierra es:
gd = (Guniv · Mtierra) /d^2

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
    return 0;
}

