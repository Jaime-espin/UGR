#include <iostream>
#include <cmath>
using namespace std;

int main(){
    const double PI = 3.14159265358979323846;
    double radio, masa, densidad, dens1, dens2, densMin, densMax, volumen;
    double minimo=2e10;
    double maximo=-2e10;
    double planetas=0.0;
    double candidato=0.0;
    char repetir;
    repetir='s';
    

    while (repetir == 's'){
        cout << "Ingrese el intervalo de densidad: ";
        cin >> dens1 >> dens2;

        if (dens1 > dens2) {
            densMax=dens1;
            densMin=dens2;
        }else{
            densMax=dens2;
            densMin=dens1;
        }

        cout << "El intervalo a analizar es: [" << densMin << ", " << densMax << "]" << endl;
        cout << "Intrdoduzca planetas: ";
        cin >> radio;

        while (radio > 0) {
            volumen=0;
            densidad=0;
            volumen=(4.0/3.0)*PI*pow(radio,3);
            cin >> masa;
            densidad=masa/volumen;
            cout<<densidad<<" ";
            if (densidad>densMin && densidad<densMax){
                candidato ++;
            }
            if(densidad<minimo){
                minimo=densidad;
            }else if(densidad>maximo){
                maximo=densidad;
            }
            planetas++;
            
            cin >> radio;
        }
        cout<<endl;

        cout << "El sistema planetario tiene " <<planetas<< " planetas" << endl;
        if (planetas!=0){
            cout << "El numero de candidatos es: " <<candidato<<" planetas ("<<(candidato/planetas)*100<<"%)"<<endl;
            cout << "El sistema planetario tiene densidades en el intervalo: ["<< minimo <<" , "<< maximo <<"]";
        }else{
            cout << "No hay planetas que analizar."<<endl;
        }

        cout<<"Quieres analizar otro sistema (s/n): ";
        cin>>repetir;
        cout << endl;
    }
}