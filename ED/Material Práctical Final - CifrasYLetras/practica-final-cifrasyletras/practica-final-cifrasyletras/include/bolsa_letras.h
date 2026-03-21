#ifndef __BOLSA_LETRAS_H__
#define __BOLSA_LETRAS_H__

#include "letras.h"
#include <vector>
#include <algorithm>
#include <random>
#include "letras_set.h"

using namespace std;

/**
 * @brief TDA BolsaLetras
 *
 */

class BolsaLetras{
private:
    vector<char> bolsa;
    
public:
    /**
     * @brief Constructor por defecto.
     */
    BolsaLetras() = default;
    
    /**
     * @brief Constructor con parametros. Inserta
     * las letras en bolsa y las mezcla
     * @param conjunto Conjunto de LettersSet a insertar en bolsa
     */
    BolsaLetras(const LettersSet &conjunto);
    
    /**
     * @brief Constructor de Copia
     * @param bl El objeto para llenar la bolsa
     */
    BolsaLetras(const BolsaLetras &bl){
        this->bolsa = bl.bolsa;
    }
    
    /**
     * @brief Sobrecarga del operador de asignacion.
     * @param bl El objeto a copiarse en this.bolsa.
     * @return Devuelve referencia al objeto recien copiado.
     */
    BolsaLetras& operator=(const BolsaLetras &bl);
    
    /**
     * @brief Obtiene el número total de caracteres en la bolsa.
     */
    unsigned long size() const {
        return bolsa.size();
    };
    
    /**
     * @brief Obtiene el número total de caracteres en la bolsa.
     * @return Devuelve true si la bolsa esta vacia, false en caso contrario.
     */
    bool empty() const{
        return bolsa.empty();
    }
    
    /**
     * @brief Extrae una secuencia aleatoria de num_letras_.
     * @param num_letras Número de letras a extraer.
     * @return vector<char> con las letras seleccionadas aleatoriamente.
     */
    vector<char> get_letras_aleatorias(int num_letras);
    
    private:
    /**
     * @brief Mezcla aleatoriamente todos los caracteres contenidos en la bolsa.
     */
    void mezclar();
};

#endif