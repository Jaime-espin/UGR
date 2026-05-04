#ifndef COMPORTAMIENTOINGENIERO_H
#define COMPORTAMIENTOINGENIERO_H

#include <chrono>
#include <list>
#include <map>
#include <set>
#include <thread>
#include <time.h>

#include "comportamientos/comportamiento.hpp"

struct EstadoI {
    ubicacion site;
    bool zapatillas;
    
    bool operator==(const EstadoI &st) const {
        return site == st.site and zapatillas == st.zapatillas;
    }

    // El mapa (std::map) necesita esto para funcionar
    bool operator<(const EstadoI &st) const {
        if (site.f < st.site.f) return true;
        if (site.f == st.site.f and site.c < st.site.c) return true;
        if (site.f == st.site.f and site.c == st.site.c and site.brujula < st.site.brujula) return true;
        if (site.f == st.site.f and site.c == st.site.c and site.brujula == st.site.brujula and zapatillas < st.zapatillas) return true;
        return false;
    }
};

struct NodoI {
    EstadoI estado;
    list<Action> secuencia;
    
    bool operator==(const NodoI &node) const{
        return estado == node.estado;
    }
    
    // Operador < para poder usar std::set y hacer la búsqueda eficiente
    bool operator<(const NodoI &node) const {
        if (estado.site.f < node.estado.site.f) return true;
        if (estado.site.f == node.estado.site.f and estado.site.c < node.estado.site.c) return true;
        if (estado.site.f == node.estado.site.f and estado.site.c == node.estado.site.c and estado.site.brujula < node.estado.site.brujula) return true;
        if (estado.site.f == node.estado.site.f and estado.site.c == node.estado.site.c and estado.site.brujula == node.estado.site.brujula and estado.zapatillas < node.estado.zapatillas) return true;
        return false;
    }
};

struct NodoI_Astar {
    EstadoI estado;
    list<Action> secuencia;
    
    int g_cost; 
    int f_cost; 
    
    bool operator==(const NodoI_Astar &node) const {
      return estado == node.estado;
    }
    
    // La priority_queue necesita esto para sacar siempre el coste más bajo
    bool operator<(const NodoI_Astar &node) const {
      return f_cost > node.f_cost;
    }
};

struct EstadoTuberia{
  ubicacion site;
  int altura_tuberia;

  bool operator==(const EstadoTuberia &est) const {
    return site == est.site && altura_tuberia == est.altura_tuberia;
  }

  bool operator<(const EstadoTuberia &est) const {
    if (site.f < est.site.f) return true;
    if (site.f == est.site.f && site.c < est.site.c) return true;
    if (site.f == est.site.f && site.c == est.site.c && altura_tuberia < est.altura_tuberia) return true;
    return false;
  }
};

struct NodoTuberia{
  EstadoTuberia estado_tub;
  list<Paso> secuencia;
  int g_cost; //Longitud tubería
  int f_cost; // g_cost + heuristica
  int impacto;

  bool operator<(const NodoTuberia &node) const {
    // 1. Prioridad principal: El camino más corto estimado
    if (f_cost == node.f_cost) {
      
      // 2. Primer desempate: El camino que menos contamine
      if (impacto == node.impacto) {
        
        // 3. SEGUNDO DESEMPATE (Tu intuición): Preferir la mayor altura (seguir plano)
        // Como es una cola de prioridad max-heap, devolver '<' hace que el mayor suba.
        return estado_tub.altura_tuberia < node.estado_tub.altura_tuberia; 
      }
      return impacto > node.impacto; 
    }
    return f_cost > node.f_cost;
  }
};

class ComportamientoIngeniero : public Comportamiento {
public:
  // =========================================================================
  // CONSTRUCTORES
  // =========================================================================
  
  /**
   * @brief Constructor para niveles 0, 1 y 6 (sin mapa completo)
   * @param size Tamaño del mapa (si es 0, se inicializa más tarde)
   */
  ComportamientoIngeniero(unsigned int size = 0) : Comportamiento(size) {
    // Inicializar Variables de Estado
    last_action=IDLE;
    tiene_zapatillas=false;
    giro45Izq=0;
    girando=0;
    iteracion_actual = 0;
    mapaVisitas.assign(size, vector<int>(size,0));
  }

