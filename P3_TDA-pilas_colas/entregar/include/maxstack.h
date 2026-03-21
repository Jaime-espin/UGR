/**
 * @file maxstack.h
 * @brief  Archivo de especificación del TDA MaxStack
 * @author Marvin Fonseca Zamora, Jaime Espín Rodríguez
 */

#ifndef maxstack_h
#define maxstack_h
#include <iostream>
#include <queue>
#include <string>

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

class MaxStack{
  
private:
    /*Se usan dos colas porque con 
    q1 se mantienen los elementos en orden de la pila
    q2 sirve como espacio temporal para reorganizar*/
    queue<element> q1, q2;
    
public:
    
    /**
     * @brief Agrega un nuevo elemento  "arriba" de la pila
     * 
     * @param elemento elemento que se añade
     */
    void push(int elemento);

     /**
      * @brief Elimina el elemento de "arriba" de la pila
      * 
      */
    void pop();
    
    /**
     * @brief Pila Vacia
     * @return Devuelve true/false si la pila esta vacia
     */
    bool empty() const;
    
    /**
     * @brief Elemento top
     * @return Devuelve copia del elemento de "arriba" de la pila
     */
    element top() const;

};

#endif // maxstack_h
