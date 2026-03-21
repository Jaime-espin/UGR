#ifndef __LETRAS_SET_H__
#define __LETRAS_SET_H__
#include <set>
#include <iostream>
#include <iomanip>
#include <iterator>
#include <string>
#include <vector>
#include "letras.h"
#include "diccionario.h"

class BolsaLetras;

using namespace std;

/**
 * @brief TDA LettersSet
 *
 * Este TDA representa un conjunto de letras, con la información necesaria para
 * jugar una partida al juego de las letras, es decir, el número de repeticiones
 * que tenemos de la letra y la puntuación que dicha letra otorga cuando se
 * utiliza en una palabra
 */

const int ESPACIO = 10;

class LettersSet{
    
private:
    set<Letra> letras;
    
public:
    
    /**
     * @brief Constructor por defecto.
     * Crea un LettersSet vacío.
     */
    LettersSet() = default;
    
    /**
     * @brief Constructor por parametros.
     * @param l Objeto LettersSet a copiar en el objeto this
     */
    LettersSet(const set<Letra> &l){
        this->letras = l;
    }
    
    /**
     * @brief Constructor de copia.
     * @param cl Objeto LettersSet a copiar en el objeto this
     */
    LettersSet(const LettersSet& cl){
        copy(cl);
    }
    
    /**
     * @brief Operador de Asignacion
     * @param cl El objeto LettersSet a copiar en el objeto this.
     * @return Devuelve referencia a this LetterSet
     */
    LettersSet& operator=(const LettersSet& cl);
    
    /**
     * @brief Obtiene el número de letras diferentes almacenadas en el conjunto.
     * @return El número de letras diferentes en el LettersSet.
     */
    unsigned long size() const{
        return letras.size();
    }
    
    /**
     * @brief Comprueba si el conjunto está vacío.
     * @return true si el conjunto no contiene letras, false en caso contrario.
     */
    bool empty() const{
        return letras.empty();
    }
    
    /**
     * @brief Inserta una letra en el conjunto.
     * @param letra El objeto Letra a insertar.
     */
    void insert(const Letra &letra);
    
    /**
     * @brief Determina una letra existe dentro del conjunto.
     * @param letra El carácter de la letra a encontrar.
     * @return true si la letra esta en el conjunto, false si no se encontró.
     */
    bool exists(const Letra &letra) const{
        return letras.find(letra) != letras.end();
    }
    
    /**
     * @brief Elimina una letra del conjunto.
     * @param letra El carácter de la letra a eliminar.
     * @return true si la letra fue eliminada, false si no se encontró.
     */
    bool remove(const Letra &letra){
        return letras.erase(letra) > 0;
    }
    
    /**
     * @brief Obtener la puntuación de una letra.
     * @param letra El carácter de la letra cuya puntuación se desea obtener.
     * @return La puntuación (int) de la letra solicitada. Si la letra no existe, devuelve 0.
     */
    
    int getPuntuacion(const Letra &letra) const;
    
    /**
     * @brief Obtener la repeticion de una letra.
     * @param letra El carácter de la letra cuya repeticion se desea obtener.
     * @return La cantidad de veces que esta presente (int) de la letra solicitada.
     *         Si la letra no existe, devuelve 0
     */
    unsigned long getRepeticiones(const Letra &letra) const;
    
    /**
     * @brief Modifica la puntuación de una letra.
     * @param letra El carácter de la letra cuya puntuación se desea modificar.
     * @return Devuelve true si la letra existe, en caso contrario, devuelve FALSE.
     */
    bool setPuntuacion(const Letra &letra, const int p);
    
    /**
     * @brief Modifica la repeticion de una letra.
     * @param letra El carácter de la letra cuya repeticion se desea modificar.
     * @return Devuelve true si la letra existe, en caso contrario devuelve false.
     */
    bool setRepeticiones(const Letra &letra, const int r);
    
    
    class iterator{
      
    private:
        set<Letra>::iterator it;
    public:
        iterator() = default;
        iterator(const iterator &i){ it = i.it; }
        iterator(const set<Letra>::iterator &cl){ it = cl; }
        iterator& operator=(const iterator &i);
        iterator& operator=(const set<Letra>::iterator &cl);
        const Letra& operator *() const { return *it; }
        iterator& operator++();
        iterator& operator--();
        bool operator==(const iterator& i) const { return it == i.it; }
        bool operator!=(const iterator& i) const { return it != i.it; }
        
        friend class LettersSet;
    };
    iterator begin(){
        return iterator(letras.begin());
    };
    iterator end(){
        return iterator(letras.end());
    }
    