  /**
   * @brief Constructor para niveles 2, 3, 4 y 5 (con mapa completo conocido)
   * @param mapaR Mapa de terreno conocido
   * @param mapaC Mapa de cotas conocido
   */
  ComportamientoIngeniero(std::vector<std::vector<unsigned char>> mapaR, 
                         std::vector<std::vector<unsigned char>> mapaC): 
                         Comportamiento(mapaR, mapaC) {
    // Inicializar Variables de Estado
    plan.clear();
    hayPlan = false;
    tiene_zapatillas = false;
    faseNivel5 = 0;
    planTuberiasVec.clear();
    // Inicializar variables del Nivel 6
    faseNivel6 = 0;
    vida_inicial = -1;
    metas_descubiertas = 0;
    meta_f = -1;
    meta_c = -1;
    niebla_inaccesible.clear();
  }

  ComportamientoIngeniero(const ComportamientoIngeniero &comport)
      : Comportamiento(comport) {}
  ~ComportamientoIngeniero() {}

  /**
   * @brief Bucle principal de decisión del agente.
   * Estudia los sensores y decide la siguiente acción.
   * 
   * EJEMPLO DE USO:
   * Action accion = think(sensores);
   * return accion; // El motor ejecutará esta acción
   */
  Action think(Sensores sensores);

  ComportamientoIngeniero *clone() {
    return new ComportamientoIngeniero(*this);
  }

  // =========================================================================
  // ÁREA DE IMPLEMENTACIÓN DEL ESTUDIANTE
  // =========================================================================

  // Funciones específicas para cada nivel (para ser implementadas por el alumno)
  
  /**
   * @brief Implementación del Nivel 0.
   * @param sensores Datos actuales de los sensores del agente.
   * @return Acción a realizar.
   */
  Action ComportamientoIngenieroNivel_0(Sensores sensores);
  
  /**
   * @brief Implementación del Nivel 1.
   * @param sensores Datos actuales de los sensores del agente.
   * @return Acción a realizar.
   */
  Action ComportamientoIngenieroNivel_1(Sensores sensores);
  
  /**
   * @brief Implementación del Nivel 2.
   * @param sensores Datos actuales de los sensores del agente.
   * @return Acción a realizar.
   */ 
  Action ComportamientoIngenieroNivel_2(Sensores sensores);
  
  /**
   * @brief Implementación del Nivel 3.
   * @param sensores Datos actuales de los sensores del agente.
   * @return Acción a realizar.
   */
  Action ComportamientoIngenieroNivel_3(Sensores sensores);
  
  /**
   * @brief Implementación del Nivel 4.
   * @param sensores Datos actuales de los sensores del agente.
   * @return Acción a realizar.
   */
  Action ComportamientoIngenieroNivel_4(Sensores sensores);
  
  /**
   * @brief Implementación del Nivel 5.
   * @param sensores Datos actuales de los sensores del agente.
   * @return Acción a realizar.
   */
  Action ComportamientoIngenieroNivel_5(Sensores sensores);
  
  /**
   * @brief Implementación del Nivel 6.
   * @param sensores Datos actuales de los sensores del agente.
   * @return Acción a realizar.
   */
  Action ComportamientoIngenieroNivel_6(Sensores sensores);

protected:
  // =========================================================================
  // FUNCIONES PROPORCIONADAS
  // =========================================================================

  /**
   * @brief Actualiza la información del mapa interno basándose en los sensores.
   * IMPORTANTE: Esta función ya está implementada. Actualiza mapaResultado y mapaCotas
   * con la información de los 16 sensores (casilla actual + 15 casillas alrededor).
   */
  void ActualizarMapa(Sensores sensores);

  /**
   * @brief Comprueba si una casilla es transitable.
   * @param f Fila de la casilla.
   * @param c Columna de la casilla.
   * @param tieneZapatillas Indica si el agente posee zapatillas.
   * @return true si la casilla es transitable (no es muro ni precipicio).
   */
  bool EsCasillaTransitableLevel0(int f, int c, bool tieneZapatillas);

  /**
   * @brief Comprueba si la casilla de delante es accesible por diferencia de altura.
   * REGLAS: Desnivel máximo 1 sin zapatillas, 2 con zapatillas.
   * @param actual Estado actual del agente (fila, columna, orientacion).
   * @return true si el desnivel con la casilla de delante es admisible.
   */
  bool EsAccesiblePorAltura(const ubicacion &actual, bool zap);

  /**
   * @brief Devuelve la posición (fila, columna) de la casilla que hay delante del agente.
   * @param actual Estado actual del agente (fila, columna, orientacion).
   * @return Estado con la fila y columna de la casilla de enfrente.
   */
  ubicacion Delante(const ubicacion &actual) const;

