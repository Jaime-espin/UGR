#include "AgenteEstudiante.hpp"
#include <iostream>
#include <limits>
#include <vector>
#include <algorithm>
#include <cmath>
#include <functional>

AgenteEstudiante::AgenteEstudiante(int id, int profundidadMax, double tiempoMax, int numHeuristica, ModoJuego modo) 
    : id(id), profundidadMax(profundidadMax), tiempoMaxSegundos(tiempoMax), numHeuristica(numHeuristica), modo(modo), abortarBanda(false) {
    nodosVisitados = 0;
}

bool AgenteEstudiante::tieneLimiteDeTiempo() const {
    return modo != ModoJuego::STATUS;
}

std::pair<int, int> AgenteEstudiante::think(const Tablero& tablero) {
    std::pair<int, int> mejor;
    nodosVisitados = 0;
    abortarBanda = false;
    inicioBusqueda = std::chrono::steady_clock::now();

    switch (modo)
    {
    case ModoJuego::ALEATORIO:
        return JuegaAleatorio(tablero);
        break;
    
    case ModoJuego::STATUS:
        Status(tablero, mejor);
        return mejor;
        break;    

    case ModoJuego::MINIMAX:
        minimax(tablero, 0, profundidadMax, mejor);
        return mejor;
        break; 

    case ModoJuego::INTELIGENTE:
        return JuegaInteligente(tablero);   
        break;
    }
        
    return {-1, -1};
}


/**
 * @brief Compara dos tableros para identificar cuál ha sido el movimiento realizado.
 * @param padre Estado inicial del tablero.
 * @param hijo Estado resultante tras un movimiento.
 * @return Un par (fila, columna) con la posición de la nueva pieza.
 */
std::pair<int, int> SacarMovimiento(const Tablero& padre, const Tablero &hijo){
    for(int f=0; f<padre.getFilas(); ++f)
        for(int c=0; c<padre.getColumnas(); ++c)
            if (padre.getCelda(f,c) == 0 && hijo.getCelda(f,c) != 0) 
                return {f, c};
    return {-1, -1};
}

/**
 * @brief Implementa un agente que juega de forma totalmente aleatoria.
 * @param tablero Estado actual del juego.
 * @return La jugada elegida al azar.
 */
std::pair<int, int> AgenteEstudiante::JuegaAleatorio(const Tablero& tablero) {

    // Calculo los tableros descendientes de tablero
    auto sucesores = tablero.getSucesores();

    // Si no tiene descendientes, paso el turno
    if (sucesores.empty()) return {-1, -1};

    // Elijo aleatoriamente uno de los descendientes
    int elegido = rand() % sucesores.size();

    // Saco el movimiento realizado comparando el tablero original con el elegido.
    std::pair<int,int> Mov = SacarMovimiento(tablero, sucesores[elegido]);

    return Mov;
}


/**
 * @brief Algoritmo de resolución completa para estados de final de juego.
 * Determina si una posición está matemáticamente ganada, perdida o empatada.
 * @param tablero Estado a evaluar.
 * @param Mov [Salida] La jugada óptima encontrada.
 * @return Resultado del análisis (VICTORIA, DERROTA o EMPATE).
 */
AgenteEstudiante::Resultado AgenteEstudiante::Status(const Tablero &tablero, std::pair<int,int> &Mov) {
    /* ============== Este trozo de código se tiene que quedar aquí  =============== */
    nodosVisitados++;
    /* ============== Empieza a partir de aquí tu implementación  =============== */
    int estado = tablero.comprobarGanador();
    if(estado==0){//No hay ganador
        auto hijos = tablero.getSucesoresConMovimientos();
        if (hijos.empty()) {
            return Resultado::EMPATE;
        }

        int turno = tablero.getJugadorTurno();
        Resultado mejor_res;
        if(turno==id){
            mejor_res = Resultado::DERROTA;
        }else{
            mejor_res = Resultado::VICTORIA;
        }
        
        Mov = hijos[0].second;
        for (const auto& hijo : hijos) {
            std::pair<int,int> movHijo;
            Resultado res = Status(hijo.first, movHijo);

            if(turno == id){
                if(res == Resultado::VICTORIA){
                    Mov = hijo.second;
                    return Resultado::VICTORIA;
                }else if(res == Resultado::EMPATE){
                    Mov = hijo.second;
                    mejor_res = Resultado::EMPATE;
                }
            }else{
                if(res == Resultado::DERROTA){
                    Mov = hijo.second;
                    return Resultado::DERROTA;
                }else if(res == Resultado::EMPATE){
                    Mov = hijo.second;
                    mejor_res = Resultado::EMPATE;
                }
            }
        }
        return mejor_res;
    }else if(estado==-1){
        return Resultado::EMPATE;
    }else if(estado==id){
        return Resultado::VICTORIA;
    }else if(estado!=id){
        return Resultado::DERROTA;
    }

    return Resultado::EMPATE;
}



/**
 * @brief Implementación del algoritmo Minimax clásico.
 * @param tablero Estado actual.
 * @param profundidad Nivel actual en el árbol de búsqueda.
 * @param prof_Max Límite de profundidad de la búsqueda.
 * @param Mov [Salida] La mejor jugada encontrada en la raíz.
 * @return Valor heurístico del estado.
 */
