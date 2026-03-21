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

bool haySubsecuencia(MaxStack p1, MaxStack p2){
    
}
