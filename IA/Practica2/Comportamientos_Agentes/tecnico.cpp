#include "tecnico.hpp"
#include "motorlib/util.h"
#include <iostream>
#include <queue>
#include <set>
#include <map>

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
/**
 * @brief Comportamiento reactivo del técnico para el Nivel 0.
 *
 * Flujo general:
 * 1. Guarda visita y actualiza el mapa visible.
 * 2. Mantiene la prioridad de parada si ya está en meta o girando.
 * 3. Decide con visión local y memoria de visitas.
 * 4. Si no hay opción clara, gira para seguir explorando.
 *
 * @param sensores Datos actuales de los sensores.
 * @return Acción a realizar.
 */
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
 * @brief Comprueba si una celda se considera navegable para la exploración reactiva.
 *
 * A efectos del nivel 1, se aceptan caminos, senderos, zapatillas y meta.
 * @param c Carácter que representa el tipo de superficie.
 * @return true si la celda puede usarse como paso seguro.
 */
bool ComportamientoTecnico::es_camino(unsigned char c) const {
  return (c == 'C' || c == 'D' || c == 'U' || c == 'S');
}


/**
 * @brief Comportamiento reactivo del técnico para el Nivel 1 (Exploración).
 *
 * Flujo general:
 * 1. Guarda visita y actualiza mapa visible.
 * 2. Resuelve interacción con el Ingeniero (si está delante).
 * 3. Continúa giros forzados si está girando.
 * 4. Elige casilla menos visitada (exploración pura, sin prioridad a meta).
 * 5. Si no hay opción clara, gira para seguir explorando.
 *
 * DIFERENCIA CON INGENIERO: El Técnico gira SIEMPRE que ve al Ingeniero (no verifica last_action)
 * y usa 3 pasos de giro a la izquierda para apartarse más.
 *
 * @param sensores Datos actuales de los sensores.
 * @return Acción a realizar.
 */
