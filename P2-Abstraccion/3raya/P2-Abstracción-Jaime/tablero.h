
#ifndef __TABLERO__H__
#define __TABLERO__H__

/* ***************************************** */

#include <iostream>
#include "ficha.h"

/* ***************************************** */

class Tablero {

  private:
    Ficha tab[3][3];      // Tablero de fichas 3x3
    int numfichas;        // N�mero de fichas que han sido puestas en total

    /**
     * @brief Copia un tablero
     * 
     * @param orig el tablero de origen que se copia
     */
    void copia_tablero(const Tablero &orig);

    /**
     * @brief Indica si la ficha tiene 3 en raya
     * 
     * @param fic Ficha que se comprueba
     * @return true si la ficha tiene tres en raya
     * @return false si no tiene tres en raya
     */
    bool hay3raya(const Ficha &fic) const;

  public:
    /**
     * @brief Constructor por defecto
     * 
     */
    Tablero();

    /**
     * @brief Destructor del objeto tablero
     * 
     */
    ~Tablero() { };

    /**
     * @brief Constructor de copia
     * 
     * @param orig Tablero que se copia
     */
    Tablero(const Tablero &orig);

    /**
     * @brief Sobrecarga del operador de asignación
     * 
     * @param orig Tablero que se copia
     * @return Devuelve tablero
     */
    Tablero& operator=(const Tablero &orig);    // Sobrecarga de asignaci�n

    /**
     * @brief Pone en blanco el tablero
     * 
     */
    void PonerEnBlanco();     // No es necesario

    /**
     * @brief Pone una ficha en la casilla indicada
     * 
     * @pre La casilla (f,c) debe estar en blando
     * @param f fila de la casilla en la que se pone la ficha
     * @param c columna de la casilla en la que se pone la ficha
     * @param fic Ficha que se colocará
     * @return true si la operación ha tenido exito
     * @return false si no tiene exito la operación
     */
    bool PonFicha(int f, int c, const Ficha &fic);

    /**
     * @brief Devuelve el color de la ficha que hay en la posicion
     * 
     * @param f fila de la casilla
     * @param c columna de la casilla
     * @return Ficha que hay en la casilla
     */
    Ficha QueFichaHay(int f, int c) const;

    /**
     * @brief Devuelve si hay algun color que tenga tres en raya.
     * 
     * @return Ficha que consiguió el tres en ralla.
     *        Si no hay devuelve el valor en blanco.
     */
    Ficha Busca3Raya() const;

    /**
     * @brief Indica el numero de fichas en el tablero
     * 
     * @return int numero de fichas en el tablero
     */
    int CuantasFichas() const { return numfichas; };

};

/**
 * @brief Operador de salida para mostrar el tablero por consola.
 */
std::ostream& operator<<(std::ostream &salida, const Tablero &tab);

/* ***************************************** */

#endif
