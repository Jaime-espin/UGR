#include <iostream>
#include <cmath>

using namespace std;

int main(){
    const double PI = 3.14159265358979323846;
    double radio, masa, intervalos;
    double volumen, densidad, dens_min, dens_max;
    dens_min=500000;
    dens_max=0;
    const int MAX_PLANETAS = 20;
    double radios[MAX_PLANETAS];
    double masas[MAX_PLANETAS];
    double densidades[MAX_PLANETAS];

    int planetas = 0;
    cout<<"Introduzca planetas: ";
    cin>>radio;
    while (radio >= 0 && planetas<MAX_PLANETAS){
        radios[planetas] = radio;
        cin >> masa;
        if (masa < 0){
            masa = abs(masa);
        }
        masas[planetas] = masa;

        volumen = (4.0 / 3.0) * PI * pow(radio, 3);
        densidad = masa / volumen;
        densidades[planetas] = densidad;
        if(densidad>dens_max){
            dens_max=densidad;
        }
        if(densidad<dens_min){
            dens_min=densidad;
        }

        planetas++;    
        cin >> radio;
    }

    if (planetas<MAX_PLANETAS){
        /*cout<<"Los planetas introducidos son: "<<endl;
        cout<<planetas<<endl;*/
        if(planetas==0){
            cout<<"No se han introducido datos."<<endl;
            cout<<"Fin del programa";
        }else{
            cout << "Las densidades están en el intervalo: [ "<<dens_min<<" , "<<dens_max<<" ]"<<endl;
            if(dens_min == dens_max){
                cout<<"No hay amplitud en el intervalo para estudiar la distribución."<<endl;
                cout<<"Fin del programa";
            }

            cout<<"Introduzca número de intervalos: ";
            cin>> intervalos;
            if(intervalos>2 && intervalos<10){
                cout<<"Distribución de densidades: "<<endl;
                double amplitud = abs((dens_min-dens_max)/intervalos);
                for(int i = 0; i<intervalos; i++){
                    int contador=0;
                    double min, max;
                    if (i==0){
                        min = dens_min;
                    }else{
                        min=dens_min+(amplitud*i);
                    }
                    if (i==intervalos){
                        max = dens_max;
                    }else{
                        max=dens_max-(amplitud*(intervalos-(i+1)));
                    }
                    
                    for(int j=0; j<MAX_PLANETAS; j++){
                        if(densidades[j]<=max && densidades[j]>=min){
                            contador++;
                        }
                    }
                    cout<<"[ "<<min<<" , "<<max<<" ]: "<<contador<<" planetas."<<endl;
                }
                double temp_dens, temp_radio, temp_masa;
                for (int i = 1; i < planetas; i++) {
                    for (int j = 0; j < planetas - i; j++) {
                        if (densidades[j] > densidades[j + 1]) {
                            double temp_densidad = densidades[j];
                            densidades[j] = densidades[j + 1];
                            densidades[j + 1] = temp_densidad;

                            double temp_radio = radios[j];
                            radios[j] = radios[j + 1];
                            radios[j + 1] = temp_radio;

                            double temp_masa = masas[j];
                            masas[j] = masas[j + 1];
                            masas[j + 1] = temp_masa;
                        }
                    }
                }
                cout<<"Los planetas por densidad son:"<<endl;
                for(int i = 0; i<planetas; i++){
                    cout<<radios[i]<<" "<<masas[i]<<": "<<densidades[i]<<endl;
                }
                int duplicados=0;
                for (int i = 0; i < planetas - 1; i++) {
                    if (densidades[i] == densidades[i + 1]) {
                        duplicados++;
                    }
                }
                if(duplicados>0){
                    cout<<"Atención: es posible que haya datos repetidos. Se han detectado "<<duplicados<<" duplicados";
                }
            }else{
                cout<<"Número de intervalos deben ser entre 2 y 10"<<endl;
                cout << "Fin del programa.";
            }
        }
    }else{
        cout << "Error: el programa no puede continuar, capacidad (20) insuficiente."<<endl;
        cout << "Fin del programa.";
    }
}