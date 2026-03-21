#ifndef __JUGADOR__H__
#define __JUGADOR__H__

/* ***************************************** */

#include <iostream>
#include <string>
#include "ficha.h"
#include "tablero.h"

/* ***************************************** */

class Jugador {
  private:
    std::string nombre;     // Nombre del jugador
    Ficha fic;              // Color de la ficha (cruz o circulo)
    int nivel;              // Nivel del jugador


    /**
     * @brief Estrategia de juego para el nivel 0 (jugador humano).
     * 
     * @param tab Tablero actual del juego.
     * @param fil Referencia a la fila donde se colocará la ficha.
     * @param col Referencia a la columna donde se colocará la ficha.
     */
    void piensa_nivel_0(const Tablero &tab, int &fil, int &col) const;

    /**
     * @brief Estrategia de juego para el nivel 1 (CPU básica).
     * 
     * @param tab Tablero actual del juego.
     * @param fil Referencia a la fila donde se colocará la ficha.
     * @param col Referencia a la columna donde se colocará la ficha.
     */
    void piensa_nivel_1(const Tablero &tab, int &fil, int &col) const;

  public:
    // No existe constructor por defecto. Cuando construimos un objeto de tipo
    // jugador debemos asignarle un nombre y un color obligatoriamente.

    /**
     * @brief Constructor de la clase jugadore
     * 
     * @param n Nombre del jugador
     * @param f Color de la ficha (cruz o circulo) del jugador
     * @param ni Entero que indica el nivel del juego (0 o 1)
     */
    Jugador(const std::string &n, const Ficha &f, int ni);

    /**
     * @brief Destructor del objeto Jugador
     * 
     */
    ~Jugador() { };     // El destructor est� vacio

    /**
     * @brief Devuelve el nombre del jugador.
     * 
     * @return Nombre del jugador.
     */
    std::string Nombre() const         { return nombre; };

    /**
     * @brief Devuelve el color de la ficha del jugador.
     * 
     * @return Color de la ficha.
     */
    Ficha Color() const                { return fic; };

    /**
     * @brief Devuelve la posición donde el jugador desea colocar su ficha.
     * 
     * Utiliza el nivel del jugador para determinar la estrategia a seguir.
     * 
     * @param tab Tablero actual del juego.
     * @param fil Referencia a la fila donde se colocará la ficha.
     * @param col Referencia a la columna donde se colocará la ficha.
     */
    void PiensaJugada(const Tablero &tab, int &fil, int &col) const;


};

/* ***************************************** */

/**
 * @brief Operador de salida para mostrar los datos del jugador por consola
 */
std::ostream& operator<<(std::ostream &salida, const Jugador &jug);

/* ***************************************** */

#endif
