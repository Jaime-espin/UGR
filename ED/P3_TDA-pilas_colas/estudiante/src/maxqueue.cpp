/**
 * @file MaxQueue.cpp
 * @brief  Archivo de implementación del TDA MaxQueue
 * @author  Marvin Augusto Fonseca Zamora
 */

#include "maxqueue.h"
#include <map>
#include <set>

ostream& operator<<(ostream &flujo, const element &dato){
    
    flujo << dato.value << ',' << dato.maximum;
    
    return flujo;
}

void MaxQueue:: push(int dato){
    
    if(s1.empty()){
        s1.push(element{dato,dato});
        
    }else{
                
        bool hayNuevoMax = s1.top().maximum < dato;
        element nuevo = {dato, hayNuevoMax ? dato:s1.top().maximum};
        
        while(!s1.empty()){
            
            element aux = s1.top();

            if(hayNuevoMax)
                aux.maximum = dato;
            
            s2.push(aux);
            s1.pop();
        }
        
        s2.push(nuevo);
        
        while(!s2.empty()){
            s1.push(s2.top());
            s2.pop();
        }
    }
}

void MaxQueue::pop(){
    
    if(!s1.empty()){
        
        if(s1.top().value == s1.top().maximum){
            
            int max = s1.top().maximum;
            s1.pop();
            //int max = -1e20;
            

            while(!s1.empty()){
                
                if(max < s1.top().value)
                    max = s1.top().value;
                
                s2.push(s1.top());
                s1.pop();
            }
            
            //vuelco y al hacerlo modifico el nuevo maximo
            while(!s2.empty()){
                element aux = s2.top();
                aux.maximum = max;
                s1.push(aux);
                s2.pop();
            }
            
        }else{
            s1.pop();
        }
    }
        
}

bool MaxQueue:: empty() const{
    
    return s1.empty();
}

element MaxQueue::front() const{
    
    element dato;
    
    if(!s1.empty())
        dato = s1.top();
    
    return dato;
}


MaxQueue MaxQueue::interseccion(MaxQueue q1, MaxQueue q2){
    MaxQueue resultado;
    
    while(!q1.empty()){
        int x=q1.front().value;
        q1.pop();
        bool found=false;
        MaxQueue tempQ;
        while(!q2.empty()){
            int y=q2.front().value;
            q2.pop();
            if(!found && y==x){
                found = true;
            }else{
                tempQ.push(y);
            }
        }
        while(!tempQ.empty()){
            q2.push(tempQ.front().value);
            tempQ.pop();
        }
        if(found){
            resultado.push(x);
        }
    }
    return resultado;
    
    /*MaxQueue resultado;
    set<int> setQ2;

    while(!q2.empty()){
        int v = q2.front().value;
        setQ2.insert(v);
        q2.pop();
    }
    while(!q1.empty()){
        int v = q1.front().value;
        //set.find return An iterator to the element, 
        //if val is found, or set::end otherwise.
        if(setQ2.find(v)!=setQ2.end()){
            resultado.push(v);
            setQ2.erase(v);
        }
        q1.pop();
    }
    return resultado;*/
}