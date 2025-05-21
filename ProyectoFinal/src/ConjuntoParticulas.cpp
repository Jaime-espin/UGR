#include <iostream>
#include "ConjuntoParticulas.hpp"


ConjuntoParticulas::ConjuntoParticulas(int n){ //Constructor con parámetro por defecto
    capacidad=n;
    num_particulas=n;
    if(n>0){
        conjunto = new Particula[capacidad];
        for(int i=0; i<capacidad; i++){
            conjunto[i]=Particula(0);
        }
    }
    else {
        conjunto = nullptr; // Initialize to nullptr when n <= 0
    }
}
ConjuntoParticulas::ConjuntoParticulas(const ConjuntoParticulas &cp){ //Constructor de copia
    capacidad = cp.capacidad;
    num_particulas = cp.num_particulas;
    conjunto = new Particula[cp.capacidad];
    for(int i=0; i<cp.num_particulas; i++){
        conjunto[i]=cp.conjunto[i];
    }
}
ConjuntoParticulas::~ConjuntoParticulas(){ //Destructor
    num_particulas=0;
    capacidad=0;
    delete [] conjunto;
}
int ConjuntoParticulas::size(){
    return num_particulas;
}
void ConjuntoParticulas::agregar(Particula p){
    if(capacidad<num_particulas+1){
        // Create larger array
        int nueva_capacidad = capacidad + TAM_BLOQUE;
        Particula* nuevo_conjunto = new Particula[nueva_capacidad];
        
        // Copy existing elements
        for(int i=0; i<num_particulas; i++){
            nuevo_conjunto[i] = conjunto[i];
        }
        
        // Free old array and update pointers
        delete[] conjunto;
        conjunto = nuevo_conjunto;
        capacidad = nueva_capacidad;
    }
    
    // Add new particle and increment count
    conjunto[num_particulas] = p;
    num_particulas++;
}
void ConjuntoParticulas::borrar(int pos) {
    if (pos >= 0 && pos < num_particulas) {
        conjunto[pos] = conjunto[num_particulas-1];
        num_particulas--;
        
        if (capacidad - num_particulas > TAM_BLOQUE && num_particulas > 0) {
            int nueva_capacidad = num_particulas;

            Particula* nuevo_conjunto = new Particula[nueva_capacidad];
            
            for (int i = 0; i < num_particulas; i++) {
                nuevo_conjunto[i] = conjunto[i];
            }
            
            delete[] conjunto;
            conjunto = nuevo_conjunto;
            capacidad = nueva_capacidad;
        }
    }
}
Particula ConjuntoParticulas::obtener(int pos){
    return conjunto[pos];
}

void ConjuntoParticulas::reemplazar(int pos, Particula p){
    conjunto[pos]=p;
}
void ConjuntoParticulas::mover(int tipo_mov){
    if(tipo_mov==0){
        for(int i=0; i<num_particulas; i++){
            conjunto[i].mover();
        }
    }else if(tipo_mov==1){
        for(int i=0; i<num_particulas; i++){
            conjunto[i].mover();
            conjunto[i].rebotar();
        }
    }else if(tipo_mov==2){
        for(int i=0; i<num_particulas; i++){
            conjunto[i].mover();
            conjunto[i].wrap();
        }
    }
}
void ConjuntoParticulas::gestionarColisiones(){
    for(int i=0; i<num_particulas; i++){
        for(int j=i+1; j<num_particulas; j++){
            if(conjunto[i].colision(conjunto[j])){
                conjunto[i].choque(conjunto[j]);
            }
        }
    }
}
string ConjuntoParticulas::toString(){
    string s=to_string(capacidad)+","+to_string(num_particulas)+"\n";
    for(int i=0; i<num_particulas; i++){
        s+=conjunto[i].toString()+"\n";
    }

    return s;
}

//Parte2

Particula ConjuntoParticulas::operator[](const int indice){
    return obtener(indice);
}
ConjuntoParticulas & ConjuntoParticulas::operator=(const ConjuntoParticulas & c){
    if (this != &c) {
        delete[] conjunto;
        
        capacidad = c.capacidad;
        num_particulas = c.num_particulas;
        
        conjunto = new Particula[capacidad];
        for (int i = 0; i < num_particulas; i++) {
            conjunto[i] = c.conjunto[i];
        }
    }
    
    return *this;
}
ConjuntoParticulas & ConjuntoParticulas::operator+(ConjuntoParticulas & c){
    ConjuntoParticulas nuevo(c);
    
    for(int i=0; i<size(); i++) {
        Particula p = conjunto[i];
        if (!nuevo.pertenece(p)) {
            nuevo.agregar(p);
        }
    }
    *this=nuevo;
    return *this;
}
ConjuntoParticulas & ConjuntoParticulas::operator+=(Particula & p){
    if(!pertenece(p)){
        agregar(p);
    }
    return *this;
}
ConjuntoParticulas & ConjuntoParticulas::operator-=(const int & indice){
    borrar(indice);
    return *this;
}

ostream& operator<<(ostream &flujo, ConjuntoParticulas &c){
    flujo<<c.toString();
    return flujo;
}

std::istream& operator>>(std::istream &flujo, ConjuntoParticulas &c){
    std::string cabecera;
    int n;
    
    flujo >> cabecera;
    flujo >> n;
    
    c = ConjuntoParticulas(0);
    
    for(int i = 0; i < n; i++) {
        std::string etiqueta;
        double pos_x, pos_y, vel_x, vel_y, ace_x, ace_y, radio;
        int tipo;
        
        flujo >> etiqueta;
        flujo >> pos_x >> pos_y >> vel_x >> vel_y >> ace_x >> ace_y >> radio >> tipo;  // Uncomment this line
        
        Particula p(Vector2D(pos_x, pos_y), Vector2D(vel_x, vel_y), Vector2D(ace_x, ace_y), radio, tipo);
        c.agregar(p);
    }
    
    return flujo;
}

//Funciones auxiliares

bool ConjuntoParticulas::pertenece(Particula & p){
    int tam=size();
    bool encontrado=false;
    for(int i=0; i<tam; i++){
        if(conjunto[i]==p){
            encontrado=true;
        }
    }
    return encontrado;
}

int ConjuntoParticulas::getNumeroParticulas(){
    return num_particulas;
}