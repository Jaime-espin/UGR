
#ifndef __JUEGO__H__
#define __JUEGO__H__

/* ***************************************** */

#include "tablero.h"
#include "jugador.h"

/* ***************************************** */


class Juego3Raya {
  private:
    Jugador jug1, jug2;    // Jugadores
    Tablero tab;           // Tablero
    int turno;             // A quien le toca jugar

  public:
    // No existe constructor por defecto
    // Contructor. Para crear un nuevo juego hemos de dar un tablero
    // y dos jugadores obligatoriamente
    /**
     * @brief Constructor de la clase Juego3Raya.
     * 
     * Crea un nuevo juego de 3 en raya inicializando el tablero y los dos jugadores.
     * 
     * @param t Referencia constante al tablero que se usará en la partida.
     * @param j1 Referencia constante al primer jugador.
     * @param j2 Referencia constante al segundo jugador.
     */
    Juego3Raya(const Tablero &t, const Jugador &j1, const Jugador &j2);

    /**
     * @brief Destructor de la clase Juego3Raya.
     * 
     * Libera los recursos asociados al juego. En este caso, el destructor es vacío
     * porque no se realiza ninguna operación especial al destruir el objeto.
     */
    ~Juego3Raya()  { };

    /**
     * @brief Inicia una nueva partida de tres en raya.
     *
     * Este método prepara el estado del juego para comenzar una nueva partida.
     * Concreta las siguientes acciones:
     *  - Cambia el turno al siguiente jugador: se hace comenzar la nueva partida
     *    al jugador que no comenzó la partida anterior (habitualmente el que
     *    perdió la anterior).
     *  - Limpia el tablero, dejando todas las casillas en blanco.
     *
     * @pre El objeto Juego3Raya debe estar correctamente inicializado.
     * @post El tablero queda completamente vacío; turno contiene 0 o 1
     *       indicando el jugador que empieza la nueva partida.
     */
    void NuevoJuego();

    /**
     * @brief Ejecuta un turno de juego para el jugador actual.
     *
     * Este método solicita al jugador cuyo turno es actual que piense su jugada
     * (fila y columna). Si la jugada propuesta no es válida, se repite la
     * petición hasta que el jugador proporcione una jugada válida que. Una vez 
     * colocada la ficha correctamente, el turno avanza al otro jugador.
     *
     * @pre El objeto debe estar inicializado correctamente.
     * @post Se habrá colocado exactamente una ficha válida en el tablero y
     *       el turno habrá avanzado al siguiente jugador.
     */
    void JugarTurno();

    /**
     * @brief Devuelve una referencia constante al tablero de la partida.
     *
     * @return Referencia constante al tablero interno `tab`.
     * @pre El objeto debe estar correctamente inicializado.
     */
    const Tablero &ElTablero() const { return tab; };

    /**
     * @brief Devuelve una referencia constante unos de los jugadores.
     *
     * @param n El numero del jugador que se desea obtener.
     * @return Referencia constante al jugador indicado.
     * @pre 'n' debe ser 0 o 1.
     */
    const Jugador &ElJugador(int n) const;

    /**
     * @brief Indica si el juego ha acabado.
     * 
     * @return devuelve un booleano constante:
     *          - true si hay 3 en raya o empate.
     *          - false en otro caso.
     */
    bool HemosAcabado() const;

    /**
     * @brief Indica que jugador debe jugar.
     * 
     * @return Devuelve el atributo turno que indica a cual de los
     *         dos jugadores le toca.
     */
    int AQuienLeToca() const  { return turno; };

    /**
     * @brief Indica el jugador que ha ganado la partida.
     * 
     * @return Devuelve el numero del jugador ganador (0 o 1),
     *         en otro caso devuelve -1.
     */
    int QuienGana() const;
};

/* ***************************************** */

#endif