Action ComportamientoTecnico::ComportamientoTecnicoNivel_1(Sensores sensores) {
  // 1. Registro de visita temporal
  iteracion_actual++;
  mapaVisitas[sensores.posF][sensores.posC] = iteracion_actual;
  
  Action accion = IDLE;
  ActualizarMapa(sensores);

  // Detectamos si hemos encontrado zapatillas
  if(sensores.superficie[0]=='D') tiene_zapatillas = true;
  
  // CASO 1: Interacción con el Ingeniero (Estrategia: Apartarse activamente)
  // El Técnico SIEMPRE se aparta girando a la IZQUIERDA cuando el Ingeniero está delante.
  // Diferencia con Ingeniero:
  // - Técnico: gira 3 pasos * 45° = 135° (más alejado)
  // - Ingeniero: gira 2 pasos * 45° = 90° (con prioridad)
  // Girando en DIRECCIONES OPUESTAS (derecha vs izquierda) reduce probabilidad de colisión.
  if(sensores.agentes[2]=='i'){
    girando = 3;  // 3 pasos * 45° = 135° de giro a la izquierda
    accion=TURN_SL;
  }
  // CASO 2: Continuar giro forzado en curso
  else if(girando > 0){
    accion=TURN_SL;
    girando--;
  }
  // CASO PRINCIPAL: Exploración normal con memoria de visitas
  else {
    cout << "REGLA: Navegación reactiva con memoria de visitas." << endl;

    vector<unsigned char> vision_segura;
    int mem1, mem2, mem3;
    ExtraerDatosDeZonaYMemoria(sensores, vision_segura, mem1, mem2, mem3);

    // Extrae las 3 opciones adyacentes (izq, frente, dch)
    char Left = vision_segura[1];
    char Center = vision_segura[2];
    char Right = vision_segura[3];

    // Detecta qué casillas son transitables
    bool caminoLeft = es_camino(Left);
    bool caminoCenter = es_camino(Center);
    bool caminoRight = es_camino(Right);

    // Si hay al menos una opción viable, elige la menos visitada
    if (caminoLeft || caminoCenter || caminoRight) {
      int minMemory = 999999;
      int bestOption = 0; // 1=izq, 2=frente, 3=dch

      // ALGORITMO: Selecciona el camino MENOS VISITADO, con preferencia SUAVE por avanzar recto.
      // Paso 1: Si hay camino recto, úsalo como "punto de referencia" inicial.
      // Esto minimiza giros (avanzar recto es más eficiente que girar)
      if (caminoCenter) {
        minMemory = mem2;       // Punto de referencia: mem2 es "visitado Center veces"
        bestOption = 2;
      }
      
      // Paso 2: Comparar izquierda con el punto de referencia.
      // Si izquierda está MENOS VISITADA, sobrescribe la referencia.
      if (caminoLeft && mem1 < minMemory) {
        minMemory = mem1;       // Nueva referencia: mem1 es menor que mem2
        bestOption = 1;
      }
      
      // Paso 3: Comparar derecha con el mejor encontrado hasta ahora.
      // Si derecha está MENOS VISITADA, sobrescribe.
      if (caminoRight && mem3 < minMemory) {
        minMemory = mem3;       // Mejor encontrada: mem3 es el mínimo
        bestOption = 3;
      }
      // RESULTADO: bestOption es el camino CON MENOR número de visitas.

      // Ejecuta la mejor opción
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
      // Bloqueado: girar a la izquierda para buscar salida
      cout << "  -> ACCION: TURN_SL (Sin opciones, explorando)" << endl;
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
    // Evita accesos fuera de rango al evaluar movimientos en bordes del mapa.
    if (next.site.f < 0 || next.site.f >= (int)terreno.size() ||
        next.site.c < 0 || next.site.c >= (int)terreno[0].size()) {
      return false;
    }

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
    set<EstadoT> explored;
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
        explored.insert(current_node.estado);

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
            else if (explored.find(nuevo_estado) == explored.end()) {
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

int Heuristica(const EstadoT &actual, const EstadoT &meta) {
  // Movimiento en 8 direcciones: cota inferior admisible = distancia de Chebyshev.
  return max(abs(actual.site.f - meta.site.f), abs(actual.site.c - meta.site.c));
}

int CalcularCosteEnergia(Action accion, char terreno_inicio, int altura_inicio, int altura_destino) {
  int coste_base = 1;
  if (accion == WALK) {
    int mod_altura = 0;
    bool aplica_mod_altura = false;
    switch (terreno_inicio) {
      case 'A': coste_base = 60; aplica_mod_altura = true; break;
      case 'H': coste_base = 6;  aplica_mod_altura = true; break;
      case 'S': coste_base = 3;  aplica_mod_altura = true; break;
    }

    if (aplica_mod_altura) {
      int dif = altura_destino - altura_inicio;
      if (dif > 0) mod_altura = 5;
      else if (dif < 0) mod_altura = -2;

      coste_base += mod_altura;
    }
  }else if (accion == TURN_SL || accion == TURN_SR) {
    switch (terreno_inicio) {
      case 'A': coste_base= 5; break;
      case 'H': coste_base= 2; break;
      case 'S': coste_base= 1; break;
    }
  }
    
  return coste_base;
}

list<Action> A_Star_Tecnico(EstadoT inicio, EstadoT fin, const vector<vector<unsigned char>> &terreno, const vector<vector<unsigned char>> &altura) {
  priority_queue<NodoT> frontier; 
  map<EstadoT, int> best_g_cost;
  list<Action> plan;
    
  bool SolutionFound = false;

  NodoT start_node;
  start_node.estado = inicio;
  start_node.g_cost = 0;
  start_node.f_cost = Heuristica(inicio, fin);
  frontier.push(start_node);

  best_g_cost[inicio] = 0; // Coste de llegar al inicio es 0

  while (!frontier.empty() and !SolutionFound) {
    NodoT current_node = frontier.top();
    frontier.pop();      
    EstadoT estado_actual = current_node.estado;

    //Comprobamos si hemos llegado a la meta
    if (estado_actual.site.f == fin.site.f && estado_actual.site.c == fin.site.c) {
      plan = current_node.secuencia;
      SolutionFound = true;
      break;
    }

    // Si ya lo exploramos con un coste menor, lo saltamos
    if (current_node.g_cost > best_g_cost[estado_actual]) {
      continue; 
    }

    // Generar hijos
    vector<Action> acciones = {WALK, TURN_SR, TURN_SL};
        
    for (Action acc : acciones) {
      EstadoT nuevo_estado = applyT(acc, estado_actual, terreno, altura);
            
      // Verificamos que la acción haya tenido efecto
      if (!(nuevo_estado == estado_actual) || acc == TURN_SR || acc == TURN_SL) {
                
        int coste_paso = 0;
        char terr_inicio = terreno[estado_actual.site.f][estado_actual.site.c];

        if (acc == WALK) {
          int alt_inicio = altura[estado_actual.site.f][estado_actual.site.c];
          int alt_destino = altura[nuevo_estado.site.f][nuevo_estado.site.c];
          coste_paso = CalcularCosteEnergia(acc, terr_inicio, alt_inicio, alt_destino);
        } else {
          coste_paso = CalcularCosteEnergia(acc, terr_inicio, 0, 0);
        }

        int nuevo_g = current_node.g_cost + coste_paso;
        // SOLO añadimos el hijo si nunca hemos estado ahí, o si hemos encontrado un camino MÁS BARATO
        if (best_g_cost.find(nuevo_estado) == best_g_cost.end() || nuevo_g < best_g_cost[nuevo_estado]) {
                  
          best_g_cost[nuevo_estado] = nuevo_g; // Actualizamos el récord
          int nuevo_f = nuevo_g + Heuristica(nuevo_estado, fin);

          NodoT child;
          child.estado = nuevo_estado;
          child.secuencia = current_node.secuencia; 
          child.secuencia.push_back(acc);
          child.g_cost = nuevo_g;
          child.f_cost = nuevo_f;
                    
          frontier.push(child);
        }
      }
    }
  }
  return plan;
}

/**
 * @brief Buscar nueva niebla para el Técnico sin acotar el mapa.
 * Selecciona la '?' más cercana al técnico y traza un plan con A* hacia ella.
 * Si la celda es inaccesible, se marca en una lista local para evitar reintentos inmediatos.
 */
bool ComportamientoTecnico::BuscarNuevaNieblaSimple(const Sensores &sensores) {
  static set<pair<int,int>> niebla_inaccesible_tec;
  int target_f = -1, target_c = -1;
  int min_dist = 999999;
  // Buscamos iterativamente la '?' más cercana que no esté marcada como inaccesible
  for (int i = 0; i < (int)mapaResultado.size(); ++i) {
    for (int j = 0; j < (int)mapaResultado[0].size(); ++j) {
      if (mapaResultado[i][j] == '?' && niebla_inaccesible_tec.find({i,j}) == niebla_inaccesible_tec.end()) {
        int dist_a_mi = abs(i - sensores.posF) + abs(j - sensores.posC);
        if (dist_a_mi < min_dist) {
          min_dist = dist_a_mi;
          target_f = i; target_c = j;
        }
      }
    }
  }

  while (target_f != -1) {
    EstadoT start, goal;
    start.site.f = sensores.posF; start.site.c = sensores.posC; start.site.brujula = sensores.rumbo; start.zapatillas = tiene_zapatillas;
    goal.site.f = target_f; goal.site.c = target_c;

    // Intentamos trazar plan con A*
    list<Action> nuevo_plan = A_Star_Tecnico(start, goal, mapaResultado, mapaCotas);
    if (!nuevo_plan.empty()) {
      // Establecemos target y plan para que la fase 1 lo ejecute
      targetF = target_f; targetC = target_c;
      plan = nuevo_plan;
      hayPlan = !plan.empty();
      VisualizaPlan(start.site, plan);
      return true;
    }

    // Si no se pudo trazar plan, marcamos esta niebla como inaccesible y buscamos la siguiente
    niebla_inaccesible_tec.insert({target_f, target_c});

    // Buscar siguiente '?' más cercana no marcada
    target_f = -1; target_c = -1; min_dist = 999999;
    for (int i = 0; i < (int)mapaResultado.size(); ++i) {
      for (int j = 0; j < (int)mapaResultado[0].size(); ++j) {
        if (mapaResultado[i][j] == '?' && niebla_inaccesible_tec.find({i,j}) == niebla_inaccesible_tec.end()) {
          int dist_a_mi = abs(i - sensores.posF) + abs(j - sensores.posC);
          if (dist_a_mi < min_dist) {
            min_dist = dist_a_mi;
            target_f = i; target_c = j;
          }
        }
      }
    }
  }

  return false; // No se encontró niebla accesible
}


/**
 * @brief Comportamiento del técnico para el Nivel 3.
 * @param sensores Datos actuales de los sensores.
 * @return Acción a realizar.
 */
/**
 * ============================================================================
 * NIVEL 3: PLANIFICACIÓN ENERGÉTICA Y EVASIÓN (TÉCNICO)
 * ============================================================================
 *
 * Descripción general:
 * - En Nivel 3 el Técnico despliega planificación con A* para llegar a la meta
 *   minimizando coste energético (función CalcularCosteEnergia).
 * - Se sincroniza el mapa con sensores y se evita activamente situarse delante
 *   del Ingeniero para prevenir bloqueos (si el Ingeniero está delante, el
 *   Técnico espera en IDLE para evitar colisiones).
 *
 * Flujo resumido:
 * 1) Actualizar mapa y estado (zapatillas).
 * 2) Si no hay plan, construir estados inicio/meta y crear `mapaPlan`.
 * 3) Si Ingeniero está justo delante, evitar planificar (retornar IDLE).
 * 4) Ejecutar `A_Star_Tecnico` sobre `mapaPlan` para obtener `plan`.
 * 5) Ejecutar acciones del `plan` con salvaguardas anti-choque (evitar WALK
 *    cuando Ingeniero aparece delante).
 *
 * Notas de diseño:
 * - `A_Star_Tecnico` usa heurística de Chebyshev y `CalcularCosteEnergia` para
 *   ordenar la frontera (priority_queue) y guardar `best_g_cost`.
 * - El Técnico no cambia el mapa real aquí; `mapaPlan` puede marcar casillas
 *   temporales como inaccesibles para evitar la celda frontal del Ingeniero.
 * - Se documenta la estrategia sin modificar la lógica funcional.
 *
 * @param sensores Datos actuales de los sensores.
 * @return Acción a realizar.
 */
Action ComportamientoTecnico::ComportamientoTecnicoNivel_3(Sensores sensores) {
  Action accion = IDLE;

  // 1) Mantener estado interno sincronizado en cada tick.
  ActualizarMapa(sensores);
  if (sensores.superficie[0] == 'D') {
    tiene_zapatillas = true;
  }

  // 2) Si hay Ingeniero delante, invalidamos plan para forzar replanificación.
  bool ingeniero_delante = (sensores.agentes[2] == 'i');
  /*if (sensores.choque || sensores.reset) {
    plan.clear();
    hayPlan = false;
  }*/

  // 3) Planificar cuando no haya plan activo.
  // Si el Ingeniero está justo delante, esa casilla se bloquea temporalmente
  // en el mapa usado por A* para evitar choques.
  if (!hayPlan) {
    EstadoT inicio, fin;
    inicio.site.f = sensores.posF;
    inicio.site.c = sensores.posC;
    inicio.site.brujula = sensores.rumbo;
    inicio.zapatillas = tiene_zapatillas;

    fin.site.f = sensores.BelPosF;
    fin.site.c = sensores.BelPosC;

    vector<vector<unsigned char>> mapaPlan = mapaResultado;
    if (ingeniero_delante) {
      return IDLE;
        /*ubicacion actual;
        actual.f = sensores.posF;
        actual.c = sensores.posC;
        actual.brujula = (Orientacion)sensores.rumbo;
        ubicacion frente = Delante(actual);

        if (frente.f >= 0 && frente.f < mapaPlan.size() &&
            frente.c >= 0 && frente.c < mapaPlan[0].size()) {
          mapaPlan[frente.f][frente.c] = 'P';
        }*/
    }

    plan = A_Star_Tecnico(inicio, fin, mapaPlan, mapaCotas);
    VisualizaPlan(inicio.site, plan);
    hayPlan = (plan.size() > 0);
  }

  // 4) Ejecutar acción del plan (si existe), manteniendo salvaguarda anti-choque.
  if (hayPlan && plan.size() > 0) {
    accion = plan.front();

    // Red de seguridad: si aparece un Ingeniero delante al avanzar, no chocamos.
    if (accion == WALK && (sensores.agentes[2] == 'i')) {
      /*plan.clear();
      hayPlan = false;*/
      accion = IDLE;
    } else {
      plan.pop_front();
    }
  }

  // 5) Si se agota el plan, forzar planificación en el próximo ciclo.
  if (plan.size() == 0) hayPlan = false;

  return accion;
}

/**
 * @brief Comportamiento del técnico para el Nivel 4.
 * @param sensores Datos actuales de los sensores.
 * @return Acción a realizar.
 */
Action ComportamientoTecnico::ComportamientoTecnicoNivel_4(Sensores sensores) {
  // Técnico en espera durante planificación de la red de tuberías.
  return IDLE;
}

/**
 * @brief Comportamiento del técnico para el Nivel 5.
 * @param sensores Datos actuales de los sensores.
 * @return Acción a realizar.
 */
/**
 * @brief Comportamiento del técnico para el Nivel 5 - INSTALACIÓN DE RED DE TUBERÍAS.
 * 
 * ═══════════════════════════════════════════════════════════════════════════════
 * ALGORITMO COORDINADO INGENIERO-TÉCNICO:
 * ═══════════════════════════════════════════════════════════════════════════════
 * 
 * El Técnico recibe órdenes del Ingeniero (COME) para navegar y coordinar la 
 * instalación de tuberías:
 * 
 * 1. ESCUCHAR SEÑALES:
 *    - venpaca: Recibe orden del Ingeniero (COME) con nueva posición objetivo.
 *    - enfrente: Si el Ingeniero está en la casilla frontal, ejecutar INSTALL.
 * 
 * 2. NAVEGAR HACIA OBJETIVO:
 *    - Si targetF/targetC están definidas, planificar ruta hacia allá.
 *    - Usar A* para rutas largas (dist > 1).
 *    - Usar control reactivo para rutas cortas (dist == 1).
 *    - Si el Ingeniero bloquea, evitar su posición en siguiente planificación.
 * 
 * 3. ENCARARSE CON INGENIERO:
 *    - Una vez en el objetivo, girar para ver al Ingeniero.
 *    - Detectar Ingeniero a izq (agentes[1]), frente (agentes[2]), o dcha (agentes[3]).
 *    - Girar hasta verlo, luego esperar.
 * 
 * 4. SINCRONIZAR INSTALACIÓN:
 *    - Cuando el Ingeniero está enfrente (enfrente=true), ejecutar INSTALL.
 *    - Esperar nueva orden COME del Ingeniero para siguiente tramo.
 * 
 * ═══════════════════════════════════════════════════════════════════════════════
 * NOTAS IMPORTANTES:
 * ═══════════════════════════════════════════════════════════════════════════════
 * - El Técnico es completamente pasivo: solo actúa siguiendo órdenes del Ingeniero.
 * - No tiene un sistema de "fases" como el Ingeniero; todo es reactivo.
 * - Si hay choque o reset, olvida el plan y replanifico.
 * - Mantiene variable bloqueoF/bloqueoC para evitar pasar por donde está el Ingeniero.
 * 
 * @param sensores Datos actuales de los sensores.
 * @return Acción a realizar en este tick.
 */
Action ComportamientoTecnico::ComportamientoTecnicoNivel_5(Sensores sensores) {
  Action accion = IDLE;
  ActualizarMapa(sensores);

  // ─────────────────────────────────────────────────────────────────────────
  // INICIALIZACIÓN: Detectar zapatillas y reseteos
  // ─────────────────────────────────────────────────────────────────────────
  if (sensores.superficie[0] == 'D') tiene_zapatillas = true;

  // Si hay colisión o reset, descarta el plan de movimiento y replanifico
  if (sensores.choque || sensores.reset) {
    hayPlan = false;
    plan.clear();
  }

  // ─────────────────────────────────────────────────────────────────────────
  // ESCUCHAR ORDEN DEL INGENIERO (COME): Actualizar objetivo de navegación
  // ─────────────────────────────────────────────────────────────────────────
  if (sensores.venpaca) {
    targetF = sensores.GotoF;
    targetC = sensores.GotoC;
    hayPlan = false;
    plan.clear();
  }

  // ─────────────────────────────────────────────────────────────────────────
  // PRIORIDAD MÁXIMA: Si el Ingeniero está enfrente, ¡INSTALAR!
  // ─────────────────────────────────────────────────────────────────────────
  if (sensores.enfrente) {
    hayPlan = false;
    plan.clear();
    return INSTALL;
  }

  // ─────────────────────────────────────────────────────────────────────────
  // NAVEGAR HACIA EL OBJETIVO (Solo si tenemos objetivo válido)
  // ─────────────────────────────────────────────────────────────────────────
  if (targetF != -1 && targetC != -1) {
    
    // ─────────────────────────────────────────────────────────────────────────
    // SUBCASO 1: Ya hemos alcanzado el objetivo
    // ─────────────────────────────────────────────────────────────────────────
    if (sensores.posF == targetF && sensores.posC == targetC) {
      // Si el Ingeniero está justo enfrente, esperar
      if (sensores.agentes[2] == 'i') return IDLE;

      // Si está a izquierda (posición 1) o derecha (posición 3), girarse
      if (sensores.agentes[1] == 'i') return TURN_SL;
      if (sensores.agentes[3] == 'i') return TURN_SR;

      // Si no lo vemos en visión cercana, seguir girando (busca activa)
      return TURN_SR;
    }

    // Calcular distancia Manhattan hacia el objetivo
    int dist = abs(targetF - sensores.posF) + abs(targetC - sensores.posC);

    // ─────────────────────────────────────────────────────────────────────────
    // SUBCASO 2: Objetivo lejano (dist > 1) → Usar A* para planificación
    // ─────────────────────────────────────────────────────────────────────────
    if (dist > 1) {
      // Planificar si aún no lo hemos hecho
      if (!hayPlan) {
        EstadoT start, goal;
        start.site.f = sensores.posF;
        start.site.c = sensores.posC;
        start.site.brujula = sensores.rumbo;
        start.zapatillas = tiene_zapatillas;
        goal.site.f = targetF;
        goal.site.c = targetC;

        // Crear copia del mapa para marcar posición del Ingeniero como intransitable
        vector<vector<unsigned char>> mapaPlan = mapaResultado;
        if (bloqueoF != -1 && bloqueoC != -1) {
          if (bloqueoF >= 0 && bloqueoF < mapaPlan.size() &&
              bloqueoC >= 0 && bloqueoC < mapaPlan[0].size()) {
            mapaPlan[bloqueoF][bloqueoC] = 'P';  // Marcar Ingeniero como pared
          }
          bloqueoF = -1; 
          bloqueoC = -1;  // Reset para futuras planificaciones
        }

        plan = A_Star_Tecnico(start, goal, mapaPlan, mapaCotas);
        VisualizaPlan(start.site, plan);
        hayPlan = !plan.empty();
      }

      // Ejecutar el plan de movimiento (con evitación si es necesario)
      if (hayPlan && !plan.empty()) {
        // Si el Ingeniero bloquea el paso, marcar su posición y replanificar
        if (plan.front() == WALK && (sensores.agentes[2] == 'i' || sensores.superficie[2] == 'P')) {
          EstadoT st_actual;
          st_actual.site.f = sensores.posF;
          st_actual.site.c = sensores.posC;
          st_actual.site.brujula = (Orientacion)sensores.rumbo;
          st_actual.zapatillas = tiene_zapatillas;
          
          EstadoT st_frontal = NextCasillaTecnico(st_actual);
          bloqueoF = st_frontal.site.f;
          bloqueoC = st_frontal.site.c;
          hayPlan = false;
          plan.clear();
          // No retornar; dejar que se replanifique abajo
        } else {
          // Ejecutar acción siguiente del plan
          Action a = plan.front();
          plan.pop_front();
          if (plan.empty()) hayPlan = false;
          return a;
        }
      }
    }
    
    // ─────────────────────────────────────────────────────────────────────────
    // SUBCASO 3: Objetivo cercano (dist == 1) → Control reactivo directo
    // ─────────────────────────────────────────────────────────────────────────
    else {
      if (hayPlan) { hayPlan = false; plan.clear(); }

      // Calcular orientación ideal hacia el objetivo
      int dF = targetF - sensores.posF;
      int dC = targetC - sensores.posC;
      Orientacion ideal;

      if (dF < 0 && dC == 0) ideal = norte;
      else if (dF == 0 && dC > 0) ideal = este;
      else if (dF > 0 && dC == 0) ideal = sur;
      else if (dF == 0 && dC < 0) ideal = oeste;
      else ideal = (Orientacion)sensores.rumbo;

      // Si no miramos la dirección, girar
      if (sensores.rumbo != ideal) {
        int diff = (ideal - sensores.rumbo + 8) % 8;
        if (diff <= 4) return TURN_SR;
        else return TURN_SL;
      }
      
      // Ya miramos la dirección → verificar si podemos avanzar
      if (sensores.agentes[2] == 'i') {
        return IDLE;  // El Ingeniero está en el camino, esperar
      }
      return WALK;  // Vía libre, avanzar
    }
  }

  return IDLE;
}

/**
 * @brief Comportamiento del técnico para el Nivel 6.
 * @param sensores Datos actuales de los sensores.
 * @return Acción a realizar.
 */
Action ComportamientoTecnico::ComportamientoTecnicoNivel_6(Sensores sensores) {
  // 1. Actualización básica de estado en el Nivel 6
  ActualizarMapa(sensores);
  if (sensores.superficie[0] == 'D') tiene_zapatillas = true;

  // =====================================================================
  // FASE 0: EXPLORADOR ACTIVO
  // =====================================================================
  if (faseNivel6 == 0) {
      // El Técnico ahora se dirige directamente al Bel (coordenadas BelPosF/BelPosC)
      // en lugar de explorar. Si recibe COME, también pasa a construcción.
      if (sensores.venpaca) {
        cout << "Tec: ¡El jefe me llama! Aborto exploración, paso a construcción." << endl;
        faseNivel6 = 1;
        // Dejamos que el código baje al Nivel 5 para procesar el COME
      } else {
          return ComportamientoTecnicoNivel_1(sensores);
      }
  }

  // =====================================================================
  // FASE 1: ASISTENTE DE CONSTRUCCIÓN
  // =====================================================================
  if (faseNivel6 >= 1) {
      // Nos inyectamos directamente en el Nivel 5, que ya tiene todas las 
      // prioridades de evadir al Ingeniero, ir a las miguitas y hacer INSTALL.
      return ComportamientoTecnicoNivel_5(sensores);
  }

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


