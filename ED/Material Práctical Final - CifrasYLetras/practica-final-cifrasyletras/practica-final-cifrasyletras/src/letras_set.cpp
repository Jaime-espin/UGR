#include "letras_set.h"
#include "bolsa_letras.h"
#include <iostream>
#include <cassert>
#include <fstream>
#include <map>
#include "diccionario.h"
#include <cctype>
#include <limits>

LettersSet& LettersSet::operator=(const LettersSet& cl){
    
    if(this != &cl)
        this->letras = cl.letras;
    
    return *this;
}


void LettersSet::insert(const Letra &letra){
    
    if(!exists(letra))
        letras.insert(letra);
    else{
        Letra nueva = letra;
        nueva.num_repeticiones++;
        replace(letra,nueva);
    }
}

int LettersSet::getPuntuacion(const Letra &letra) const{
    
    int puntuacion;
    auto it = letras.find(letra);
    
    if(it != letras.end()){
        puntuacion = it->puntuacion;
    }else
        puntuacion = 0;
        
    return puntuacion;
}

unsigned long LettersSet::getRepeticiones(const Letra &letra) const{
    
    
    unsigned long repeticiones;
    auto it = letras.find(letra);
    
    if(it != letras.end()){
        repeticiones = it->num_repeticiones;
    }else
        repeticiones = 0;
        
    return repeticiones;
}

bool LettersSet::setPuntuacion(const Letra &letra, const int p){
    
    bool modificada;

    if(exists(letra)){
        
        Letra nueva = letra;
        nueva.puntuacion = p;
        
        replace(letra, nueva);
        
        modificada = true;
    }else
        modificada = false;
    
    return modificada;
}

bool LettersSet::setRepeticiones(const Letra &letra, const int r){
    
    bool modificada;
    
    if(exists(letra)){
        
        Letra nueva = letra;
        nueva.num_repeticiones = r;
        
        replace(letra, nueva);
        
        modificada = true;
        
    }else
        modificada = false;
    
    return modificada;
}

LettersSet::iterator& LettersSet::iterator::operator=(const iterator &i){
    
    it = i.it;
    return *this;
}

LettersSet::iterator& LettersSet::iterator::operator=(const set<Letra>::iterator &cl){
    
    it = cl;
    return *this;
}

LettersSet::iterator& LettersSet::iterator::operator++(){
    ++it;
    return *this;
}

LettersSet::iterator& LettersSet::iterator::operator--(){
    --it;
    return *this;
}

LettersSet::const_iterator& LettersSet::const_iterator::operator=(const const_iterator &i){
    
    const_it = i.const_it;
    return *this;
}

LettersSet::const_iterator& LettersSet::const_iterator::operator=(const set<Letra>::const_iterator &cl){
    
    const_it = cl;
    return *this;
}

LettersSet::const_iterator& LettersSet::const_iterator::operator++(){
    
    ++const_it;
    return *this;
}

LettersSet::const_iterator& LettersSet::const_iterator::operator--(){
    
    --const_it;
    return *this;
}

istream& operator>>(istream &is, LettersSet &cl){
    
    string aux;
    getline(is, aux); //saltamos la cabecera
    char letra;
    unsigned long cantidad;
    int puntos;
    
    while(is >> letra >> cantidad >> puntos){
        char minuscula = tolower((unsigned char)(letra));
        cl.insert(Letra(minuscula,cantidad,puntos));
    }
    
    return is;
}

ostream& operator<<(ostream &os, const LettersSet &cl){
    
    os << "LETRA" << setw(ESPACIO) << "CANTIDAD" << setw(ESPACIO) << "PUNTOS" << endl;
    
    auto it = cl.cbegin();
    
    while(it != cl.cend()){
        
        os << (*it).letra << setw(ESPACIO) << (*it).num_repeticiones << setw(ESPACIO) << (*it).puntuacion << endl;
        ++it;
    }
    return os;
}

void LettersSet::replace(const Letra &antigua, const Letra &nueva){
    
    letras.erase(antigua);
    letras.insert(nueva);
}

#include <iostream>
#include <cassert>
#include <fstream>
#include <map>
#include "letras_set.h"
#include "diccionario.h"
#include "bolsa_letras.h"

using namespace std;

int CalcularPuntuacion(const string &palabra, const LettersSet &conjunto){
    
    int puntuacion = 0;
    for(char c: palabra){
        char minuscula = tolower((unsigned char)c);
        Letra aux(minuscula);
        puntuacion += conjunto.getPuntuacion(aux);
    }
    return puntuacion;
}

vector<string> EncontrarMejoresPalabras(const Diccionario &D, const vector<char> &disponibles, const LettersSet &conjunto, char modo){
    
    assert(modo == 'L' || modo == 'P');
    
    vector<string> mejores_palabras;
    int puntos_mejor = -1;
    
    for (auto it = D.cbegin(); it != D.cend(); ++it) {
        const string& palabra = *it;

        if(PuedeFormar(palabra, disponibles)){
            int puntos_actuales;
            if(modo == 'L')
                puntos_actuales = (int)(palabra).size();
            else
                puntos_actuales = CalcularPuntuacion(palabra, conjunto);
            
            if(puntos_actuales > puntos_mejor){
            
                mejores_palabras.clear();
                mejores_palabras.push_back(palabra);
                puntos_mejor = puntos_actuales;
            
            }else if(puntos_actuales == puntos_mejor)
                mejores_palabras.push_back(palabra);
        }
    }
    return mejores_palabras;
}

