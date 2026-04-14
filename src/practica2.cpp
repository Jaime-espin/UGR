#include "practica2.h"
#include "myTime.h"
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

double Practica2::crearTestAlgoritmoBasico(const int k){
    MyTime timer; //Clase auxiliar para el tiempo
    const int repeticiones = 35; //35 repeticiones para el lineal está bien
    double sumador = 0.0; //Para calcular el tiempo promedio

    const int pivote = k; // Siempre el último elemento
    rellenarvector(v, k, pivote); //Rellenamos sin el elemento pivote

    int r; //Para almacenar el resultado
    for(int i = 0; i < repeticiones; i++){
        timer.start(); 
        r = algoritmoObvio(v); 
        timer.end();
        sumador += *timer;

    }

    assert(r == pivote); //Asegurarnos que ha ido bien
    const double time = sumador/double(repeticiones);
    cout << "Test Pasado correctamente (k, pivote) " << k << " " << pivote << " en " << time<< endl;
    return time; //Devolvemos el tiempo a main para guardar los datos

}


//Son solo los test del profe que pone en el enunciado
void Practica2::testProfe(){
    const vector<int> v1 = {0, 1, 2, 6, 9, 11, 15};
    assert(algoritmoObvio(v1) == 3);
    assert(DivideyVenceras(v1, 0, v1.size()) == 3);
    cout << "Test1 Pasado correctamente\n";

    const vector<int> v2 = {1, 2, 3, 4, 6, 9, 11, 15};
    assert(algoritmoObvio(v2) == 0);
    assert(DivideyVenceras(v2, 0, v2.size()) == 0);
    cout << "Test2 Pasado correctamente\n";

    const vector<int> v3 = {0, 1, 2, 3, 4, 5, 6};
    assert(algoritmoObvio(v3) == 7);
    assert(DivideyVenceras(v3, 0, v3.size()) == 7);
    cout << "Test3 Pasado correctamente\n";
}


int Practica2::DivideyVenceras(const std::vector<int>& vec, int izq, int drch){
    
    int mitad = (izq + drch) / 2; //Justo el punto medio

    if (izq == drch) { //Caso Base
      //Este índice es la primera posición donde el valor no coincide con el índice.
        return izq;
    }else if(vec[mitad]>mitad){ //en este caso el número que falta está a la izquierda
        return DivideyVenceras(vec, izq, mitad);
    }else{  //en este aso el nº que falta está a la derecha
        return DivideyVenceras(vec, mitad+1, drch);
    }
}

double Practica2::crearTestAleatorioAlgoritmoDivideVenceras(const int k){
    MyTime timer;
    int repeticiones; 
    if(k < 100000) repeticiones = 5000000; // pequeño
    else if(k >= 100000 && k < 10000000) repeticiones = 2000000; // Medianos
    else repeticiones = 500000; //grande

    const int pivote = k; 
    rellenarvector(v, k, pivote);

    int r;
    timer.start();
    for(int i = 0; i < repeticiones; i++){
        r = DivideyVenceras(v, 0, v.size());
    }
    timer.end();

    assert(r == pivote);
    const double time = (*timer)/double(repeticiones);
    cout << "Test Pasado correctamente (k, pivote) " << k << " " << pivote << " en " << time << endl; 
    return time; 

}