#include "practica2.h"
#include "myTime.h"
#include <random>
#include <iostream>
#include <cassert>

using namespace std; 


int Practica2::algoritmoObvio(const vector<int>& vec) const {
    //La solución más tonta que se me ocurre es: Sabiendo que siempre empieza en 0, hacemos un bucle de 0 a size, y con el índice
    // del bucle (i) si no es igual al número por el que vamos abortamos
    const int size = vec.size();

    for(int i = 0; i < size; i++){
        if(i != vec[i]) return i; //Abortamos
    }

    //Si llegamos aquí hay dos posibilidades: 1. Está sin huecos; 2. El hueco es el último.
    //Del enunciado asumimos que sí o sí tiene huecos, por lo que es el último:
    return vec.size(); 

}

//Vale ahora necesito crear algún tipo de generador aleatorio de tests, para aumentar el tamaño del vector y poder hacer mediciones.
// Mi idea es, le pasamos el vector (vacio), k elementos que queremos (random).
void Practica2::rellenarvector(vector<int>& vec, const int k, const int pivote){
    vec.clear();
    vec.reserve(k);
    for(int i = 0; i < k; i++) { 
        if(i != pivote) vec.push_back(i); 
    }

}

void Practica2::crearTestAleatorioAlgoritmoBasico(const int min, const int k){
    MyTime timer;
    const int repeticiones = 50; 
    double sumador = 0.0;

    uniform_int_distribution<> dis(min, k);
    const int pivote = k; //Esto hay que mirarlo bien como elegir el pivote
    rellenarvector(v, k, pivote);

    int r;
    for(int i = 0; i < repeticiones; i++){
        timer.start();
        r = algoritmoObvio(v);
        timer.end();
        sumador += *timer;

    }

    assert(r == pivote);
    cout << "Test Pasado correctamente (k, pivote) " << k << " " << pivote << " en " << sumador/double(repeticiones) << endl; 

}

//Pongo aquí según google la mejor forma de hacer un número aleatorio: 
// Esto lo podemos quitar si seguimos usando lo de quitar siempre el último elemento.
// Antes lo tenía porque el pivote era aleatorio
int Practica2::aleatorio(const int min, const int max) const{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(min, max);

    return dis(gen);

}

//Son solo los test del profe que pone en el enunciado
void Practica2::testProfe(){
    const vector<int> v1 = {0, 1, 2, 6, 9, 11, 15};
    assert(algoritmoObvio(v1) == 3);
    cout << "Test1 Pasado correctamente\n";

    const vector<int> v2 = {1, 2, 3, 4, 6, 9, 11, 15};
    assert(algoritmoObvio(v2) == 0);
    cout << "Test2 Pasado correctamente\n";

    const vector<int> v3 = {0, 1, 2, 3, 4, 5, 6};
    assert(algoritmoObvio(v3) == 7);
    cout << "Test3 Pasado correctamente\n";

}

//Teniendo en cuenta que el vector está ordenado el indice de la 
//posicón del vector debería corresponder con el número que se 
//encuentra en ella. En la posición 0 debe haber un cero o en la
//posición 3 debe haber un 3.
//Teniendo eso en cuenta si el valor de una posición del vector es
//mayor que el indice significa que falta un valor en una posición
//anterior.
int Practica2::DivideyVenceras(const std::vector<int>& vec) const{
    //Primero dividimos
    const int size = vec.size();
    int mitad = size/2;

    return recursiva(vec, 0, size);
}

int recursiva(const std::vector<int>& vec, int izq, int drch){
    int tam = drch - izq;
    int mitad = (izq + drch) / 2;

    if (izq == drch) { //El rango se ha cerrado en una sola posición. Los límites coinciden.
    // Este índice es la primera posición donde el valor no coincide con el índice.
        return izq;
    }else if(vec[mitad]>mitad){ //en este caso el número que falta está a la izquierda
        return recursiva(vec, izq, mitad);
    }else{  //en este aso el nº que falta está a la derecha
        return recursiva(vec, mitad+1, drch);
    }
}