/**
 * @file maxstack.cpp
 * @brief  Archivo de implementación del TDA MaxStack
 * @author  Marvin Augusto Fonseca Zamora
 */

#include "maxstack.h"

ostream& operator<<(ostream &flujo, const element &dato){
    
    flujo << to_string(dato.value) + "," + to_string(dato.maximum);
    
    return flujo;
}

void MaxStack:: push(int dato){
    
    if(q1.empty()){
        q1.push(element{dato,dato});
        
    }else{
        
        element nuevo = {dato,(q1.front().maximum < dato) ? dato : q1.front().maximum};
        
        q2.push(nuevo);
        
        while(!q1.empty()){
            
            q2.push(q1.front());
            q1.pop();
        }
        
        swap(q1, q2);
    }
}

void MaxStack::pop(){
    
    if(!q1.empty())
        q1.pop();
}

bool MaxStack:: empty() const{
    
    return q1.empty();
}

element MaxStack::top() const{
    
    element dato;
    
    if(!q1.empty())
        dato = q1.front();
    
    return dato;
}


void MaxStack::copiar(MaxStack p){
    // Reemplaza las colas actuales por las de p (p está pasado por valor)
    q1 = p.q1;
    q2 = p.q2;
}


bool MaxStack::HaySubsecuencia(MaxStack p1, MaxStack p2){
    if (p2.empty())
        return true;

    MaxStack c1 = p1;
    MaxStack c2 = p2;
    size_t s1 = 0, s2 = 0;
    while (!c1.empty()) { c1.pop(); ++s1; }
    while (!c2.empty()) { c2.pop(); ++s2; }
    if (s2 > s1)
        return false;

    while (!p1.empty()){
        if (p1.top().value == p2.top().value){
            MaxStack t1 = p1;
            MaxStack t2 = p2;
            while (!t2.empty() && !t1.empty() && t1.top().value == t2.top().value){
                t1.pop();
                t2.pop();
            }
            if (t2.empty())
                return true;
        }
        p1.pop();
    }

    return false;
}
