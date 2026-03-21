#include <iostream>
#include <cassert>
#include <cmath>
#include <string>

using namespace std;


class Planeta{
    string nombre;
    double radio;
    double masa;

    public:
    Planeta(){
        nombre="";
        radio=0;
        masa=0;
    }

    Planeta(string nom, double r, double m){
        nombre=nom;
        /*assert(r<0 && m<0);*/
        radio=r;
        masa=m;
    }

    bool nulo(){
        if(nombre=="" && radio==0 && masa==0){
            return true;
        }else{
            return false;
        }
    }

    double getradio(){
        return radio;
    }

    double getmasa(){
        return masa;
    }

    string getnombre(){
        return nombre;
    }

    double getdensidad(){
        const double PI=3.14159265359;
        double densidad, volumen;
        volumen=(4.0/3.0)*PI*pow(radio,3);
        densidad=masa/volumen;
        return densidad;
    }
};

Planeta Lectura(){
    char c1, c2, c3;
    int cargados=0;
    string nom;
    double r, m;
    Planeta p;
    
    cin >> c1 >> nom >> r >> c2 >> m >> c3;
    if(c1 != '(' || c2 != '/' || c3 != ')' || m<=0 || r<=0){
        Planeta p("",0,0);
        return p;
    }else{
        Planeta p(nom,r,m);
        return p;
    }
    
}

void Escritura(Planeta p){
    if(p.nulo()){
        cout<<"Desconocido"<<endl;
    }else{
        cout<< "("<<p.getnombre()<<" "<<p.getradio()<<" / "<<p.getmasa()<<"): "<<p.getdensidad()<<endl;
    }
}

int main(){
    const int MAX=20;
    Planeta v[MAX];
    int n;

    cout<<"Introduzca número de planetas seguido de planetas:";
    cin>>n;
    if(n>MAX || n<1){
        cout<<"Error: la lista debe tener de 1 a "<< MAX <<" planetas.";
    }else{
        int leidos=0;
        for(int i=0; i<n; i++){
            v[i]=Lectura();
            if(v[i].nulo()){
                cout<<"Error: sólo hemos cargado "<<leidos<<" planetas"<<endl;
                i=n;
            }
            leidos++;
        }
        Planeta aux;
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < n - i; j++) {
                if (v[j].getdensidad() > v[j + 1].getdensidad()) {
                    aux = v[j];
                    v[j] = v[j + 1];
                    v[j + 1] = aux;
                }
            }
        }

        if(leidos==n){
            cout<<"Listado por densidad:"<<endl;
            cout<<n<<endl;
            for(int i=0; i<n; i++){
                Escritura(v[i]);
            }
        }
    }
}