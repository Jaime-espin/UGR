#include "cifras_set.h"

#include <cstdlib>
#include <ctime>
#include <vector>
#include <iostream>
#include <algorithm>
#include <set>
using namespace std;


//Funciones de generar números
multiset<int> generarConjunto(){
    multiset<int> v;
    for(int i=0; i<6; i++){
        int numero = rand() % (13 + 1);
        v.insert(C[numero]);
    }

    return v;
}

//Parte extra, 6 numero aleatorios fuera del conjunto
multiset<int> generar(){
    multiset<int> v;
    for(int i=0; i<6; i++){
        int numero = 1 + rand() % (100 - 1 + 1);
        v.insert(numero);
    }

    return v;
}

bool es_combinacion_magica(const multiset<int>& conjunto_magico) {
    for (int target = 100; target <= 999; ++target) {
        Cifras juego; 
        bool encontrado = juego.resolver_juego(conjunto_magico, target);
        if (!encontrado) {
            return false;
        }
    }
    
    return true; 
}

multiset<int> generarConjuntoMagico(){
    multiset<int> conjunto = generarConjunto();
    while(!es_combinacion_magica(conjunto)){
        conjunto = generarConjunto();
    }
    return conjunto;
}


int generarNumero(){
    int min=100;
    int max=999;
    int numero = min + rand() % (max - min + 1);

    return numero;
}

//TDA de cifras
    Cifras::Cifras() {
        mejor_resultado_encontrado = 0; 
        operaciones.clear();
    };

    void Cifras::imprimirOperaciones(){
        reverse(operaciones.begin(), operaciones.end());

        for (const auto& op : operaciones) {
            cout << op << endl;
        }
    };

    int Cifras::get_mejor_resultado_encontrado(){
        return mejor_resultado_encontrado;
    };

    bool Cifras::resolver_juego(const multiset<int>& numeros_iniciales, int target){
        operaciones.clear(); 
        mejor_resultado_encontrado = 0; 
        objetivo = target;

        return buscar_solucion(numeros_iniciales, target); 
    };

    bool Cifras::buscar_solucion(multiset<int> restantes, int objetivo){
        for(auto it1 = restantes.begin(); it1 != restantes.end(); ++it1){
            for(auto it2 = next(it1); it2 != restantes.end(); ++it2){
                int a = *it1;
                int b = *it2;
                
                // División a/b
                if(b != 0 && a%b==0){
                    int r=a/b;
                    if(mejor_resultado_encontrado == 0 || abs(objetivo-r) < abs(objetivo-mejor_resultado_encontrado)){
                        mejor_resultado_encontrado = r;
                    }
                    if(r==objetivo){
                        operaciones.push_back(to_string(a) + " / " + to_string(b)+"="+to_string(r));
                        return true;
                    }else{
                        multiset<int> nueva_lista = restantes;
                        nueva_lista.erase(nueva_lista.find(a));
                        nueva_lista.erase(nueva_lista.find(b));
                        nueva_lista.insert(r);
                        if (buscar_solucion(nueva_lista, objetivo)) {
                            operaciones.push_back(to_string(a) + " / " + to_string(b)+"="+to_string(r));
                            return true;
                        }
                    }
                }
                
                // Resta a-b
                if(a-b>=0){
                    int r=a-b;
                    if(mejor_resultado_encontrado == 0 || abs(objetivo-r) < abs(objetivo-mejor_resultado_encontrado)){
                        mejor_resultado_encontrado = r;
                    }
                    if(r==objetivo){
                        operaciones.push_back(to_string(a) + " - " + to_string(b)+"="+to_string(r));
                        return true;
                    }else{
                        multiset<int> nueva_lista = restantes;
                        nueva_lista.erase(nueva_lista.find(a));
                        nueva_lista.erase(nueva_lista.find(b));
                        nueva_lista.insert(r);
                        if (buscar_solucion(nueva_lista, objetivo)) {
                            operaciones.push_back(to_string(a) + " - " + to_string(b)+"="+to_string(r));
                            return true;
                        }
                    }
                }
                
                // División b/a
                if(a != 0 && b%a==0){
                    int r=b/a;
                    if(mejor_resultado_encontrado == 0 || abs(objetivo-r) < abs(objetivo-mejor_resultado_encontrado)){
                        mejor_resultado_encontrado = r;
                    }
                    if(r==objetivo){
                        operaciones.push_back(to_string(b) + " / " + to_string(a)+"="+to_string(r));
                        return true;
                    }else{
                        multiset<int> nueva_lista = restantes;
                        nueva_lista.erase(nueva_lista.find(a));
                        nueva_lista.erase(nueva_lista.find(b));
                        nueva_lista.insert(r);
                        if (buscar_solucion(nueva_lista, objetivo)) {
                            operaciones.push_back(to_string(b) + " / " + to_string(a)+"="+to_string(r));
                            return true;
                        }
                    }
                }
                
                // Resta b-a
                if(b-a>=0){
                    int r=b-a;
                    if(mejor_resultado_encontrado == 0 || abs(objetivo-r) < abs(objetivo-mejor_resultado_encontrado)){
                        mejor_resultado_encontrado = r;
                    }
                    if(r==objetivo){
                        operaciones.push_back(to_string(b) + " - " + to_string(a)+"="+to_string(r));
                        return true;
                    }else{
                        multiset<int> nueva_lista = restantes;
                        nueva_lista.erase(nueva_lista.find(a));
                        nueva_lista.erase(nueva_lista.find(b));
                        nueva_lista.insert(r);
                        if (buscar_solucion(nueva_lista, objetivo)) {
                            operaciones.push_back(to_string(b) + " - " + to_string(a)+"="+to_string(r));
                            return true;
                        }
                    }
                }
                
                // Suma a+b
                if(a+b==objetivo){
                    operaciones.push_back(to_string(a) + " + " + to_string(b)+"="+to_string(a+b));
                    return true;
                }else{
                    int r=a+b;
                    if(mejor_resultado_encontrado == 0 || abs(objetivo-r) < abs(objetivo-mejor_resultado_encontrado)){
                        mejor_resultado_encontrado = r;
                    }
                    multiset<int> nueva_lista = restantes;
                    nueva_lista.erase(nueva_lista.find(a));
                    nueva_lista.erase(nueva_lista.find(b));
                    nueva_lista.insert(r);
                    if (buscar_solucion(nueva_lista, objetivo)) {
                        operaciones.push_back(to_string(a) + " + " + to_string(b)+"="+to_string(r));
                        return true;
                    }
                }
                
                // Multiplicación a*b
                if(a*b==objetivo){
                    operaciones.push_back(to_string(a) + " * " + to_string(b)+"="+to_string(a*b));
                    return true;
                }else{
                    int r=a*b;
                    if(mejor_resultado_encontrado == 0 || abs(objetivo-r) < abs(objetivo-mejor_resultado_encontrado)){
                        mejor_resultado_encontrado = r;
                    }
                    multiset<int> nueva_lista = restantes;
                    nueva_lista.erase(nueva_lista.find(a));
                    nueva_lista.erase(nueva_lista.find(b));
                    nueva_lista.insert(r);
                    if (buscar_solucion(nueva_lista, objetivo)) {
                        operaciones.push_back(to_string(a) + " * " + to_string(b)+"="+to_string(r));
                        return true;
                    }
                }
            }
        }
        return false;
    };

