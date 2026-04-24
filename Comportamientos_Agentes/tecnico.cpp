#include "tecnico.hpp"
#include "motorlib/util.h"
#include <iostream>
#include <queue>
#include <set>

using namespace std;

// =========================================================================
// ÁREA DE IMPLEMENTACIÓN DEL ESTUDIANTE
// =========================================================================

Action ComportamientoTecnico::think(Sensores sensores) {
  Action accion = IDLE;


  // Decisión del agente según el nivel
  switch (sensores.nivel) {
    case 0: accion = ComportamientoTecnicoNivel_0(sensores); break;
    case 1: accion = ComportamientoTecnicoNivel_1(sensores); break;
    case 2: accion = ComportamientoTecnicoNivel_2(sensores); break;
    case 3: accion = ComportamientoTecnicoNivel_3(sensores); break;
    case 4: accion = ComportamientoTecnicoNivel_4(sensores); break;
    case 5: accion = ComportamientoTecnicoNivel_5(sensores); break;
    case 6: accion = ComportamientoTecnicoNivel_6(sensores); break;
    case 10: accion = ComportamientoTecnicoNivel_E(sensores); break;
  }

  return accion;
}

/**
 * @brief Determina la mejor opcion entre las 3 casillas que tiene delante
 * 
 * @param i terreno que hay en la poción 1 de superficie (45izq)
 * @param c terreno que hay en la poción 2 de superficie (justo delante)
 * @param d terreno que hay en la poción 3 de superficie (45dch)
 * @return int 2 si es mejor WALK, 1 para TURN_SL y 3 para TURN_SR. 0 no hay nada interesante.
 */
int VeoCasillaInteresanteT(char i, char c, char d){
  if(c=='U') return 2;
  else if (i=='U') return 1;
  else if (d=='U') return 3;
  else if (c=='C') return 2;
  else if (i=='C') return 1;
  else if (d=='C') return 3;
  else return 0;
}

/**
 * @brief Determina la mejor opcion entre todas las casillas que detecta el sensor
 * @param v el vector que contiene el tipo de casillas (idealmente filtrado por altura)
 * @param zap indica si tiene zapatillas
 * @return int 2 si es mejor WALK, 1 para TURN_SL y 3 para TURN_SR. 0 no hay nada interesante.
 */
int VeoCasillaInteresanteTAmpliada(const vector<unsigned char> &v) {
  
  // PRIORIDAD 1: Buscar la META ('U')
  if (v[2] == 'U') return 2; // Meta justo delante
  if (v[1] == 'U' || v[4] == 'U' || v[5] == 'U' || v[9] == 'U' || v[10] == 'U' || v[11] == 'U') return 1; // Meta a la izquierda
  if (v[3] == 'U' || v[7] == 'U' || v[8] == 'U' || v[13] == 'U' || v[14] == 'U' || v[15] == 'U') return 3; // Meta a la derecha
  if (v[6] == 'U' || v[12] == 'U') {
      // Meta lejos de frente. Solo avanzamos si el paso inmediato es un terreno permitido en Nivel 0
      if (v[2] == 'C' || v[2] == 'D' || v[2] == 'U') return 2;
      else return 1; // Si hay un obstáculo, giramos para intentar rodearlo
  }

  // PRIORIDAD 2: Caminos CERCANOS (Distancia 1). Tratamos C y D por igual.
  if (v[2] == 'C' || v[2] == 'D') return 2;
  if (v[1] == 'C' || v[1] == 'D') return 1;
  if (v[3] == 'C' || v[3] == 'D') return 3;

  // PRIORIDAD 3: Anticipar Caminos LEJANOS (Distancia 2 y 3)
  if (v[4] == 'C' || v[4] == 'D' || v[5] == 'C' || v[5] == 'D' || v[9] == 'C' || v[9] == 'D' || v[10] == 'C' || v[10] == 'D' || v[11] == 'C' || v[11] == 'D') return 1;
  if (v[7] == 'C' || v[7] == 'D' || v[8] == 'C' || v[8] == 'D' || v[13] == 'C' || v[13] == 'D' || v[14] == 'C' || v[14] == 'D' || v[15] == 'C' || v[15] == 'D') return 3;
  if (v[6] == 'C' || v[6] == 'D' || v[12] == 'C' || v[12] == 'D') {
      if (v[2] == 'C' || v[2] == 'D' || v[2] == 'U') return 2;
      else return 1;
  }

  // Si no hay absolutamente nada interesante en todo el radar
  return 0;
}

/**
 * @brief Calcula las coordenadas de las casillas 1, 2 y 3 basándose en la posición y rumbo del agente
 */
void ObtenerCoordenadasAdyacentesT(int f, int c, int rumbo, int &f1, int &c1, int &f2, int &c2, int &f3, int &c3) {
    // Array de desplazamientos para N, NE, E, SE, S, SW, W, NW
    int df[] = {-1, -1,  0,  1,  1,  1,  0, -1};
    int dc[] = { 0,  1,  1,  1,  0, -1, -1, -1};
    
    int r2 = rumbo;                 // Frente (Posición 2)
    int r1 = (rumbo + 7) % 8;       // Izquierda (Posición 1)
    int r3 = (rumbo + 1) % 8;       // Derecha (Posición 3)
    
    f2 = f + df[r2]; 
    c2 = c + dc[r2];
    f1 = f + df[r1]; 
    c1 = c + dc[r1];
    f3 = f + df[r3]; 
    c3 = c + dc[r3];
}


