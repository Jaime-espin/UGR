/**
 * @file maxqueue.h
 * @brief  Archivo de especificación del TDA MaxQueue
 * @author Marvin Fonseca Zamora, Jaime Espín Rodríguez
 */

#ifndef maxqueue_h
#define maxqueue_h
#include <iostream>
#include <stack>

using namespace std;

struct element{
        
    int value=0;
    int maximum=0;
};

/**
 * @brief Sobrecarga << para insertar un 'element' en el flujo de salida
 * @param  flujo flujo de salida
 * @param  dato de tipo ''element' para insertar en el flujo de salida
 * @return Devuelve referencia al flujo de salida
 */
ostream& operator<<(ostream &flujo, const element &dato);

class MaxQueue{
  
private:
    
    stack<element> s1, s2;
    
public:

    /**
     * @brief Agrega un nuevo elemento al principio de la cola
     * 
     * @param elemento que se añade
     */
    void push(int elemento);

    /**
     * @brief Elimina el elemento al frente de la cola
     * 
     */
    void pop();
    
    /**
     * @brief Cola Vacia
     * @return Devuelve true/false si la cola esta vacia
     */
    bool empty() const;
    
    /**
     * @brief Elemento front
     * @return Devuelve una copia del elemento al frente de la cola
     */
    element front() const;
    

    /**
     * @brief Devuelve una cola con los elementos en las dos colas dadas
     * 
     * @param q1 cola que se intersecta
     * @param q2 cola que se intersecta
     * @return MaxQueue contiene los elementos de la intersección
     */
    MaxQueue interseccion(MaxQueue q1, MaxQueue q2);
};

#endif
