#include "bolsa_letras.h"
#include <algorithm>
#include <random>

BolsaLetras::BolsaLetras(const LettersSet &conjunto){
    
    auto it = conjunto.cbegin();
    while(it != conjunto.cend()){
        Letra l = *it;
        for(unsigned short j = 0; j < l.num_repeticiones; ++j)
            bolsa.push_back(l.letra);
        ++it;
    }
    mezclar();
}

BolsaLetras& BolsaLetras::operator=(const BolsaLetras &bl){
    
    if(this != &bl)
        this->bolsa = bl.bolsa;
    
    return *this;
}

vector<char> BolsaLetras::get_letras_aleatorias(int num_letras){
    
    vector<char> subconjunto;
    
    if(!bolsa.empty()){
        //ya que estamos usando la libreria algorithm...
        //le hacemos un casting a bolsa.size porque regresa un unsigned long
        int N = min((int)bolsa.size(), num_letras);
        
        for(int i = 0; i < N; ++i){
            subconjunto.push_back(bolsa.back());
            bolsa.pop_back();
        }
        
    }
    return subconjunto;
}


void BolsaLetras::mezclar(){
    random_device rd;
    mt19937 semilla(rd());
    shuffle(bolsa.begin(), bolsa.end(), semilla);
}