double AgenteEstudiante::minimax(const Tablero &tablero, int profundidad, int prof_Max, std::pair<int,int> &Mov) {
    /* ============== Este trozo de código se tiene que quedar aquí  =============== */
    nodosVisitados++;
    if (abortarBanda) return 0;
    
    if (std::chrono::duration<double>(std::chrono::steady_clock::now() - inicioBusqueda).count() > tiempoMaxSegundos) {
        abortarBanda = true;
        return 0;
    }
    /* ============== Empieza a partir de aquí tu implementación  =============== */
    int estado = tablero.comprobarGanador();

    if(estado == 0){
        if(profundidad == prof_Max){
            return heuristica(tablero);
        }else{
            auto hijos = tablero.getSucesoresConMovimientos();
            if (hijos.empty()) {
                return 0.0;
            }

            int turno = tablero.getJugadorTurno();
            double mejor_res;
            if(turno==id){
                mejor_res = -99999999999999.0;
            }else{
                mejor_res = 99999999999999.0;
            }
            
            Mov = hijos[0].second;
            for (const auto& hijo : hijos) {
                std::pair<int,int> movHijo;
                double puntuacion_hijo = minimax(hijo.first, profundidad + 1, prof_Max, movHijo);

                if(turno == id){
                    if(puntuacion_hijo > mejor_res){
                        mejor_res = puntuacion_hijo;
                        Mov = hijo.second;
                    }
                }else{
                    if(puntuacion_hijo < mejor_res){
                        mejor_res = puntuacion_hijo;
                        Mov = hijo.second;
                    }
                }
            }
            return mejor_res;
        }
    }else if(estado==-1){ //Empate
        return 0.0;
    }else if(estado==id){ //Ganamos
        return 99999999999999.0;
    }else if(estado!=id){ //Perdemos
        return -99999999999999.0;
    }

    return 0;
}


/**
 * @brief Punto de entrada para el juego inteligente.
 * @param tablero Estado actual del juego.
 * @return La jugada elegida por el algoritmo de búsqueda.
 */
std::pair<int, int> AgenteEstudiante::JuegaInteligente(const Tablero& tablero) {
    std::pair<int,int> Mov;

    double valor = alfaBeta(tablero, 0, profundidadMax, MenosInfinito, MasInfinito, Mov);
    std::cout << "Valor Minimax: " << valor << "\tJugada: (" << Mov.first << ", " << Mov.second << ")\n";
    return Mov;
}




/**
 * @brief Implementación del algoritmo Minimax con Poda Alfa-Beta.
 * @param tablero Estado actual.
 * @param profundidad Nivel actual en el árbol de búsqueda.
 * @param prof_Max Límite de profundidad de la búsqueda.
 * @param alfa Valor mínimo garantizado para el jugador MAX.
 * @param beta Valor máximo garantizado para el jugador MIN.
 * @param Mov [Salida] La mejor jugada encontrada en la raíz.
 * @return Valor heurístico del estado tras la poda.
 */
double AgenteEstudiante::alfaBeta(const Tablero &tablero, int profundidad, int prof_Max, double alfa, double beta, std::pair<int,int> &Mov) {
    /* ============== Este trozo de código se tiene que quedar aquí  =============== */
    nodosVisitados++;
    if (abortarBanda) return 0;
    
    if (std::chrono::duration<double>(std::chrono::steady_clock::now() - inicioBusqueda).count() > tiempoMaxSegundos) {
        abortarBanda = true;
        return 0;
    }
    /* ============== Empieza a partir de aquí tu implementación  =============== */


    return 0;
}

/**
 * @brief Función heurística para evaluar la calidad de un tablero.
 * @param tablero Estado a evaluar.
 * @return Puntuación numérica (positiva para ventaja de J1, negativa para J2).
 */
double AgenteEstudiante::heuristica(const Tablero& tablero) {
    switch(numHeuristica) {
        case 0: return heuristicaPrueba(tablero);
                break;
        case 1: return heuristica1(tablero);
                break;
        case 2: return heuristica2(tablero);
                break;
        default: return heuristica1(tablero);
    }
}

double AgenteEstudiante::heuristicaPrueba(const Tablero& tablero) {
    // n es el número de fichas en línea para ganar.
    int n = tablero.getNParaGanar();
    int oponente = (id == 1) ? 2 : 1;
    double score_positivo = 0;

    double score_negativo = 0;

    for (int f=0; f< tablero.getFilas(); f++ ){
        for (int c = 0; c< tablero.getColumnas(); c++){
            if (tablero.getCelda(f,c) != 0 ){
                int valor = tablero.getFilas()-abs(f-(tablero.getFilas()/2)) + tablero.getColumnas()-abs(c-(tablero.getColumnas()/2)); 
                if (tablero.getCelda(f,c) == id){
                  score_positivo += valor;
                 }
                else {
                  score_negativo += valor;
                }
            }
        }
    }

   
    return score_positivo - score_negativo;
}


double AgenteEstudiante::heuristica1(const Tablero& tablero) {
    int oponente = (id == 1) ? 2 : 1;
    double score_positivo = 0;
    double score_negativo = 0;

    score_positivo += tablero.contarCombinaciones(2, id) * 10.0;
    score_positivo += tablero.contarCombinaciones(3, id) * 100.0;
    score_positivo += tablero.contarCombinaciones(4, id) * 10000.0;

    score_negativo += tablero.contarCombinaciones(2, oponente) * 15.0;
    score_negativo += tablero.contarCombinaciones(3, oponente) * 150.0;
    score_negativo += tablero.contarCombinaciones(4, oponente) * 50000.0;
    /*for(int i=1; i<=2; i++){
        for(int n=2; n<=4; n++){
            if(i == oponente){
                score_negativo += tablero.contarCombinaciones(n, i) * n;
            }else{
                score_positivo += tablero.contarCombinaciones(n, i) * n;
            }
        }
    }*/

    return score_positivo - score_negativo;
}

double AgenteEstudiante::heuristica2(const Tablero& tablero) {
    //A implementar por el estudiante
return 0;
}