/**
 * @brief Comprueba si el técnico puede ir a la casilla por la diferencia de altura.
 * Si tiene zapatillas, el bosque ('B') es transitable como camino.
 * 
 * @param casilla a la que quiere moverse
 * @param dif diferencia de altura entre la casilla actual y a la que se va a mover
 * @param tiene_zapatillas indica si el técnico tiene zapatillas
 * @return char devuelve la casilla objetivo si es viable y P si no lo es
 */

char ViablePorAlturaT(char casilla, int dif, bool tiene_zapatillas){
  return (abs(dif) <= 1 && (casilla != 'B' || tiene_zapatillas)) ? casilla : 'P';
}

// funciones auxiliares del nivel 0

/**
 * @brief Extrae los datos de visión segura y memoria de las celdas adyacentes
 */
void ComportamientoTecnico::ExtraerDatosDeZonaYMemoria(const Sensores &sensores, vector<unsigned char> &vision_segura, int &mem1, int &mem2, int &mem3) {
  // 1. CREAR EL VECTOR DE VISIÓN filtrado usando la altura
  vision_segura = sensores.superficie;
  for(int i = 1; i <= 15; i++) { 
    vision_segura[i] = ViablePorAlturaT(sensores.superficie[i], sensores.cota[i] - sensores.cota[0], tiene_zapatillas);

    // Si vemos al Ingeniero ('i') en CUALQUIER casilla de nuestro radar, 
    // la marcamos temporalmente como un Muro ('M').
    if (sensores.agentes[i] == 'i') {
      vision_segura[i] = 'M';
    }
  }

  // 2. OBTENER COORDENADAS Y LEER MEMORIA de las 3 casillas adyacentes
  int f1, c1, f2, c2, f3, c3;
  ObtenerCoordenadasAdyacentesT(sensores.posF, sensores.posC, sensores.rumbo, f1, c1, f2, c2, f3, c3);

  // Leemos la matriz de visitas. Si está fuera de los bordes del mapa, 
  // asignamos un valor enorme (999999) para ignorarla
  mem1 = (f1 >= 0 && f1 < mapaVisitas.size() && c1 >= 0 && c1 < mapaVisitas[0].size()) 
             ? mapaVisitas[f1][c1] : 999999;
  mem2 = (f2 >= 0 && f2 < mapaVisitas.size() && c2 >= 0 && c2 < mapaVisitas[0].size()) 
             ? mapaVisitas[f2][c2] : 999999;
  mem3 = (f3 >= 0 && f3 < mapaVisitas.size() && c3 >= 0 && c3 < mapaVisitas[0].size()) 
             ? mapaVisitas[f3][c3] : 999999;
}

/**
 * @brief Evalúa las opciones adyacentes (visión cercana) considerando prioridades y memoria.
 * @param vision_segura Vector de visión filtrado por altura
 * @param mem1, mem2, mem3 Contadores de visitas de las casillas izq, frente, dch
 * @return Acción a realizar
 */
Action ComportamientoTecnico::EvaluarOpcionesAdyacentes(const vector<unsigned char> &vision_segura, int mem1, int mem2, int mem3)
{
  char Left = vision_segura[1];    // Casilla izquierda
  char Center = vision_segura[2];  // Casilla frontal
  char Right = vision_segura[3];   // Casilla derecha

  // PRIORIDAD 1: Meta muy cerca
  if (Center == 'U') {
    cout << "  -> ACCION: WALK (Meta al frente)" << endl;
    return WALK;
  }
  else if (Left == 'U') {
    cout << "  -> ACCION: TURN_SL (Meta a la izq)" << endl;
    return TURN_SL;
  }
  else if (Right == 'U') {
    cout << "  -> ACCION: TURN_SR (Meta a la dch)" << endl;
    return TURN_SR;
  }

  // PRIORIDAD 2: Hay caminos viables - elegir el menos visitado
  // Para el Técnico: 'C' (camino) y 'D' (zapatillas) se tratan por igual como navegables
  bool caminoLeft = (Left == 'C' || Left == 'D');
  bool caminoCenter = (Center == 'C' || Center == 'D');
  bool caminoRight = (Right == 'C' || Right == 'D');

  if (caminoLeft || caminoCenter || caminoRight) {
    int minMemory = 999999;
    int bestOption = 0; // 1=izq, 2=frente, 3=dch

    // Evaluamos de frente primero
    if (caminoCenter) {
      minMemory = mem2;
      bestOption = 2;
    }
    // Evaluamos izquierda
    if (caminoLeft && mem1 < minMemory) {
      minMemory = mem1;
      bestOption = 1;
    }
    // Evaluamos derecha
    if (caminoRight && mem3 < minMemory) {
      minMemory = mem3;
      bestOption = 3;
    }

    // Aplicamos la mejor decisión basada en la memoria
    if (bestOption == 2) {
      cout << "  -> ACCION: WALK (Camino menos visitado, mem=" << minMemory << ")" << endl;
      return WALK;
    } else if (bestOption == 1) {
      cout << "  -> ACCION: TURN_SL (Camino menos visitado, mem=" << minMemory << ")" << endl;
      return TURN_SL;
    } else if (bestOption == 3) {
      cout << "  -> ACCION: TURN_SR (Camino menos visitado, mem=" << minMemory << ")" << endl;
      return TURN_SR;
    }
  }

  // No hay opción viable en visión cercana
  return IDLE;
}

