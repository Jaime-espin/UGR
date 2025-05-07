#include "ConjuntoParticulas.hpp"

using namespace std;

ConjuntoParticulas::ConjuntoParticulas(int n=0){
    capacidad=n;
    num_particulas=n;
    if(n>0){
        conjunto = new Particula[capacidad];
        for(int i=0; i<capacidad; i++){
            conjunto[i]=Particula(0);
        }
    }
}
ConjuntoParticulas::ConjuntoParticulas(const ConjuntoParticulas &cp){
    conjunto = new Particula[cp.capacidad];
    for(int i=0; i<cp.num_particulas; i++){
        conjunto[i]=cp.conjunto[i];
    }
}
ConjuntoParticulas::~ConjuntoParticulas(){
    num_particulas=0;
    capacidad=0;
    delete [] conjunto;
}
int ConjuntoParticulas::size(){
    return num_particulas;
}
void ConjuntoParticulas::agergar(Particula p){
    if(capacidad<num_particulas+1){
        conjunto = new Particula[capacidad+TAM_BLOQUE];
    }
    conjunto[num_particulas+1]=p;
}
void ConjuntoParticulas::borrar(int pos){
    conjunto[pos]=conjunto[num_particulas];
    num_particulas--;
    if(capacidad-num_particulas>TAM_BLOQUE){
        //redimensionar el conjunto para que la capacidad coincida con el numero de part ´ ´ıculas.
    }
}
Particula ConjuntoParticulas::obtener(int pos){
    return conjunto[pos];
}
void ConjuntoParticulas::reemplazar(int pos, Particula p){
    conjunto[pos]=p;
}
void ConjuntoParticulas::mover(int tipo_mov=0){
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
        for(int j=0; j<num_particulas; j++){
            if(conjunto[i].colision(conjunto[j+1])){
                conjunto[i].choque(conjunto[j+1]);
            }
        }
    }
}
std::string ConjuntoParticulas::toString(){
    string s=to_string(capacidad)+","+to_string(num_particulas)+"\n";
    for(int i=0; i<num_particulas; i++){
        s+=conjunto[i].toString()+"\n";
    }

    return s;
}