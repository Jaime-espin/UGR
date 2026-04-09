#include "practica2.h"
#include "myTime.h"
#include <random>
#include <iostream>
#include <cassert>

using namespace std; 


int Practica2::algoritmoObvio(const vector<int>& vec, const int k) const {
    //La solución más tonta que se me ocurre es: Sabiendo que siempre empieza en 0, hacemos un bucle de 0 a k, y con el índice
    // del bucle (i) si no es igual al número por el que vamos abortamos
    bool parar = false;
    int result=-1; //Si está perfectamente ordenado sacamos -1.

    for(int i = 0; i <= k && !parar; i++){
        if(i != vec[i]){ parar = true; result = i; }

    }

    return result; 

}

//Vale ahora necesito crear algún tipo de generador aleatorio de tests, para aumentar el tamaño del vector y poder hacer mediciones.
// Mi idea es, le pasamos el vector (vacio), k elementos que queremos (random) y qué numero queremos eliminar (pivote).
void Practica2::rellenarvector(vector<int>& vec, const int k, const int pivote){
    vec.clear();
    vec.reserve(k);
    for(int i = 0; i <= k; i++){
        if(i != pivote) { vec.push_back(i); }
    }

}

void Practica2::crearTestAleatorioAlgoritmoBasico(const int min, const int max){
    MyTime timer; 

    const int k = aleatorio(min, max);
    uniform_int_distribution<> dis(min, k);
    const int pivote = aleatorio(min, k);
    rellenarvector(v, k, pivote);

    timer.start();
    const int r = algoritmoObvio(v, k);
    timer.end();

    assert(r == pivote);
    cout << "Test Pasado correctamente (k, pivote) " << k << " " << pivote << " en " << *timer << endl; 

}

//Pongo aquí según google la mejor forma de hacer un número aleatorio: 
int Practica2::aleatorio(const int min, const int max) const{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(min, max);

    return dis(gen);

}

//Son solo los test del profe que pone en el enunciado
void Practica2::testProfe(){
    const vector<int> v1 = {0, 1, 2, 6, 9, 11, 15};
    const int k1 = 15;
    assert(algoritmoObvio(v1, k1) == 3);
    cout << "Test1 Pasado correctamente\n";

    const vector<int> v2 = {1, 2, 3, 4, 6, 9, 11, 15};
    const int k2 = 15;
    assert(algoritmoObvio(v2, k2) == 0);
    cout << "Test2 Pasado correctamente\n";

    const vector<int> v3 = {0, 1, 2, 3, 4, 5, 6};
    const int k3 = 7;
    assert(algoritmoObvio(v3, k3) == 7);
    cout << "Test3 Pasado correctamente\n";

    const vector<int> v4 = {0, 1, 2, 3, 4, 5, 6};
    const int k4 = 6;
    assert(algoritmoObvio(v4, k4) == -1);
    cout << "Test4 Pasado correctamente\n";

}