    class const_iterator{
      
    private:
        set<Letra>::const_iterator const_it;
    public:
        const_iterator() = default;
        const_iterator(const const_iterator &i) { const_it = i.const_it; }
        const_iterator(const set<Letra>::const_iterator &cl) { const_it = cl; }
        const_iterator& operator=(const const_iterator &i);
        const_iterator& operator=(const set<Letra>::const_iterator &cl);
        const Letra& operator *() const { return *const_it; }
        const_iterator& operator++();
        const_iterator& operator--();
        bool operator==(const const_iterator& i) const { return  const_it == i.const_it;}
        bool operator!=(const const_iterator& i) const { return  const_it != i.const_it;}
        
        friend class LettersSet;
        
    };

    const_iterator begin() const{
        return const_iterator(letras.begin());
    }
    const_iterator end() const{
        return const_iterator(letras.end());
    }
    const_iterator cbegin() const{
        return const_iterator(letras.cbegin());
    }
    const_iterator cend() const{
        return const_iterator(letras.cend());
    }
    
private:
    
    /**
     * @brief Funcion auxiliar del constructor de copia y
     * del operador de asignacion
     * @param cl Objeto LetterSet a copiar en objeto this
     */
    void copy(const LettersSet &cl){
        this->letras = cl.letras;
    }
    
    /**
     * @brief Remplaza numRepeticiones o puntuacion de una letra del conjunto
     * @param antigua Objeto Letra a reemplazar
     * @param nueva Objeto Letra reemplazo
     * @pre La letra debe de existir
     */
    void replace(const Letra &antigua, const Letra &nueva);

};

/**
 * @brief Operador de extracción de flujo. Lee un LettersSet desde un istream.
 * @param is Flujo de entrada.
 * @param cl El objeto LettersSet donde se almacenará la lectura.
 * @return Referencia al flujo de entrada para permitir encadenamiento.
 */
istream& operator>>(istream &is, LettersSet &cl);

/**
 * @brief Operador de inserción de flujo. Escribe un LettersSet a un ostream.
 * El formato de escritura debe incluir las cabeceras y los datos de cada letra.
 * @param os Flujo de salida.
 * @param cl El objeto LettersSet a escribir.
 * @return Referencia al flujo de salida para permitir encadenamiento.
 */
ostream& operator<<(ostream &os, const LettersSet &cl);


/**
 * @brief Calcula la puntuación total de una palabra según un conjunto de letras.
 * @param palabra La palabra cuya puntuación se desea calcular.
 * @param conjunto El conjunto de letras que contiene la información de puntuación de cada carácter.
 * @return La puntuación total de la palabra. Si una letra de la palabra no existe en set_letras, no se puntúa.
 **/
int CalcularPuntuacion(const string &palabra, const LettersSet &conjunto);

/**
 * @brief Encuentra la mejor palabra del diccionario que se pueden formar con las letras disponibles, según la modalidad.
 * @param D Diccionario de palabras válidas.
 * @param disponibles Vector de caracteres disponibles para formar palabras.
 * @param conjunto Objeto LettersSet con las puntuaciones y repeticiones de cada letra.
 * @param modo El modo de juego ('L' para Longitud y 'P' para Puntuación).
 * @return Un vector de strings con la(s) mejor(es) palabra(s) encontrada(s).
 **/
vector<string> EncontrarMejoresPalabras(const Diccionario &D, const vector<char> &disponibles, const LettersSet &conjunto, char modo);

/**
 * @brief Comprueba si una palabra se puede formar con las letras disponibles.
 * @param palabra La palabra a comprobar.
 * @param disponibles Un vector de caracteres con las letras que se tienen.
 * @return true si la palabra se puede formar usando las letras disponibles, false en caso contrario.
 **/
bool PuedeFormar(const string &palabra, const vector<char> &disponibles);

/**
 * @brief Función auxiliar para imprimir letras
 * @param letras Vector de caracteres a imprimir.
 */
void Imprimir(const vector<char>& letras);

/**
 * @brief Procesa una ronda del juego de letras.
 * @param D Objeto diccionario.
 * @param L Objeto LettersSet con la informacion de puntuacion.
 * @param B Objeto BolsaLetras para generar letras aleatorias.
 * @param num_letras Numero de letras a generar.
 * @param modo Modalidad de juego (L o P).
 */
void JugarRonda(const Diccionario& D, const LettersSet& L, BolsaLetras& B, int num_letras, char modo);

#endif