/**
 * @brief Evalúa el radar ampliado cuando no hay opciones claras adyacentes.
 * @param vision_segura Vector de visión filtrado por altura
 * @return Acción a realizar basada en el radar ampliado
 */
Action ComportamientoTecnico::EvaluarRadarAmpliado(const vector<unsigned char> &vision_segura)
{
  cout << "  -> Bloqueado o sin opciones inmediatas. Consultando radar ampliado..." << endl;
  int pos = VeoCasillaInteresanteTAmpliada(vision_segura);

  switch (pos) {
    case 2: // Meta o camino al frente (lejano)
      cout << "  -> ACCION: WALK (Radar lejano frente)" << endl;
      return WALK;

    case 1: // Meta o camino a la izquierda (lejano)
      // Alternamos para evitar quedarse bloqueado girando
      if (last_action == TURN_SR) {
        cout << "  -> ACCION: TURN_SR (Alternancia)" << endl;
        return TURN_SR;
      } else {
        cout << "  -> ACCION: TURN_SL" << endl;
        return TURN_SL;
      }

    case 3: // Meta o camino a la derecha (lejano)
      // Alternamos para evitar quedarse bloqueado girando
      if (last_action == TURN_SL) {
        cout << "  -> ACCION: TURN_SL (Alternancia)" << endl;
        return TURN_SL;
      } else {
        cout << "  -> ACCION: TURN_SR" << endl;
        return TURN_SR;
      }

    default: // Nada interesante en el radar
      cout << "  -> ACCION: TURN_SL por default (Radar vacío, explorando...)" << endl;
      return TURN_SL;
  }
}

// =========================================================================
// NIVELES DE COMPORTAMIENTO
// =========================================================================

// Niveles del técnico
Action ComportamientoTecnico::ComportamientoTecnicoNivel_0(Sensores sensores) {
  // Aumentamos el reloj interno
  iteracion_actual++; 
  // Marcamos la casilla actual con el instante de tiempo actual
  mapaVisitas[sensores.posF][sensores.posC] = iteracion_actual;
  Action accion = IDLE;

  ActualizarMapa(sensores);
  
  // Detectamos si hemos encontrado zapatillas
  if(sensores.superficie[0]=='D') tiene_zapatillas = true;
  
  // =========================================================================
  // CASOS ESPECIALES (Prioridad máxima)
  // =========================================================================
  
  // CASO 1: Hemos alcanzado la meta
  if(sensores.superficie[0]=='U'){
    accion=IDLE;
  }
  // CASO 2: Estamos en medio de un giro forzado
  else if(girando>0){
    accion=TURN_SL;
    girando--;
  }
  // =========================================================================
  // CASO PRINCIPAL: Navegación normal
  // =========================================================================
  else {
    cout << "REGLA: Evaluando opciones con Memoria y Vision Ampliada." << endl;

    vector<unsigned char> vision_segura;
    int mem1, mem2, mem3;
    ExtraerDatosDeZonaYMemoria(sensores, vision_segura, mem1, mem2, mem3);

    // 3. EVALUAR OPCIONES ADYACENTES (visión cercana)
    // Resuelve: meta muy cerca + camino menos visitado
    accion = EvaluarOpcionesAdyacentes(vision_segura, mem1, mem2, mem3);

    // 4. Si no hay opciones claras adyacentes, consultar radar ampliado
    if (accion == IDLE) {
      accion = EvaluarRadarAmpliado(vision_segura);
    }
  }
  
  last_action=accion;
  return accion;
}

/**
 * @brief Comprueba si una celda es de tipo camino transitable.
 * @param c Carácter que representa el tipo de superficie.
 * @return true si es camino ('C'), zapatillas ('D') o meta ('U').
 */
bool ComportamientoTecnico::es_camino(unsigned char c) const {
  return (c == 'C' || c == 'D' || c == 'U' || c == 'S');
}


/**
 * @brief Comportamiento reactivo del técnico para el Nivel 1.
 * @param sensores Datos actuales de los sensores.
 * @return Acción a realizar.
 */
Action ComportamientoTecnico::ComportamientoTecnicoNivel_1(Sensores sensores) {
  // Incrementamos el reloj interno
  iteracion_actual++;
  // Marcamos la casilla actual con el instante de tiempo actual
  mapaVisitas[sensores.posF][sensores.posC] = iteracion_actual;
  
  Action accion = IDLE;
  ActualizarMapa(sensores);

  // Detectamos si hemos encontrado zapatillas
  if(sensores.superficie[0]=='D') tiene_zapatillas = true;
  
  // CASO 1: Hay un ingeniero delante.
  if(sensores.agentes[2]=='i'){
    cout << "REGLA: Ingeniero delante, girando" << endl;
    girando = 3;
    accion=TURN_SL;
  } else if(girando > 0){
    accion=TURN_SL;
    girando--;
  }
  // CASO PRINCIPAL: Navegación normal basada en memoria de visitas
  else {
    cout << "REGLA: Navegación reactiva con memoria de visitas." << endl;

    vector<unsigned char> vision_segura;
    int mem1, mem2, mem3;
    ExtraerDatosDeZonaYMemoria(sensores, vision_segura, mem1, mem2, mem3);

    // 3. EVALUAR OPCIONES CON MEMORIA (preferir caminos menos visitados)
    char Left = vision_segura[1];
    char Center = vision_segura[2];
    char Right = vision_segura[3];

    // Hay caminos viables - elegir el menos visitado (sin prioridad de meta)
    bool caminoLeft = es_camino(Left);
    bool caminoCenter = es_camino(Center);
    bool caminoRight = es_camino(Right);

    if (caminoLeft || caminoCenter || caminoRight) {
      int minMemory = 999999;
      int bestOption = 0; // 1=izq, 2=frente, 3=dch

      // Evaluamos de frente primero
      if (caminoCenter) {
        minMemory = mem2;
        bestOption = 2;
      }
      // Evaluamos izquierda
      if (caminoLeft && mem1 < minMemory) {
        minMemory = mem1;
        bestOption = 1;
      }
      // Evaluamos derecha
      if (caminoRight && mem3 < minMemory) {
        minMemory = mem3;
        bestOption = 3;
      }

      // Aplicamos la mejor decisión basada en la memoria
      if (bestOption == 2) {
        cout << "  -> ACCION: WALK (Camino menos visitado, mem=" << minMemory << ")" << endl;
        accion = WALK;
      } else if (bestOption == 1) {
        cout << "  -> ACCION: TURN_SL (Camino menos visitado, mem=" << minMemory << ")" << endl;
        accion = TURN_SL;
      } else if (bestOption == 3) {
        cout << "  -> ACCION: TURN_SR (Camino menos visitado, mem=" << minMemory << ")" << endl;
        accion = TURN_SR;
      }
    } else {
      // No hay opciones, girar para explorar
      cout << "  -> ACCION: TURN_SL (Sin opciones)" << endl;
      accion = TURN_SL;
    }
  }

  last_action = accion;
  return accion;
}