bool PuedeFormar(const string &palabra, const vector<char> &disponibles){
    
    map<char,int> contador_disponibles;
    for(char c: disponibles)
        contador_disponibles[c]++;
    
    int posibilidad = true;
    
    map<char,int> contador_palabra;
    for(char c: palabra){
        contador_palabra[c]++;
        if(contador_palabra[c] > contador_disponibles[c]){
            posibilidad = false;
            break;
        }
    }
    return posibilidad;
}

void Imprimir(const vector<char>& letras){
    
    cout << "Las letras son: ";
    for(unsigned long i = 0; i < letras.size(); ++i){
        cout << (char)toupper(letras[i]) << ' ';
    }
    cout << endl;
}

void JugarRonda(const Diccionario& D, const LettersSet& L, BolsaLetras& B, int num_letras, char modo) {
    
    vector<char> disponibles = B.get_letras_aleatorias(num_letras);
    
    if (disponibles.size() < num_letras){ //si la bolsa se vacio
        cerr << "No se pudieron generar en la bola las letras pedidas. Se generaron solo " << disponibles.size() << " letras." << endl;
    }
    Imprimir(disponibles);
    
    string solucion_usuario;
    cout << "Decime tu solucion: ";
    cin >> solucion_usuario;
    
    for (char &c: solucion_usuario)
        c = tolower((unsigned char)c);//convertimos a a mayusculas
    
    bool esValida = D.Esta(solucion_usuario); //comprobamos que la letra esta en el diccionario
    
    if (esValida && PuedeFormar(solucion_usuario, disponibles)){
        if(modo == 'P'){
            int puntuacion = CalcularPuntuacion(solucion_usuario, L);
            cout << solucion_usuario << " Puntuacion: " << puntuacion << endl;
        }else
            cout << solucion_usuario << " Longitud: " << solucion_usuario.size() << endl;
        
    } else if (!esValida) {
        cout << "La palabra \"" << solucion_usuario << "\" no se encuentra en el diccionario." << endl;
    } else { // es_valida = true, pero PuedeFormar = false
        cout << "La palabra \"" << solucion_usuario << "\" no se puede formar con las letras disponibles." << endl;
    }
    
    // encontrar y mostrar las soluciones del programa
    cout << endl << "Mis soluciones son:" << endl;
    vector<string> solucion_programa = EncontrarMejoresPalabras(D, disponibles, L, modo);
    
    for (const string& palabra : solucion_programa){
        if(modo == 'P'){
            int puntuacion = CalcularPuntuacion(palabra, L);
            cout << palabra << " Puntuacion: " << puntuacion << endl;
        }else
            cout << palabra << " Longitud: " << palabra.size() << endl;
    }
    
    if (!solucion_programa.empty()){
        bool usuario_valido = D.Esta(solucion_usuario) && PuedeFormar(solucion_usuario, disponibles);
        string mejor;
        
        if(usuario_valido){
            bool mejorEsPrograma;
            if(modo == 'P'){
                int puntuacion_usuario = CalcularPuntuacion(solucion_usuario, L);
                int puntuacion_programa = CalcularPuntuacion(solucion_programa[0], L);
                // Si el programa tiene puntuación mayor, es mejor
                mejorEsPrograma = (puntuacion_usuario < puntuacion_programa);
            }else{
                // Modo longitud: comparar longitud de las palabras
                mejorEsPrograma = (solucion_usuario.size() < solucion_programa[0].size());
            }
            
            mejor = mejorEsPrograma ? solucion_programa[0] : solucion_usuario;
        }else{
            // Si el usuario no tiene palabra válida, la mejor es la del programa
            mejor = solucion_programa[0];
        }
        
        // si hay varias mejores soluciones solo mostramos la primera
        cout << "Mejor Solucion: " << mejor << endl;
    }else
        cout << "No se encontro ninguna palabra valida con las letras disponibles." << endl;
    
}


int main(int argc, char * argv[]){
    
    if (argc != 5){
        cerr << "Uso: " << argv[0] << " <fichero_diccionario> <fichero_letras> <num_letras> <modo (L/P)>" << endl;
        return 1;
    }

    string nombre_diccionario = argv[1];
    string nombre_letras = argv[2];
    int num_letras = stoi(argv[3]);;
    
    char modo = toupper(*argv[4]); //por si lo pone en minusculas

    if (modo != 'L' && modo != 'P') {
        cerr << "ERROR: El modo de juego debe ser 'L' o 'P'." << endl;
        return 1;
    }

    //LEEMOS FICHEROS
    
    //leemos Diccionario
    Diccionario D;
    ifstream fich_diccionario(nombre_diccionario);
    if (!fich_diccionario) {
        cerr << "ERROR: No se pudo abrir el fichero diccionario " << nombre_diccionario << endl;
        return 1;
    }
    fich_diccionario >> D; //lo cargamos en D
    fich_diccionario.close(); //cerramos fichero diccionario

    //leemos LettersSet
    LettersSet L;
    ifstream fich_letras(nombre_letras);
    if (!fich_letras) {
        cerr << "ERROR: No se pudo abrir el fichero letras: " << nombre_letras << endl;
        return 1;
    }
    fich_letras >> L; //lo cargamos en L
    fich_letras.close(); //cerramos fichero letras

    //inicializamos bolsa de letras
    BolsaLetras B(L);

    //JUEGO
    char simon = 'S';
    while (toupper(simon) == 'S') {
        
        cout << endl << "NUEVO ROUND(" << modo << ")" << endl;
        
        if (B.empty()) { //si se vacia la bolsa volvemos a llenarla
            BolsaLetras B_nueva(L);
            B = B_nueva;
        }
        
        JugarRonda(D, L, B, num_letras, modo);
        
        cout << endl << "¿Queres seguir jugando [S/N]?";
        cin >> simon;
        
    }

    return 0;
}