//Función extra para permitir jugar al usuario
void operar(int a, int b, char oper, multiset<int> &conjunto){
    if(conjunto.find(a) == conjunto.end() || conjunto.find(b) == conjunto.end()){
        cout<<"El numero no está en el conjunto"<<endl;
        return;
    }
    
    if(a == b){
        int count = conjunto.count(a);
        if(count < 2){
            cout<<"No hay suficientes números "<<a<<" en el conjunto"<<endl;
            return;
        }
    }
    
    int result;
    switch (oper)
    {
    case '+':
        result = a+b;
        break;
    case '-':
        if(a-b<0){
            cout<<"No se pueden obtener numeros negativos"<<endl;
            return;
        }else{
            result=a-b;
        }
        break;
    case '*':
        result=a*b;
        break;
    case '/':
        if(b == 0){
            cout<<"No se puede dividir por cero"<<endl;
            return;
        }
        if(a%b==0){
            result=a/b;
        }else{
            cout<<"La división debe ser exacta"<<endl;
            return;
        }
        break;
    default:
        cout<<"Operador no válido"<<endl;
        return;
    }

    auto it = conjunto.find(a);
    if (it != conjunto.end()){
        conjunto.erase(it);
    } 

    it = conjunto.find(b);
    if (it != conjunto.end()){
        conjunto.erase(it);
    }

    conjunto.insert(result);
    cout<<result<<endl;
}

void imprimirConjunto(multiset<int> conjunto){
    cout << "Números: ";
    for (int n : conjunto) {
        cout << n << " ";
    }
    cout <<endl;
}

int main(){
    srand(time(0));

    int opc;
    cout<<"¿Quieres jugar con:"<<endl;
    cout<<"1) Combinación mágica (siempre hay solución)/muy poco eficiente"<<endl;
    cout<<"2) Números aleatorios (más difícil)"<<endl;
    cin>>opc;
    multiset<int> conjunto;
    if (opc == 1){
        conjunto = generarConjuntoMagico();
    } else{
        conjunto = generarConjunto();
        //conjunto = generar();
    }
    multiset<int> numeros = conjunto;
    int objetivo = generarNumero();

    cout << "Objetivo: " << objetivo <<endl;
    imprimirConjunto(conjunto);

    char respuesta;
    cout<<"Quieres jugar? (y/n)"<<endl;
    cin>>respuesta;
    if(respuesta == 'y'){
        bool victoria=false;
        bool rendirse=false;
        while(!victoria && !rendirse){
            int a, b;
            char oper;
            cin>>a>>oper>>b;
            if(a==-1){
                rendirse=true;
                continue;
            }
            operar(a, b, oper, conjunto);
            imprimirConjunto(conjunto);
            if(conjunto.find(objetivo) != conjunto.end()){
                victoria = true;
                break;
            }
            if(conjunto.size() == 1){
                break;
            }
            cout<<"-1 para rendirte"<<endl;
        }
        
        if(victoria){
            cout<<"¡Felicidades, lo conseguiste!"<<endl;
        }else if(rendirse){
            cout<<"Te rendiste. Aquí está la solución correcta:"<<endl;
        }else{
            cout<<"Te quedaste sin movimientos. Aquí está la solución correcta:"<<endl;
        }
    }
    
    Cifras juego;
    if(juego.resolver_juego(numeros, objetivo)){
        juego.imprimirOperaciones();
    }else{
        cout <<"El mejor resultado encontrado es "<<juego.get_mejor_resultado_encontrado()<<endl;
    }
}