list<Action> AvanzaASaltosDeCaballo(){
  list<Action> secuencia;
  secuencia.push_back(WALK);
  secuencia.push_back(WALK);
  secuencia.push_back(TURN_SR);
  secuencia.push_back(TURN_SR);
  secuencia.push_back(WALK);
  return secuencia;
}

EstadoT NextCasillaTecnico(const EstadoT &st){
    EstadoT siguiente = st;
    switch (st.site.brujula) {
        case norte: siguiente.site.f = st.site.f - 1; break;
        case noreste: siguiente.site.f = st.site.f - 1; siguiente.site.c = st.site.c + 1; break;
        case este: siguiente.site.c = st.site.c + 1; break;
        case sureste: siguiente.site.f = st.site.f + 1; siguiente.site.c = st.site.c + 1; break;
        case sur: siguiente.site.f = st.site.f + 1; break;
        case suroeste: siguiente.site.f = st.site.f + 1; siguiente.site.c = st.site.c - 1; break;
        case oeste: siguiente.site.c = st.site.c - 1; break;
        case noroeste: siguiente.site.f = st.site.f - 1; siguiente.site.c = st.site.c - 1; break;
    }
    return siguiente;
}

bool CasillaAccesibleTecnico (const EstadoT &st, const vector<vector<unsigned char>> &terreno, const vector<vector<unsigned char>> &altura){
    EstadoT next = NextCasillaTecnico(st);
    bool noObstaculo = terreno[next.site.f][next.site.c] != 'P' and terreno[next.site.f][next.site.c] != 'M';
    bool bosqueValido = terreno[next.site.f][next.site.c] != 'B' or (terreno[next.site.f][next.site.c] == 'B' and st.zapatillas);
    bool alturaValida = abs(altura[next.site.f][next.site.c] - altura[st.site.f][st.site.c]) <= 1;
    
    return noObstaculo and bosqueValido and alturaValida;
}

EstadoT applyT(Action accion, const EstadoT & st, const vector<vector<unsigned char>> &terreno, const vector<vector<unsigned char>> &altura){
    EstadoT next = st;
    switch(accion){
        case WALK:
            if (CasillaAccesibleTecnico (st, terreno, altura)){
                next = NextCasillaTecnico(st);
                if (terreno[next.site.f][next.site.c] == 'D') next.zapatillas = true;
            }
            break;
        case TURN_SR:
            next.site.brujula = (Orientacion) ((next.site.brujula+1)%8);
            break;
        case TURN_SL:
            next.site.brujula = (Orientacion) ((next.site.brujula+7)%8);
            break;
    }
    return next;
}

list<Action> B_Anchura(EstadoT inicio, EstadoT fin, const vector<vector<unsigned char>> &terreno, const vector<vector<unsigned char>> &altura) {
    list<NodoT> frontier;
    set<NodoT> explored;
    list<Action> plan;
    bool SolutionFound = (inicio.site.f == fin.site.f and inicio.site.c == fin.site.c);
    
    NodoT current_node;
    current_node.estado = inicio;
    frontier.push_back(current_node);

    while (!frontier.empty() and !SolutionFound) {
        // Extraer el primer nodo de la frontera
        current_node = frontier.front();
        frontier.pop_front();
        
        // Añadir a explorados
        explored.insert(current_node);

        // Generar hijos (solo movimientos posibles para el técnico)
        vector<Action> acciones = {WALK, TURN_SR, TURN_SL};
        
        for (Action acc : acciones) {
            if (SolutionFound) break; // Si ya encontramos solución, paramos de expandir

            EstadoT nuevo_estado = applyT(acc, current_node.estado, terreno, altura);
            
            // Comprobar si es solución (solo tiene sentido al hacer WALK)
            if (acc == WALK and nuevo_estado.site.f == fin.site.f and nuevo_estado.site.c == fin.site.c) {
                plan = current_node.secuencia;
                plan.push_back(acc);
                SolutionFound = true;
            }
            // Si no es solución y no lo hemos explorado, lo añadimos a la frontera
            else if (explored.find(NodoT{nuevo_estado, {}}) == explored.end()) {
                NodoT child;
                child.estado = nuevo_estado;
                child.secuencia = current_node.secuencia;
                child.secuencia.push_back(acc);
                frontier.push_back(child);
            }
        }
    }
    
    return plan;
}

