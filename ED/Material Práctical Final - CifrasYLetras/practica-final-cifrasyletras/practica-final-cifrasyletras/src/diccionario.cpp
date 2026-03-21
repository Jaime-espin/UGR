#include "diccionario.h"
#include <algorithm>

vector<string> Diccionario:: PalabrasLongitud(int longitud){
    
    vector<string> palabrasSelecionadas;
    
    for(const auto &it: datos)
        if(it.size() == longitud)
            palabrasSelecionadas.push_back(it);
    
    return palabrasSelecionadas;
}

bool Diccionario:: Esta(string palabra) const{
    
    return datos.find(palabra) != datos.end();
}

/**
 @brief Lee de un flujo de entrada un diccionario
 @param is : flujo de entrada
 @param D : el objeto donde se realiza la lectura.
 @return el flujo de entrada
 **/
istream & operator>>(istream & is,Diccionario &D){
    
    string palabra;
    while(is >> palabra)
        D.datos.insert(palabra);
    
    return is;
}


/**
 @brief Escribe en un flujo de salida un diccionario
 @param os : flujo de salida
 @param D : el objeto diccionario que se escribe
 @return el flujo de salida
 **/
ostream & operator<<(ostream & os, const Diccionario &D){

    for(const auto &it: D.datos)
        os << it << endl;
    
    return os;
}

string Diccionario::iterator::operator *() const{
    
    return *it;
}

Diccionario::iterator &Diccionario::iterator::operator ++(){
    
    ++it;
    return *this;
}

bool Diccionario::iterator::operator ==(const iterator &i) const{
    
    return i.it == it;
}

bool Diccionario::iterator::operator !=(const iterator &i) const{
    
    return i.it != it;
}

Diccionario::iterator Diccionario::begin() {
    iterator it;
    it.it = datos.begin();
    return it;
}

Diccionario::iterator Diccionario:: end(){
    iterator it;
    it.it = datos.end();
    return it;
}
Diccionario::const_iterator Diccionario::cbegin() const{
    const_iterator it;
    it.const_it = datos.cbegin();
    return it;
}

Diccionario::const_iterator Diccionario::cend() const{
    const_iterator it;
    it.const_it = datos.cend();
    return it;
}