  bool es_camino(unsigned char c) const;

  /**
 * @brief Imprime por consola la secuencia de acciones de un plan para un agente.
 * @param plan  Lista de acciones del plan.
 */
  void PintaPlan(const list<Action> &plan);


/**
 * @brief Imprime las coordenadas y operaciones de un plan de tubería.
 * @param plan  Lista de pasos (fila, columna, operación).
 */
  void PintaPlan(const list<Paso> &plan);


  /**
 * @brief Convierte un plan de acciones en una lista de casillas para
 *        su visualización en el mapa gráfico.
 * @param st    Estado de partida.
 * @param plan  Lista de acciones del plan.
 */
  void VisualizaPlan(const ubicacion &st, const list<Action> &plan);

  /**
 * @brief Convierte un plan de tubería en la lista de casillas usada
 *        por el sistema de visualización.
 * @param st    Estado de partida (no utilizado directamente).
 * @param plan  Lista de pasos del plan de tubería.
 */
  void VisualizaRedTuberias(const list<Paso> &plan);



private:
  // funciones auxiliares nivel 0

  /**
   * @brief Evalúa la visión cercana y aplica memoria para elegir la mejor opción.
   * @param vision_segura Vector de visión filtrado por altura
   * @param mem1, mem2, mem3 Valores de memoria de las 3 casillas adyacentes
   * @param f1, c1, f2, c2, f3, c3 Coordenadas de las casillas adyacentes
   * @return Acción a realizar
   */
  Action EvaluarOpcionesAdyacentes(const vector<unsigned char> &vision_segura, int mem1, int mem2, int mem3);

  /**
   * @brief Evalúa el radar ampliado cuando no hay opciones claras adyacentes.
   * @param vision_segura Vector de visión filtrado por altura
   * @return Acción a realizar basada en el radar lejano
   */
  Action EvaluarRadarAmpliado(const vector<unsigned char> &vision_segura);

  /**
   * @brief Extrae los datos de visión segura y memoria de las celdas adyacentes
   * @param sensores Datos actuales de los sensores
   * @param vision_segura Salida: Vector de visión filtrado por altura
   * @param mem1 Salida: Memoria de la casilla izquierda
   * @param mem2 Salida: Memoria de la casilla frontal
   * @param mem3 Salida: Memoria de la casilla derecha
   */
  void ExtraerDatosDeZonaYMemoria(const Sensores &sensores, vector<unsigned char> &vision_segura, int &mem1, int &mem2, int &mem3);

  // =========================================================================
  // VARIABLES DE ESTADO (PUEDEN SER EXTENDIDAS POR EL ALUMNO)
  // =========================================================================

  Action last_action;     //Almacena la última acción ejecutada
  bool tiene_zapatillas;  //Indica si el agente tiene las zapatillas
  int giro45Izq;          //Indica el número de giros a la izq que quedan por dar
  int girando;            //Para completar un giro si hay obstaculo
  int iteracion_actual; // Para saber en qué "momento" estamos
  vector<vector<int>> mapaVisitas; //Matriz para saber por donde ya pasó

  //Segunda parte
  list<Action> plan;
  bool hayPlan;

  //Nivel 5
  int faseNivel5 = 0;            
  int tramo_idx = 0; // Para saber por qué paso vamos
  vector<Paso> planTuberiasVec; // Más fácil de leer que una list
  
  //Nivel 6
  int faseNivel6 = 0;
  int vida_inicial = -1;
  set<pair<int, int>> niebla_inaccesible;
  bool meta_nueva=false;
  int cont = 0;
  int metas_descubiertas=0;
  int meta_c = -1;
  int meta_f = -1;
  int radio_maximo = 999999;
  list<Paso> plan_temporal;

  void ChequearReinicioNivel6(int vida_actual);
  bool BuscarNuevaNiebla(const Sensores &sensores, int radio_maximo);
  bool ReplanificarTuberiasDesdeInstalado(const Sensores &sensores);
  Action EjecutarConEscudoYEvasion(const Sensores &sensores, Action accion_prevista);
  void AnalizarMapaNivel6(int &num_Us, float &porc_explorado);
  bool NuevaMeta(const vector<vector<unsigned char>> &terreno, int bel_f, int bel_c, int &meta_cercana_f, int &meta_cercana_c);
};

#endif