Action ComportamientoTecnico::ComportamientoTecnicoNivel_E(Sensores sensores) {
    Action accion = IDLE;
    if (!hayPlan){
        // Invocar al método de búsqueda
        EstadoT inicio, fin;
        inicio.site.f = sensores.posF;
        inicio.site.c = sensores.posC;
        inicio.site.brujula = sensores.rumbo;
        inicio.zapatillas = tiene_zapatillas;
        
        fin.site.f = sensores.BelPosF;
        fin.site.c = sensores.BelPosC;
        
        plan = B_Anchura(inicio, fin, mapaResultado, mapaCotas);
        VisualizaPlan(inicio.site, plan);
        hayPlan = plan.size() != 0;
    }
    
    if (hayPlan and plan.size()>0){
        accion = plan.front();
        plan.pop_front();
    }
    
    if (plan.size() == 0){
        hayPlan = false;
    }
    
    return accion;
}

/**
 * @brief Comportamiento del técnico para el Nivel 2.
 * @param sensores Datos actuales de los sensores.
 * @return Acción a realizar.
 */
Action ComportamientoTecnico::ComportamientoTecnicoNivel_2(Sensores sensores) {
  // En Nivel 2 el objetivo temporal principal es minimizar instantes del Ingeniero.
  // Mantener al técnico quieto evita bloqueos y colisiones que degradan ese óptimo.
  return IDLE;
}

/**
 * @brief Comportamiento del técnico para el Nivel 3.
 * @param sensores Datos actuales de los sensores.
 * @return Acción a realizar.
 */
Action ComportamientoTecnico::ComportamientoTecnicoNivel_3(Sensores sensores) {
  return IDLE;
}

/**
 * @brief Comportamiento del técnico para el Nivel 4.
 * @param sensores Datos actuales de los sensores.
 * @return Acción a realizar.
 */
Action ComportamientoTecnico::ComportamientoTecnicoNivel_4(Sensores sensores) {
  return IDLE;
}

/**
 * @brief Comportamiento del técnico para el Nivel 5.
 * @param sensores Datos actuales de los sensores.
 * @return Acción a realizar.
 */
Action ComportamientoTecnico::ComportamientoTecnicoNivel_5(Sensores sensores) {
  return IDLE;
}

/**
 * @brief Comportamiento del técnico para el Nivel 6.
 * @param sensores Datos actuales de los sensores.
 * @return Acción a realizar.
 */
Action ComportamientoTecnico::ComportamientoTecnicoNivel_6(Sensores sensores) {
  return IDLE;
}




// =========================================================================
// FUNCIONES PROPORCIONADAS
// =========================================================================

/**
 * @brief Actualiza el mapaResultado y mapaCotas con la información de los sensores.
 * @param sensores Datos actuales de los sensores.
 */
