#ifndef __LETRAS_H__
#define __LETRAS_H__

#include <string>

using namespace std;

/**
 * @brief TDA LETRASInfo
 *
 * Contiene información sobre un determinado carácter del juego de las
 * letras. En concreto, almacena información sobre el número de repeticiones de
 * la letra en la partida y de la puntuación que otorga al utilizarse en una
 * palabra.
 */

class Letra{
    
public:
    char letra;
    unsigned long num_repeticiones;
    int puntuacion;

    /**
     * @brief Constructor. Inicializa una nueva letra con valores nulos por defecto.
     */
    Letra(char l = '\0', unsigned long r = 0, int p = 0);

    /**
     * @brief Operador de igualdad.
     * @param l Letra a comparar
     * @return Devuelve true si this letra (char) es igual a la letra de l,
     * en caso contrario devuelve false
     */
    bool operator==(const Letra & l) const;
    
    /**
     * @brief Operador comparador <.
     * @param l Letra a comparar
     * @return Devuelve true si this letra (char) es menor a la letra de l,
     * en caso contrario devuelve false
     */
    bool operator <(const Letra & l) const;
    
};






#endif