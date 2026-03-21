#ifndef __DICCIONARIO_H__
#define __DICCIONARIO_H__

#include <set>
#include <string>
#include <vector>
#include <iostream>
#include <iterator>

using namespace std;
/**
 * @brief TDA DICCIONARIO
 * @details Almacena las palabras de un fichero de texto y permite iterar sobre ellas
 *
 */

class Diccionario{
    
private:
    set<string> datos;
    
public:
    /**
     @brief Construye un diccionario vacío.
     **/
    Diccionario() = default;
    
    /**
     @brief Devuelve el numero de palabras en el diccionario
     **/
    unsigned long size() const {
        return this->datos.size();
    };
    
    /**
     @brief Obtiene todas las palabras en el diccionario de un longitud dada
     @param longitud la longitud de las palabras de salida
     @return un vector con las palabras de longitud especifica en el parametro de entrada
     **/
    vector<string> PalabrasLongitud(int longitud);
    
    /**
     @brief Indica si una palabra está en el diccionario o no
     @param palabra la palabra que se quiere buscar
     @return true si la palabra esta en el diccionario. False en caso contrario
     **/
    bool Esta(string palabra) const;
    
    /**
     @brief Lee de un flujo de entrada un diccionario
     @param is : flujo de entrada
     @param D : el objeto donde se realiza la lectura.
     @return el flujo de entrada
     **/
    friend istream & operator>>(istream & is,Diccionario &D);
    
    /**
     @brief Escribe en un flujo de salida un diccionario
     @param os : flujo de salida
     @param D : el objeto diccionario que se escribe
     @return el flujo de salida
     **/
    friend ostream & operator<<(ostream & os, const Diccionario &D);
    
    class iterator{
        private:
            set<string>::iterator it;
        public:
            iterator () = default;
            string operator *() const;
            iterator& operator ++();
            bool operator ==(const iterator &i) const;
            bool operator !=(const iterator &i) const;
            friend class Diccionario;
    };
    iterator begin();
    iterator end();
    
    class const_iterator{
            private:
                set<string>::const_iterator const_it;
            public:
                const_iterator () = default;
                const string& operator *() const { return *const_it; }
                const_iterator& operator ++() { ++const_it; return *this; }
                bool operator ==(const const_iterator &i) const { return const_it == i.const_it; }
                bool operator !=(const const_iterator &i) const { return const_it != i.const_it; }
                friend class Diccionario;
        };
    
    const_iterator cbegin() const;
    const_iterator cend() const;
    
    
};

#endif