void ComportamientoTecnico::ActualizarMapa(Sensores sensores) {
  mapaResultado[sensores.posF][sensores.posC] = sensores.superficie[0];
  mapaCotas[sensores.posF][sensores.posC] = sensores.cota[0];

  int pos = 1;
  switch (sensores.rumbo) {
    case norte:
      for (int j = 1; j < 4; j++)
        for (int i = -j; i <= j; i++) {
          mapaResultado[sensores.posF - j][sensores.posC + i] = sensores.superficie[pos];
          mapaCotas[sensores.posF - j][sensores.posC + i] = sensores.cota[pos++];
        }
      break;
    case noreste:
      mapaResultado[sensores.posF - 1][sensores.posC] = sensores.superficie[1];
      mapaCotas[sensores.posF - 1][sensores.posC] = sensores.cota[1];
      mapaResultado[sensores.posF - 1][sensores.posC + 1] = sensores.superficie[2];
      mapaCotas[sensores.posF - 1][sensores.posC + 1] = sensores.cota[2];
      mapaResultado[sensores.posF][sensores.posC + 1] = sensores.superficie[3];
      mapaCotas[sensores.posF][sensores.posC + 1] = sensores.cota[3];
      mapaResultado[sensores.posF - 2][sensores.posC] = sensores.superficie[4];
      mapaCotas[sensores.posF - 2][sensores.posC] = sensores.cota[4];
      mapaResultado[sensores.posF - 2][sensores.posC + 1] = sensores.superficie[5];
      mapaCotas[sensores.posF - 2][sensores.posC + 1] = sensores.cota[5];
      mapaResultado[sensores.posF - 2][sensores.posC + 2] = sensores.superficie[6];
      mapaCotas[sensores.posF - 2][sensores.posC + 2] = sensores.cota[6];
      mapaResultado[sensores.posF - 1][sensores.posC + 2] = sensores.superficie[7];
      mapaCotas[sensores.posF - 1][sensores.posC + 2] = sensores.cota[7];
      mapaResultado[sensores.posF][sensores.posC + 2] = sensores.superficie[8];
      mapaCotas[sensores.posF][sensores.posC + 2] = sensores.cota[8];
      mapaResultado[sensores.posF - 3][sensores.posC] = sensores.superficie[9];
      mapaCotas[sensores.posF - 3][sensores.posC] = sensores.cota[9];
      mapaResultado[sensores.posF - 3][sensores.posC + 1] = sensores.superficie[10];
      mapaCotas[sensores.posF - 3][sensores.posC + 1] = sensores.cota[10];
      mapaResultado[sensores.posF - 3][sensores.posC + 2] = sensores.superficie[11];
      mapaCotas[sensores.posF - 3][sensores.posC + 2] = sensores.cota[11];
      mapaResultado[sensores.posF - 3][sensores.posC + 3] = sensores.superficie[12];
      mapaCotas[sensores.posF - 3][sensores.posC + 3] = sensores.cota[12];
      mapaResultado[sensores.posF - 2][sensores.posC + 3] = sensores.superficie[13];
      mapaCotas[sensores.posF - 2][sensores.posC + 3] = sensores.cota[13];
      mapaResultado[sensores.posF - 1][sensores.posC + 3] = sensores.superficie[14];
      mapaCotas[sensores.posF - 1][sensores.posC + 3] = sensores.cota[14];
      mapaResultado[sensores.posF][sensores.posC + 3] = sensores.superficie[15];
      mapaCotas[sensores.posF][sensores.posC + 3] = sensores.cota[15];
      break;
    case este:
      for (int j = 1; j < 4; j++)
        for (int i = -j; i <= j; i++) {
          mapaResultado[sensores.posF + i][sensores.posC + j] = sensores.superficie[pos];
          mapaCotas[sensores.posF + i][sensores.posC + j] = sensores.cota[pos++];
        }
      break;
    case sureste:
      mapaResultado[sensores.posF][sensores.posC + 1] = sensores.superficie[1];
      mapaCotas[sensores.posF][sensores.posC + 1] = sensores.cota[1];
      mapaResultado[sensores.posF + 1][sensores.posC + 1] = sensores.superficie[2];
      mapaCotas[sensores.posF + 1][sensores.posC + 1] = sensores.cota[2];
      mapaResultado[sensores.posF + 1][sensores.posC] = sensores.superficie[3];
      mapaCotas[sensores.posF + 1][sensores.posC] = sensores.cota[3];
      mapaResultado[sensores.posF][sensores.posC + 2] = sensores.superficie[4];
      mapaCotas[sensores.posF][sensores.posC + 2] = sensores.cota[4];
      mapaResultado[sensores.posF + 1][sensores.posC + 2] = sensores.superficie[5];
      mapaCotas[sensores.posF + 1][sensores.posC + 2] = sensores.cota[5];
      mapaResultado[sensores.posF + 2][sensores.posC + 2] = sensores.superficie[6];
      mapaCotas[sensores.posF + 2][sensores.posC + 2] = sensores.cota[6];
      mapaResultado[sensores.posF + 2][sensores.posC + 1] = sensores.superficie[7];
      mapaCotas[sensores.posF + 2][sensores.posC + 1] = sensores.cota[7];
      mapaResultado[sensores.posF + 2][sensores.posC] = sensores.superficie[8];
      mapaCotas[sensores.posF + 2][sensores.posC] = sensores.cota[8];
      mapaResultado[sensores.posF][sensores.posC + 3] = sensores.superficie[9];
      mapaCotas[sensores.posF][sensores.posC + 3] = sensores.cota[9];
      mapaResultado[sensores.posF + 1][sensores.posC + 3] = sensores.superficie[10];
      mapaCotas[sensores.posF + 1][sensores.posC + 3] = sensores.cota[10];
      mapaResultado[sensores.posF + 2][sensores.posC + 3] = sensores.superficie[11];
      mapaCotas[sensores.posF + 2][sensores.posC + 3] = sensores.cota[11];
      mapaResultado[sensores.posF + 3][sensores.posC + 3] = sensores.superficie[12];
      mapaCotas[sensores.posF + 3][sensores.posC + 3] = sensores.cota[12];
      mapaResultado[sensores.posF + 3][sensores.posC + 2] = sensores.superficie[13];
      mapaCotas[sensores.posF + 3][sensores.posC + 2] = sensores.cota[13];
      mapaResultado[sensores.posF + 3][sensores.posC + 1] = sensores.superficie[14];
      mapaCotas[sensores.posF + 3][sensores.posC + 1] = sensores.cota[14];
      mapaResultado[sensores.posF + 3][sensores.posC] = sensores.superficie[15];
      mapaCotas[sensores.posF + 3][sensores.posC] = sensores.cota[15];
      break;
    case sur:
      for (int j = 1; j < 4; j++)
        for (int i = -j; i <= j; i++) {
          mapaResultado[sensores.posF + j][sensores.posC - i] = sensores.superficie[pos];
          mapaCotas[sensores.posF + j][sensores.posC - i] = sensores.cota[pos++];
        }
      break;
    case suroeste:
      mapaResultado[sensores.posF + 1][sensores.posC] = sensores.superficie[1];
      mapaCotas[sensores.posF + 1][sensores.posC] = sensores.cota[1];
      mapaResultado[sensores.posF + 1][sensores.posC - 1] = sensores.superficie[2];
      mapaCotas[sensores.posF + 1][sensores.posC - 1] = sensores.cota[2];
      mapaResultado[sensores.posF][sensores.posC - 1] = sensores.superficie[3];
      mapaCotas[sensores.posF][sensores.posC - 1] = sensores.cota[3];
      mapaResultado[sensores.posF + 2][sensores.posC] = sensores.superficie[4];
      mapaCotas[sensores.posF + 2][sensores.posC] = sensores.cota[4];
      mapaResultado[sensores.posF + 2][sensores.posC - 1] = sensores.superficie[5];
      mapaCotas[sensores.posF + 2][sensores.posC - 1] = sensores.cota[5];
      mapaResultado[sensores.posF + 2][sensores.posC - 2] = sensores.superficie[6];
      mapaCotas[sensores.posF + 2][sensores.posC - 2] = sensores.cota[6];
      mapaResultado[sensores.posF + 1][sensores.posC - 2] = sensores.superficie[7];
      mapaCotas[sensores.posF + 1][sensores.posC - 2] = sensores.cota[7];
      mapaResultado[sensores.posF][sensores.posC - 2] = sensores.superficie[8];
      mapaCotas[sensores.posF][sensores.posC - 2] = sensores.cota[8];
      mapaResultado[sensores.posF + 3][sensores.posC] = sensores.superficie[9];
      mapaCotas[sensores.posF + 3][sensores.posC] = sensores.cota[9];
      mapaResultado[sensores.posF + 3][sensores.posC - 1] = sensores.superficie[10];
      mapaCotas[sensores.posF + 3][sensores.posC - 1] = sensores.cota[10];
      mapaResultado[sensores.posF + 3][sensores.posC - 2] = sensores.superficie[11];
      mapaCotas[sensores.posF + 3][sensores.posC - 2] = sensores.cota[11];
      mapaResultado[sensores.posF + 3][sensores.posC - 3] = sensores.superficie[12];
      mapaCotas[sensores.posF + 3][sensores.posC - 3] = sensores.cota[12];
      mapaResultado[sensores.posF + 2][sensores.posC - 3] = sensores.superficie[13];
      mapaCotas[sensores.posF + 2][sensores.posC - 3] = sensores.cota[13];
      mapaResultado[sensores.posF + 1][sensores.posC - 3] = sensores.superficie[14];
      mapaCotas[sensores.posF + 1][sensores.posC - 3] = sensores.cota[14];
      mapaResultado[sensores.posF][sensores.posC - 3] = sensores.superficie[15];
      mapaCotas[sensores.posF][sensores.posC - 3] = sensores.cota[15];
      break;
    case oeste:
      for (int j = 1; j < 4; j++)
        for (int i = -j; i <= j; i++) {
          mapaResultado[sensores.posF - i][sensores.posC - j] = sensores.superficie[pos];
          mapaCotas[sensores.posF - i][sensores.posC - j] = sensores.cota[pos++];
        }
      break;
    case noroeste:
      mapaResultado[sensores.posF][sensores.posC - 1] = sensores.superficie[1];
      mapaCotas[sensores.posF][sensores.posC - 1] = sensores.cota[1];
      mapaResultado[sensores.posF - 1][sensores.posC - 1] = sensores.superficie[2];
      mapaCotas[sensores.posF - 1][sensores.posC - 1] = sensores.cota[2];
      mapaResultado[sensores.posF - 1][sensores.posC] = sensores.superficie[3];
      mapaCotas[sensores.posF - 1][sensores.posC] = sensores.cota[3];
      mapaResultado[sensores.posF][sensores.posC - 2] = sensores.superficie[4];
      mapaCotas[sensores.posF][sensores.posC - 2] = sensores.cota[4];
      mapaResultado[sensores.posF - 1][sensores.posC - 2] = sensores.superficie[5];
      mapaCotas[sensores.posF - 1][sensores.posC - 2] = sensores.cota[5];
      mapaResultado[sensores.posF - 2][sensores.posC - 2] = sensores.superficie[6];
      mapaCotas[sensores.posF - 2][sensores.posC - 2] = sensores.cota[6];
      mapaResultado[sensores.posF - 2][sensores.posC - 1] = sensores.superficie[7];
      mapaCotas[sensores.posF - 2][sensores.posC - 1] = sensores.cota[7];
      mapaResultado[sensores.posF - 2][sensores.posC] = sensores.superficie[8];
      mapaCotas[sensores.posF - 2][sensores.posC] = sensores.cota[8];
      mapaResultado[sensores.posF][sensores.posC - 3] = sensores.superficie[9];
      mapaCotas[sensores.posF][sensores.posC - 3] = sensores.cota[9];
      mapaResultado[sensores.posF - 1][sensores.posC - 3] = sensores.superficie[10];
      mapaCotas[sensores.posF - 1][sensores.posC - 3] = sensores.cota[10];
      mapaResultado[sensores.posF - 2][sensores.posC - 3] = sensores.superficie[11];
      mapaCotas[sensores.posF - 2][sensores.posC - 3] = sensores.cota[11];
      mapaResultado[sensores.posF - 3][sensores.posC - 3] = sensores.superficie[12];
      mapaCotas[sensores.posF - 3][sensores.posC - 3] = sensores.cota[12];
      mapaResultado[sensores.posF - 3][sensores.posC - 2] = sensores.superficie[13];
      mapaCotas[sensores.posF - 3][sensores.posC - 2] = sensores.cota[13];
      mapaResultado[sensores.posF - 3][sensores.posC - 1] = sensores.superficie[14];
      mapaCotas[sensores.posF - 3][sensores.posC - 1] = sensores.cota[14];
      mapaResultado[sensores.posF - 3][sensores.posC] = sensores.superficie[15];
      mapaCotas[sensores.posF - 3][sensores.posC] = sensores.cota[15];
      break;
  }
}



/**
 * @brief Determina si una casilla es transitable para el técnico.
 * En esta práctica, si el técnico tiene zapatillas, el bosque ('B') es transitable.
 * @param f Fila de la casilla.
 * @param c Columna de la casilla.
 * @param tieneZapatillas Indica si el agente posee las zapatillas.
 * @return true si la casilla es transitable.
 */
bool ComportamientoTecnico::EsCasillaTransitableLevel0(int f, int c, bool tieneZapatillas) {
  if (f < 0 || f >= mapaResultado.size() || c < 0 || c >= mapaResultado[0].size()) return false;
  unsigned char terreno = mapaResultado[f][c];
  // Caminos normales: 'C', 'S', 'D', 'U'
  if (es_camino(terreno)) return true;
  // Bosque es transitable solo si tiene zapatillas
  if (terreno == 'B' && tieneZapatillas) return true;
  return false;
}

/**
 * @brief Comprueba si la casilla de delante es accesible por diferencia de altura.
 * Para el técnico: desnivel máximo siempre 1.
 * @param actual Estado actual del agente (fila, columna, orientacion).
 * @return true si el desnivel con la casilla de delante es admisible.
 */
bool ComportamientoTecnico::EsAccesiblePorAltura(const ubicacion &actual) {
  ubicacion del = Delante(actual);
  if (del.f < 0 || del.f >= mapaCotas.size() || del.c < 0 || del.c >= mapaCotas[0].size()) return false;
  int desnivel = abs(mapaCotas[del.f][del.c] - mapaCotas[actual.f][actual.c]);
  if (desnivel > 1) return false;
  return true;
}

/**
 * @brief Devuelve la posición (fila, columna) de la casilla que hay delante del agente.
 * Calcula la casilla frontal según la orientación actual (8 direcciones).
 * @param actual Estado actual del agente (fila, columna, orientacion).
 * @return Estado con la fila y columna de la casilla de enfrente.
 */
ubicacion ComportamientoTecnico::Delante(const ubicacion &actual) const {
  ubicacion delante = actual;
  switch (actual.brujula) {
    case 0: delante.f--; break;                        // norte
    case 1: delante.f--; delante.c++; break;     // noreste
    case 2: delante.c++; break;                     // este
    case 3: delante.f++; delante.c++; break;     // sureste
    case 4: delante.f++; break;                        // sur
    case 5: delante.f++; delante.c--; break;     // suroeste
    case 6: delante.c--; break;                     // oeste
    case 7: delante.f--; delante.c--; break;     // noroeste
  }
  return delante;
}


/**
 * @brief Imprime por consola la secuencia de acciones de un plan.
 *
 * @param plan  Lista de acciones del plan.
 */
void ComportamientoTecnico::PintaPlan(const list<Action> &plan)
{
  auto it = plan.begin();
  while (it != plan.end())
  {
    if (*it == WALK)
    {
      cout << "W ";
    }
    else if (*it == JUMP)
    {
      cout << "J ";
    }
    else if (*it == TURN_SR)
    {
      cout << "r ";
    }
    else if (*it == TURN_SL)
    {
      cout << "l ";
    }
    else if (*it == COME)
    {
      cout << "C ";
    }
    else if (*it == IDLE)
    {
      cout << "I ";
    }
    else
    {
      cout << "-_ ";
    }
    it++;
  }
  cout << "( longitud " << plan.size() << ")" << endl;
}



/**
 * @brief Convierte un plan de acciones en una lista de casillas para
 *        su visualización en el mapa 2D.
 *
 * @param st    Estado de partida.
 * @param plan  Lista de acciones del plan.
 */
void ComportamientoTecnico::VisualizaPlan(const ubicacion &st,
                                            const list<Action> &plan)
{
   listaPlanCasillas.clear();
  ubicacion cst = st;

  listaPlanCasillas.push_back({cst.f, cst.c, WALK});
  auto it = plan.begin();
  while (it != plan.end())
  {

    switch (*it)
    {
    case JUMP:
      switch (cst.brujula)
      {
      case 0:
        cst.f--;
        break;
      case 1:
        cst.f--;
        cst.c++;
        break;
      case 2:
        cst.c++;
        break;
      case 3:
        cst.f++;
        cst.c++;
        break;
      case 4:
        cst.f++;
        break;
      case 5:
        cst.f++;
        cst.c--;
        break;
      case 6:
        cst.c--;
        break;
      case 7:
        cst.f--;
        cst.c--;
        break;
      }
      if (cst.f >= 0 && cst.f < mapaResultado.size() &&
          cst.c >= 0 && cst.c < mapaResultado[0].size())
        listaPlanCasillas.push_back({cst.f, cst.c, JUMP});
      break;
    case WALK:
      switch (cst.brujula)
      {
      case 0:
        cst.f--;
        break;
      case 1:
        cst.f--;
        cst.c++;
        break;
      case 2:
        cst.c++;
        break;
      case 3:
        cst.f++;
        cst.c++;
        break;
      case 4:
        cst.f++;
        break;
      case 5:
        cst.f++;
        cst.c--;
        break;
      case 6:
        cst.c--;
        break;
      case 7:
        cst.f--;
        cst.c--;
        break;
      }
      if (cst.f >= 0 && cst.f < mapaResultado.size() &&
          cst.c >= 0 && cst.c < mapaResultado[0].size())
        listaPlanCasillas.push_back({cst.f, cst.c, WALK});
      break;
    case TURN_SR:
      cst.brujula = (Orientacion) (( (int) cst.brujula + 1) % 8);
      break;
    case TURN_SL:
      cst.brujula = (Orientacion) (( (int) cst.brujula + 7) % 8);
      break;
    }
    it++;
  }
}


