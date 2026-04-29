#include "ingeniero.hpp"
#include "motorlib/util.h"
#include <iostream>
#include <queue>
#include <set>

using namespace std;

// =========================================================================
// ÁREA DE IMPLEMENTACIÓN DEL ESTUDIANTE
// =========================================================================

Action ComportamientoIngeniero::think(Sensores sensores)
{
  Action accion = IDLE;

  // Decisión del agente según el nivel
  switch (sensores.nivel)
  {
  case 0:
    accion = ComportamientoIngenieroNivel_0(sensores);
    break;
  case 1:
    accion = ComportamientoIngenieroNivel_1(sensores);
    break;
  case 2:
    accion = ComportamientoIngenieroNivel_2(sensores);
    break;
  case 3:
    accion = ComportamientoIngenieroNivel_3(sensores);
    break;
  case 4:
    accion = ComportamientoIngenieroNivel_4(sensores);
    break;
  case 5:
    accion = ComportamientoIngenieroNivel_5(sensores);
    break;
  case 6:
    accion = ComportamientoIngenieroNivel_6(sensores);
    break;
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
int VeoCasillaInteresanteI(char i, char c, char d, bool zap){
  if(c=='U') return 2;
  else if (i=='U') return 1;
  else if (d=='U') return 3;
  else if(!zap){
    if (c=='D') return 2;
    else if(i =='D') return 1;
    else if(d=='D') return 3;
  }
  
  if (c=='C') return 2;
  else if (d=='C') return 3;
  else if (i=='C') return 1;
  
  return 0;
}

/**
 * @brief Determina la mejor opcion entre todas las casillas que detecta el sensor
 * @param v el vector que contiene el tipo de casillas (idealmente filtrado por altura)
 * @param zap indica si tiene zapatillas
 * @return int 2 si es mejor WALK, 1 para TURN_SL y 3 para TURN_SR. 0 no hay nada interesante.
 */
int VeoCasillaInteresanteIAmpliada(const vector<unsigned char> &v, bool zap) {
  
  // PRIORIDAD 1: Buscar la META ('U')
  if (v[2] == 'U') return 2; // Meta justo delante
  if (v[1] == 'U' || v[4] == 'U' || v[5] == 'U' || v[9] == 'U' || v[10] == 'U' || v[11] == 'U') return 1; // Meta a la izquierda
  if (v[3] == 'U' || v[7] == 'U' || v[8] == 'U' || v[13] == 'U' || v[14] == 'U' || v[15] == 'U') return 3; // Meta a la derecha
  if (v[6] == 'U' || v[12] == 'U') {
      // Meta lejos de frente. Solo avanzamos si el paso inmediato NO es un obstáculo duro ('M' o 'P')
      if (v[2] != 'M' && v[2] != 'P') return 2;
      else return 1; // Si hay un obstáculo, giramos para intentar rodearlo
  }

  // PRIORIDAD 2: Buscar ZAPATILLAS ('D') si no las tengo
  if (!zap) {
      if (v[2] == 'D') return 2;
      if (v[1] == 'D' || v[4] == 'D' || v[5] == 'D' || v[9] == 'D') return 1;
      if (v[3] == 'D' || v[7] == 'D' || v[8] == 'D' || v[13] == 'D') return 3;
      if (v[6] == 'D' || v[12] == 'D') {
          if (v[2] != 'M' && v[2] != 'P') return 2;
          else return 1;
      }
  }

  // PRIORIDAD 3: Caminos CERCANOS (Distancia 1)
  if (v[2] == 'C') return 2;
  if (v[1] == 'C') return 1;
  if (v[3] == 'C') return 3;

  // PRIORIDAD 4: Anticipar Caminos LEJANOS (Distancia 2 y 3)
  if (v[4] == 'C' || v[5] == 'C' || v[9] == 'C' || v[10] == 'C' || v[11] == 'C') return 1;
  if (v[7] == 'C' || v[8] == 'C' || v[13] == 'C' || v[14] == 'C' || v[15] == 'C') return 3;
  if (v[6] == 'C' || v[12] == 'C') {
      if (v[2] != 'M' && v[2] != 'P') return 2;
      else return 1;
  }

  // Si no hay absolutamente nada interesante en todo el radar
  return 0;
}

/**
 * @brief Calcula las coordenadas de las casillas 1, 2 y 3 basándose en la posición y rumbo del agente
 */
void ObtenerCoordenadasAdyacentesI(int f, int c, int rumbo, int &f1, int &c1, int &f2, int &c2, int &f3, int &c3) {
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
 * @brief Comprueba si el ingeniero puede ir a la casilla por la diferencia de altura
 * 
 * @param casilla a la que quiere moverse
 * @param dif diferencia de altura entre la casilla actual y a la que se va a mover
 * @param zap indica si el agente tiene o no zapatilla
 * @return char devuelve la casilla objetivo si es viable y P si no lo es
 */
char ViablePorAlturaI(char casilla, int dif, bool zap){
  if(abs(dif)<=1 or (zap and abs(dif) <= 2)){
    return casilla;
  }else{
    return 'P';
  }
}

// funicones auxiliares nivel 0

/**
 * @brief Extrae los datos de visión segura y memoria de las celdas adyacentes
 */
void ComportamientoIngeniero::ExtraerDatosDeZonaYMemoria(const Sensores &sensores, vector<unsigned char> &vision_segura, int &mem1, int &mem2, int &mem3) {
  // 1. crear vector filtrado usando la altura
  vision_segura = sensores.superficie;
  for(int i = 1; i <= 15; i++) { 
    vision_segura[i] = ViablePorAlturaI(sensores.superficie[i], sensores.cota[i] - sensores.cota[0], tiene_zapatillas);
  }

  // 2. obtener coordenadas y memoria de las 3 casillas adyacentes
  //Tengo que hacerlo con las 6 casillas 
  int f1, c1, f2, c2, f3, c3;
  ObtenerCoordenadasAdyacentesI(sensores.posF, sensores.posC, sensores.rumbo, f1, c1, f2, c2, f3, c3);

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
Action ComportamientoIngeniero::EvaluarOpcionesAdyacentes(const vector<unsigned char> &vision_segura, int mem1, int mem2, int mem3){
  char Left = vision_segura[1];    // Casilla izquierda
  char Center = vision_segura[2];  // Casilla frontal
  char Right = vision_segura[3];   // Casilla derecha

  // PRIORIDAD 1: Meta muy cerca
  if (Center == 'U') {
    cout << "  -> ACCION: WALK (Meta al frente)" << endl;
    return WALK;
  }else if (Left == 'U') {
    cout << "  -> ACCION: TURN_SL (Meta a la izq)" << endl;
    return TURN_SL;
  }else if (Right == 'U') {
    cout << "  -> ACCION: TURN_SR (Meta a la dch)" << endl;
    return TURN_SR;
  }

  // PRIORIDAD 2: Hay caminos o zapatillas viables - elegir el menos visitado
  bool caminoLeft = (Left == 'C' || (!tiene_zapatillas && Left == 'D'));
  bool caminoCenter = (Center == 'C' || (!tiene_zapatillas && Center == 'D'));
  bool caminoRight = (Right == 'C' || (!tiene_zapatillas && Right == 'D'));

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
Action ComportamientoIngeniero::EvaluarRadarAmpliado(const vector<unsigned char> &vision_segura){
  cout << "Consultando radar ampliado." << endl;
  int pos = VeoCasillaInteresanteIAmpliada(vision_segura, tiene_zapatillas);

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


// Niveles iniciales (Comportamientos reactivos simples)
Action ComportamientoIngeniero::ComportamientoIngenieroNivel_0(Sensores sensores)
{
  // Aumentamos el reloj interno
  iteracion_actual++; 
  // Marcamos la casilla actual con el instante de tiempo actual
  mapaVisitas[sensores.posF][sensores.posC] = iteracion_actual;
  Action accion = IDLE;

  ActualizarMapa(sensores);

  // Detectamos si hemos encontrado zapatillas
  if(sensores.superficie[0]=='D') tiene_zapatillas = true;
  
  // CASO 1: Hemos alcanzado la meta
  if(sensores.superficie[0]=='U'){
    cout << "REGLA: Meta encontrada (U)" << endl;
    accion=IDLE;
  }
  // CASO 2: Estamos en medio de un giro forzado
  else if(girando>0){
    cout << "REGLA: Girando contador=" << girando << endl;
    accion=TURN_SL;
    girando--;
  } 
  // CASO 3: Hay un técnico delante y NO es la meta. Espera ingeniero porque tiene prioridad.
  else if(sensores.agentes[2]=='t' && sensores.superficie[2]!='U'){
    cout << "REGLA: Tecnico delante, no es meta" << endl;
    accion=IDLE;
  } 
  // CASO 4: Hay un técnico delante y está en meta
  else if(sensores.agentes[2]=='t' && sensores.superficie[2]=='U'){
    cout << "REGLA: Tecnico delante con meta, activando giro" << endl;
    accion=TURN_SL;
    girando=2;
  }
  // CASO PRINCIPAL: Navegación normal
  else {
    cout << "REGLA: Evaluando opciones con Memoria y Vision Ampliada." << endl;

    vector<unsigned char> vision_segura;
    int mem1, mem2, mem3;
    ExtraerDatosDeZonaYMemoria(sensores, vision_segura, mem1, mem2, mem3);

    // 3. EVALUAR OPCIONES ADYACENTES (visión cercana)
    accion = EvaluarOpcionesAdyacentes(vision_segura, mem1, mem2, mem3);

    // 4. Si no hay opciones claras adyacentes, consultar radar ampliado
    if (accion == IDLE) {
      accion = EvaluarRadarAmpliado(vision_segura);
    }
  }

  last_action = accion;
  return accion;
}

/**
 * @brief Comprueba si una celda es de tipo camino transitable.
 * @param c Carácter que representa el tipo de superficie.
 * @return true si es camino ('C'), zapatillas ('D') o meta ('U').
 */
bool ComportamientoIngeniero::es_camino(unsigned char c) const
{
  return (c == 'C' || c == 'D' || c == 'U' || c == 'S');
}

/**
 * @brief Comportamiento reactivo del ingeniero para el Nivel 1.
 * @param sensores Datos actuales de los sensores.
 * @return Acción a realizar.
 */
Action ComportamientoIngeniero::ComportamientoIngenieroNivel_1(Sensores sensores)
{
  // Incrementamos el reloj interno
  iteracion_actual++;
  // Marcamos la casilla actual con el instante de tiempo actual
  mapaVisitas[sensores.posF][sensores.posC] = iteracion_actual;
  
  Action accion = IDLE;
  ActualizarMapa(sensores);

  // Detectamos si hemos encontrado zapatillas
  if(sensores.superficie[0]=='D') tiene_zapatillas = true;
  
  // CASO 1: Hay un técnico delante. Espera ingeniero porque tiene prioridad.
  if(sensores.agentes[2]=='t'){
    if(last_action==IDLE){
      girando = 2;
      accion=TURN_SR;
    }else{
      cout << "REGLA: Tecnico delante, esperando" << endl;
      accion=IDLE;
    }
  } else if(girando > 0){
    accion=TURN_SR;
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
      cout << "  -> ACCION: TURN_SR (Sin opciones)" << endl;
      accion = TURN_SR;
    }
  }

  last_action = accion;
  return accion;
}

ubicacion DelanteSt(const ubicacion &actual) {
  // Devuelve la casilla inmediatamente frontal en función de la brújula.
    ubicacion delante = actual;
    switch (actual.brujula) {
        case 0: delante.f--; break;
        case 1: delante.f--; delante.c++; break;
        case 2: delante.c++; break;
        case 3: delante.f++; delante.c++; break;
        case 4: delante.f++; break;
        case 5: delante.f++; delante.c--; break;
        case 6: delante.c--; break;
        case 7: delante.f--; delante.c--; break;
    }
    return delante;
}

// Calcula la casilla a 2 pasos de distancia
ubicacion Delante2(const ubicacion &actual) {
  // Se usa para simular JUMP: misma dirección, dos celdas por delante.
    ubicacion sig = actual;
    switch (actual.brujula) {
        case norte: sig.f -= 2; break;
        case noreste: sig.f -= 2; sig.c += 2; break;
        case este: sig.c += 2; break;
        case sureste: sig.f += 2; sig.c += 2; break;
        case sur: sig.f += 2; break;
        case suroeste: sig.f += 2; sig.c -= 2; break;
        case oeste: sig.c -= 2; break;
        case noroeste: sig.f -= 2; sig.c -= 2; break;
    }
    return sig;
}

// Comprueba si el WALK es válido
bool EsAccesibleWalkI(const EstadoI &st, const vector<vector<unsigned char>> &terreno, const vector<vector<unsigned char>> &altura) {
    ubicacion sig = DelanteSt(st.site); // Función dada en el tutorial
    if (sig.f < 0 || sig.c < 0 || sig.f >= terreno.size() || sig.c >= terreno[0].size()) return false;
    
    // WALK exige celda destino no bloqueante y desnivel admisible.
    bool noObstaculo = terreno[sig.f][sig.c] != 'P' and terreno[sig.f][sig.c] != 'M' and terreno[sig.f][sig.c] != 'B';
    int maxDif = st.zapatillas ? 2 : 1;
    bool alturaValida = abs(altura[sig.f][sig.c] - altura[st.site.f][st.site.c]) <= maxDif;
    
    return noObstaculo and alturaValida;
}

// Comprueba si el JUMP es válido
bool EsAccesibleJumpI(const EstadoI &st, const vector<vector<unsigned char>> &terreno, const vector<vector<unsigned char>> &altura) {
    ubicacion intermedia = DelanteSt(st.site);
    ubicacion destino = Delante2(st.site);
    
    // Comprobar límites del mapa para ambas casillas
    if (destino.f < 0 || destino.c < 0 || destino.f >= terreno.size() || destino.c >= terreno[0].size()) return false;
    if (intermedia.f < 0 || intermedia.c < 0 || intermedia.f >= terreno.size() || intermedia.c >= terreno[0].size()) return false;

    // JUMP requiere que la casilla intermedia también sea transitable.
    bool intermediaValida = terreno[intermedia.f][intermedia.c] != 'P' and terreno[intermedia.f][intermedia.c] != 'M' and terreno[intermedia.f][intermedia.c] != 'B';
    // El destino no puede ser P, M, B
    bool destNoObstaculo = terreno[destino.f][destino.c] != 'P' and terreno[destino.f][destino.c] != 'M' and terreno[destino.f][destino.c] != 'B';
    
    // La altura se comprueba solo entre inicio y destino
    int maxDif = st.zapatillas ? 2 : 1;
    bool alturaValida = abs(altura[destino.f][destino.c] - altura[st.site.f][st.site.c]) <= maxDif;

    return intermediaValida and destNoObstaculo and alturaValida;
}

EstadoI applyI(Action accion, const EstadoI &st, const vector<vector<unsigned char>> &terreno, const vector<vector<unsigned char>> &altura) {
  // Transición de estados para el planificador: si la acción no es viable, el estado no avanza.
    EstadoI next = st;
    switch(accion) {
        case WALK:
            if (EsAccesibleWalkI(st, terreno, altura)) {
                next.site = DelanteSt(st.site);
                if (terreno[next.site.f][next.site.c] == 'D') next.zapatillas = true;
            }
            break;
        case JUMP:
            if (EsAccesibleJumpI(st, terreno, altura)) {
                next.site = Delante2(st.site);
                if (terreno[next.site.f][next.site.c] == 'D') next.zapatillas = true;
            }
            break;
        case TURN_SR:
            next.site.brujula = (Orientacion) ((next.site.brujula + 1) % 8);
            break;
        case TURN_SL:
            next.site.brujula = (Orientacion) ((next.site.brujula + 7) % 8);
            break;
    }
    return next;
}

list<Action> BFS_Ingeniero(EstadoI inicio, EstadoI fin, const vector<vector<unsigned char>> &terreno, const vector<vector<unsigned char>> &altura) {
    // frontier: cola FIFO de expansión BFS (camino con menos acciones primero).
    list<NodoI> frontier;
    // explored: nodos ya expandidos; discovered: nodos ya vistos (evita duplicados en cola).
    set<NodoI> explored;
  set<NodoI> discovered;
    list<Action> plan;
    bool SolutionFound = (inicio.site.f == fin.site.f and inicio.site.c == fin.site.c);
    
    NodoI current_node;
    current_node.estado = inicio;
    frontier.push_back(current_node);
    discovered.insert(NodoI{inicio, {}});

    while (!frontier.empty() and !SolutionFound) {
        current_node = frontier.front();
        frontier.pop_front();
        explored.insert(current_node);

        // Espacio de acciones del Ingeniero para nivel 2.
        vector<Action> acciones = {WALK, JUMP, TURN_SR, TURN_SL};
        
        for (Action acc : acciones) {
            if (SolutionFound) break;

            EstadoI nuevo_estado = applyI(acc, current_node.estado, terreno, altura);
            
            // Solo comprobamos objetivo tras acciones de movimiento.
            // Girar puede alinear al agente, pero no cambia su casilla.
            if ((acc == WALK || acc == JUMP) && 
                nuevo_estado.site.f == fin.site.f && nuevo_estado.site.c == fin.site.c) {
                
                plan = current_node.secuencia;
                plan.push_back(acc);
                SolutionFound = true;
            }
            else if (explored.find(NodoI{nuevo_estado, {}}) == explored.end() && discovered.find(NodoI{nuevo_estado, {}}) == discovered.end()) {
                NodoI child;
                child.estado = nuevo_estado;
                child.secuencia = current_node.secuencia;
                child.secuencia.push_back(acc);
                frontier.push_back(child);
              discovered.insert(NodoI{nuevo_estado, {}});
            }
        }
    }
    return plan;
}

// Niveles avanzados (Uso de búsqueda)
/**
 * @brief Comportamiento del ingeniero para el Nivel 2 (búsqueda).
 * @param sensores Datos actuales de los sensores.
 * @return Acción a realizar.
 */
Action ComportamientoIngeniero::ComportamientoIngenieroNivel_2(Sensores sensores)
{
  Action accion = IDLE;

  // 1) Estado interno persistente: mantener si ya obtuvo zapatillas.
  // Sincronizar estado persistente de zapatillas con la casilla actual.
  if (sensores.superficie[0] == 'D') {
    tiene_zapatillas = true;
  }

  // 2) Replanificar si el mundo real invalida la ejecución prevista.
  // Si la última acción no pudo ejecutarse, invalidar el plan actual.
  if (sensores.choque || sensores.reset) {
    hayPlan = false;
    plan.clear();
  }

    if (!hayPlan) {
        // 3) Construir estado inicial/objetivo y lanzar BFS sobre mapa conocido.
        EstadoI inicio, fin;
        inicio.site.f = sensores.posF;
        inicio.site.c = sensores.posC;
        inicio.site.brujula = sensores.rumbo;
        inicio.zapatillas = tiene_zapatillas; // Debes controlar esta variable de estado
        
        fin.site.f = sensores.BelPosF;
        fin.site.c = sensores.BelPosC;
        
        plan = BFS_Ingeniero(inicio, fin, mapaResultado, mapaCotas);
        VisualizaPlan(inicio.site, plan);
        hayPlan = (plan.size() > 0);
    }

    if (hayPlan and plan.size() > 0) {
        // 4) Política de ejecución: consumir una acción por ciclo de think().
        accion = plan.front();
        plan.pop_front();
    }

      // 5) Si el plan se agotó, en el próximo ciclo se replantea desde el estado actual.
    if (plan.size() == 0) hayPlan = false;

    return accion;
}

/**
 * @brief Comportamiento del ingeniero para el Nivel 3.
 * @param sensores Datos actuales de los sensores.
 * @return Acción a realizar.
 */
Action ComportamientoIngeniero::ComportamientoIngenieroNivel_3(Sensores sensores)
{
  if (sensores.superficie[0] == 'D') {
    tiene_zapatillas = true;
  }

  // Si el estado real invalida el plan en curso, lo descartamos.
  if (sensores.choque || sensores.reset) {
    hayPlan = false;
    plan.clear();
  }

  if (!hayPlan && sensores.agentes[2] == 't') {
    EstadoI estado_actual;
    estado_actual.site.f = sensores.posF;
    estado_actual.site.c = sensores.posC;
    estado_actual.site.brujula = sensores.rumbo;
    estado_actual.zapatillas = tiene_zapatillas;

    EstadoI estado_izq = estado_actual;
    estado_izq.site.brujula = (Orientacion) ((estado_izq.site.brujula + 7) % 8);

    EstadoI estado_dch = estado_actual;
    estado_dch.site.brujula = (Orientacion) ((estado_dch.site.brujula + 1) % 8);

    bool izquierda_viable = EsAccesibleWalkI(estado_izq, mapaResultado, mapaCotas) && sensores.agentes[1] == '_';
    bool derecha_viable = EsAccesibleWalkI(estado_dch, mapaResultado, mapaCotas) && sensores.agentes[3] == '_';
      // Plan de evasión: girar hacia lateral libre y avanzar para apartarse.
      if (izquierda_viable || derecha_viable) {
        if (izquierda_viable && derecha_viable) {
          Action giro = (last_action == TURN_SL) ? TURN_SR : TURN_SL;
          plan.push_back(giro);
        } else if (izquierda_viable) {
          plan.push_back(TURN_SL);
        } else {
          plan.push_back(TURN_SR);
        }
        plan.push_back(WALK);
      } else {
        // Sin huecos laterales: intentar saltar por encima y, si no, girar.
        bool salto_viable = EsAccesibleJumpI(estado_actual, mapaResultado, mapaCotas) && sensores.agentes[6] == '_';
        if (salto_viable) {
          plan.push_back(JUMP);
        } else {
          plan.push_back(TURN_SR);
        }
      }
      plan.push_back(WALK);
      hayPlan = !plan.empty();
    }

  Action accion = TURN_SR;
  if(!plan.empty()) {
    accion = plan.front();
    plan.pop_front();
  }

  if (plan.empty()) {
    hayPlan = false;
  }

  last_action = accion;
  return accion;
}

int CalcularImpactoEcologico(char terreno, int operacion){
  int impacto = 0;
    
  // Coste base por INSTALAR la tubería
  switch (terreno) {
    case 'A': impacto += 50; break;
    case 'H': impacto += 45; break;
    case 'S': impacto += 25; break;
    case 'C': case 'U': impacto += 15; break;
    default: impacto += 30; break;
  }

  // Coste extra por MODIFICAR el terreno (operacion: 1 = RAISE, -1 = DIG)
  if (operacion == 1) { // RAISE
    switch (terreno) {
      case 'H': impacto += 55; break;
      case 'S': impacto += 30; break;
      case 'C': case 'U': impacto += 10; break;
      default: impacto += 40; break; // "Resto"
    }
  } else if (operacion == -1) { // DIG
    switch (terreno) {
      case 'H': impacto += 65; break;
      case 'S': impacto += 40; break;
      case 'C': case 'U': impacto += 25; break;
      default: impacto += 50; break; // "Resto"
    }
  }

  return impacto;
}

int CosteInstalacionTuberia(char terreno)
{
  switch (terreno) {
    case 'A': return 50;
    case 'H': return 45;
    case 'S': return 25;
    case 'C': return 15;
    case 'U': return 15;
    default: return 30;
  }
}

vector<NodoTuberia> GenerarSucesoresTuberia(const NodoTuberia &nodo_actual, const vector<vector<unsigned char>> &terreno, const vector<vector<unsigned char>> &altura, int limite_eco){
  vector<NodoTuberia> sucesores;

  int f_actual = nodo_actual.estado_tub.site.f;
  int c_actual = nodo_actual.estado_tub.site.c;
  int h_actual = nodo_actual.estado_tub.altura_tuberia;

  int df[] = {-1, 1, 0, 0}; // Cambios en fila
  int dc[] = {0, 0, 1, -1}; // Cambios en columna

  for (int i = 0; i < 4; i++) {
    int nf = f_actual + df[i];
    int nc = c_actual + dc[i];

    // 1. Limites del mapa
    if (nf < 0 || nf >= terreno.size() || nc < 0 || nc >= terreno[0].size()) continue;

    char tipo_terreno = terreno[nf][nc];
        
    // 2. Obstáculos duros: Muros, Precipicios y Bosques no se pueden transitar
    if (tipo_terreno == 'P' || tipo_terreno == 'M' || tipo_terreno == 'B') continue;

    int h_mapa = altura[nf][nc];

    // OPCIÓN 1: La tubería sigue plana (misma altura que la actual)
    
    int op_plana = h_actual - h_mapa;

    // Comprobamos si esta opción plana es legal
    if (abs(op_plana) <= 1) { // Regla de modificación +-1
      if (tipo_terreno == 'A' && op_plana != 0) continue; // Si es agua, op_plana debe ser 0
        int impacto_sucesor = CosteInstalacionTuberia(tipo_terreno);
        bool operacion_altura_valida = true;

    
        // 2. Coste de MODIFICAR el terreno de esta casilla (RAISE o DIG)
        if (op_plana == 1) { // RAISE
            if (h_mapa < 9) { // Precondición: no se puede RAISE si altura es 9
                impacto_sucesor += CalcularImpactoEcologico(tipo_terreno, 1);
            } else {
                operacion_altura_valida = false; // Ilegal
            }
        } else if (op_plana == -1) { // DIG
            if (h_mapa > 1) { // Precondición: no se puede DIG si altura es 0 o 1
                impacto_sucesor += CalcularImpactoEcologico(tipo_terreno, -1);
            } else {
                operacion_altura_valida = false; // Ilegal
            }
        }

        // Si la operación de altura es válida y no superamos el límite ecológico
        if (operacion_altura_valida && nodo_actual.impacto + impacto_sucesor <= limite_eco) {
          
          NodoTuberia sucesor_plano = nodo_actual;
          sucesor_plano.estado_tub.site.f = nf;
          sucesor_plano.estado_tub.site.c = nc;
          sucesor_plano.estado_tub.altura_tuberia = h_actual;
          sucesor_plano.secuencia.push_back(Paso{nf, nc, op_plana});
          sucesor_plano.g_cost++;
          sucesor_plano.impacto += impacto_sucesor;
                      
          sucesores.push_back(sucesor_plano);
        }
      
    }
  

    // OPCIÓN 2: La tubería baja un nivel por gravedad
    int h_bajada = h_actual - 1;
    int op_bajada = h_bajada - h_mapa;

    // Comprobamos si esta opción en bajada es legal
    if (abs(op_bajada) <= 1) { // Regla de modificación +-1
      if (tipo_terreno == 'A' && op_bajada != 0) continue; // Si es agua, op_bajada debe ser 0
        int impacto_sucesor = CosteInstalacionTuberia(tipo_terreno);
        bool operacion_altura_valida = true;

        
        // 2. Coste de MODIFICAR el terreno de esta casilla (RAISE o DIG)
        if (op_bajada == 1) { // RAISE
            if (h_bajada < 9) { // Precondición: no se puede RAISE si altura es 9
                impacto_sucesor += CalcularImpactoEcologico(tipo_terreno, 1);
            } else {
                operacion_altura_valida = false; // Ilegal
            }
        } else if (op_bajada == -1) { // DIG
            if (h_bajada > 1) { // Precondición: no se puede DIG si altura es 0 o 1
                impacto_sucesor += CalcularImpactoEcologico(tipo_terreno, -1);
            } else {
                operacion_altura_valida = false; // Ilegal
            }
        }

        // Si la operación de altura es válida y no superamos el límite ecológico
        if (operacion_altura_valida && nodo_actual.impacto + impacto_sucesor <= limite_eco) {
          
          NodoTuberia sucesor_bajada = nodo_actual;
          sucesor_bajada.estado_tub.site.f = nf;
          sucesor_bajada.estado_tub.site.c = nc;
          sucesor_bajada.estado_tub.altura_tuberia = h_bajada;
          sucesor_bajada.secuencia.push_back(Paso{nf, nc, op_bajada});
          sucesor_bajada.g_cost++;
          sucesor_bajada.impacto += impacto_sucesor;
                      
          sucesores.push_back(sucesor_bajada);
        }
      
    }
  }
  return sucesores;
}

int HeuristicaTuberias(int f_actual, int c_actual, const vector<pair<int, int>> &metas_U){
  int min_dist = 999999;
  //Recorremos mapa en busca de todas las metas y devolvemos la que esté más cerca
  for (auto meta : metas_U) {
    int dist = abs(f_actual - meta.first) + abs(c_actual - meta.second);
    if (dist < min_dist) {
      min_dist = dist;
    }
  }
  return min_dist;
}

list<Paso> A_Star_Tuberias(EstadoTuberia inicio, const vector<vector<unsigned char>> &terreno, const vector<vector<unsigned char>> &altura, int limite_eco){
    // 1. Encontrar todas las plantas de tratamiento ('U') en el mapa
    vector<pair<int, int>> plantas_U;
    for (int f = 0; f < terreno.size(); f++) {
        for (int c = 0; c < terreno[0].size(); c++) {
            if (terreno[f][c] == 'U') {
                plantas_U.push_back({f, c});
            }
        }
    }

    priority_queue<NodoTuberia> frontier; 
    map<EstadoTuberia, vector<pair<int, int>>> explorados;
    list<Paso> plan_final;

    // 2. Inicializar los nodos raíz (¡Teniendo en cuenta RAISE y DIG en la salida!)
    char tipo_inicio = terreno[inicio.site.f][inicio.site.c];
    int h_mapa_inicio = altura[inicio.site.f][inicio.site.c];

    // Evaluamos las 3 opciones iniciales: 0 (Plana), 1 (RAISE), -1 (DIG)
    int opciones_inicio[] = {0, 1, -1};

    for (int op : opciones_inicio) {
        // Reglas físicas: No se puede alterar el agua, ni superar los límites del cielo/suelo
        if (tipo_inicio == 'A' && op != 0) continue; 
        if (op == 1 && h_mapa_inicio >= 9) continue; 
        if (op == -1 && h_mapa_inicio <= 1) continue; 

        NodoTuberia start_node;
        start_node.estado_tub = inicio;
        // ¡La altura inicial de la tubería ahora depende de si hemos modificado el terreno!
        start_node.estado_tub.altura_tuberia = h_mapa_inicio + op; 
        start_node.g_cost = 0;
        
        start_node.impacto = (op == 0) ? 0 : CalcularImpactoEcologico(tipo_inicio, op);

        // Si solo modificar la salida ya revienta el presupuesto, la descartamos
        if (start_node.impacto > limite_eco) continue;

        start_node.f_cost = start_node.g_cost + HeuristicaTuberias(inicio.site.f, inicio.site.c, plantas_U);
        start_node.secuencia.push_back(Paso{inicio.site.f, inicio.site.c, op});

        frontier.push(start_node);
        explorados[start_node.estado_tub].push_back({start_node.g_cost, start_node.impacto});
    }

    // 3. Bucle principal
    while (!frontier.empty()) {
        NodoTuberia current = frontier.top();
        frontier.pop();

        int f = current.estado_tub.site.f;
        int c = current.estado_tub.site.c;

        // CONDICIÓN DE ÉXITO:
        // Como la cola prioriza el f_cost más bajo y la ecología, la primera 'U' 
        // que sacamos es matemáticamente la ruta más óptima y físicamente legal.
        if (terreno[f][c] == 'U') {
            plan_final = current.secuencia;
            break; // Detenemos la búsqueda de inmediato
        }

        // 4. Generar sucesores
        vector<NodoTuberia> sucesores = GenerarSucesoresTuberia(current, terreno, altura, limite_eco);

        for (NodoTuberia sucesor : sucesores) {
          EstadoTuberia estado_suc = sucesor.estado_tub;
          int nuevo_g = sucesor.g_cost;
          int nuevo_impacto = sucesor.impacto;
          bool dominado = false;
            
          // Solo añadimos a la cola si NO ha sido cerrado ya
            if (explorados.find(estado_suc) != explorados.end()) {
                for (auto p : explorados[estado_suc]) {
                    // Si ya existe una ruta de igual/menor longitud Y de igual/menor impacto, descartamos
                    if (p.first <= nuevo_g && p.second <= nuevo_impacto) {
                        dominado = true;
                        break;
                    }
                }
            }
            if (!dominado) {
                explorados[estado_suc].push_back({nuevo_g, nuevo_impacto}); 
                sucesor.f_cost = sucesor.g_cost + HeuristicaTuberias(estado_suc.site.f, estado_suc.site.c, plantas_U);
                frontier.push(sucesor);
            }
        }
    }

    return plan_final;
}
  
/**
 * @brief Comportamiento del ingeniero para el Nivel 4.
 * @param sensores Datos actuales de los sensores.
 * @return Acción a realizar.
 */
Action ComportamientoIngeniero::ComportamientoIngenieroNivel_4(Sensores sensores)
{
  // Nivel 4: no ejecutamos pasos aquí; solo generamos y publicamos la red de tuberías.
  if (!hayPlan) {
        EstadoTuberia inicio;
        inicio.site.f = sensores.BelPosF;
        inicio.site.c = sensores.BelPosC;
    // La red arranca en la altura natural de la casilla de inicio.
        inicio.altura_tuberia = mapaCotas[sensores.BelPosF][sensores.BelPosC];

    // El presupuesto real es el impacto restante disponible para esta planificación.
    int limite_eco = sensores.max_ecologico;

    // Lanzamos la búsqueda sobre el mapa completo conocido.
        list<Paso> plan_tub = A_Star_Tuberias(inicio, mapaResultado, mapaCotas, limite_eco);

    // Si encontró solución, la guardamos en la estructura que lee el monitor.
        if (plan_tub.size() > 0) {
            VisualizaRedTuberias(plan_tub);
            hayPlan = true;
            cout << "Plan de tuberías trazado con éxito!" << endl;
        } else {
            cout << "No se encontró un camino válido para las tuberías." << endl;
        }
    }
    return IDLE;
}

/**
 * @brief Comportamiento del ingeniero para el Nivel 5.
 * @param sensores Datos actuales de los sensores.
 * @return Acción a realizar.
 */
Action ComportamientoIngeniero::ComportamientoIngenieroNivel_5(Sensores sensores)
{
  return IDLE;
}

/**
 * @brief Comportamiento del ingeniero para el Nivel 6.
 * @param sensores Datos actuales de los sensores.
 * @return Acción a realizar.
 */
Action ComportamientoIngeniero::ComportamientoIngenieroNivel_6(Sensores sensores)
{
  return IDLE;
}

// =========================================================================
// FUNCIONES PROPORCIONADAS
// =========================================================================

/**
 * @brief Actualiza el mapaResultado y mapaCotas con la información de los sensores.
 * @param sensores Datos actuales de los sensores.
 */
void ComportamientoIngeniero::ActualizarMapa(Sensores sensores)
{
  mapaResultado[sensores.posF][sensores.posC] = sensores.superficie[0];
  mapaCotas[sensores.posF][sensores.posC] = sensores.cota[0];

  int pos = 1;
  switch (sensores.rumbo)
  {
  case norte:
    for (int j = 1; j < 4; j++)
      for (int i = -j; i <= j; i++)
      {
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
      for (int i = -j; i <= j; i++)
      {
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
      for (int i = -j; i <= j; i++)
      {
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
      for (int i = -j; i <= j; i++)
      {
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
 * @brief Determina si una casilla es transitable para el ingeniero.
 * @param f Fila de la casilla.
 * @param c Columna de la casilla.
 * @param tieneZapatillas Indica si el agente posee las zapatillas.
 * @return true si la casilla es transitable (no es muro ni precipicio).
 */
bool ComportamientoIngeniero::EsCasillaTransitableLevel0(int f, int c, bool tieneZapatillas)
{
  if (f < 0 || f >= mapaResultado.size() || c < 0 || c >= mapaResultado[0].size())
    return false;
  return es_camino(mapaResultado[f][c]); // Solo 'C', 'D', 'U' son transitables en Nivel 0
}

/**
 * @brief Comprueba si la casilla de delante es accesible por diferencia de altura.
 * Para el ingeniero: desnivel máximo 1 sin zapatillas, 2 con zapatillas.
 * @param actual Estado actual del agente (fila, columna, orientacion, zap).
 * @return true si el desnivel con la casilla de delante es admisible.
 */
bool ComportamientoIngeniero::EsAccesiblePorAltura(const ubicacion &actual, bool zap)
{
  ubicacion del = Delante(actual);
  if (del.f < 0 || del.f >= mapaCotas.size() || del.c < 0 || del.c >= mapaCotas[0].size())
    return false;
  int desnivel = abs(mapaCotas[del.f][del.c] - mapaCotas[actual.f][actual.c]);
  if (zap && desnivel > 2)
    return false;
  if (!zap && desnivel > 1)
    return false;
  return true;
}

/**
 * @brief Devuelve la posición (fila, columna) de la casilla que hay delante del agente.
 * Calcula la casilla frontal según la orientación actual (8 direcciones).
 * @param actual Estado actual del agente (fila, columna, orientacion).
 * @return Estado con la fila y columna de la casilla de enfrente.
 */
ubicacion ComportamientoIngeniero::Delante(const ubicacion &actual) const
{
  ubicacion delante = actual;
  switch (actual.brujula)
  {
  case 0:
    delante.f--;
    break; // norte
  case 1:
    delante.f--;
    delante.c++;
    break; // noreste
  case 2:
    delante.c++;
    break; // este
  case 3:
    delante.f++;
    delante.c++;
    break; // sureste
  case 4:
    delante.f++;
    break; // sur
  case 5:
    delante.f++;
    delante.c--;
    break; // suroeste
  case 6:
    delante.c--;
    break; // oeste
  case 7:
    delante.f--;
    delante.c--;
    break; // noroeste
  }
  return delante;
}

/**
 * @brief Imprime por consola la secuencia de acciones de un plan.
 *
 * @param plan  Lista de acciones del plan.
 */
void ComportamientoIngeniero::PintaPlan(const list<Action> &plan)
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
 * @brief Imprime las coordenadas y operaciones de un plan de tubería.
 *
 * @param plan  Lista de pasos (fila, columna, operación),
 *              donde operacion = -1 (DIG), operación = 1 (RAISE).
 */
void ComportamientoIngeniero::PintaPlan(const list<Paso> &plan)
{
  auto it = plan.begin();
  while (it != plan.end())
  {
    cout << it->fil << ", " << it->col << " (" << it->op << ")\n";
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
void ComportamientoIngeniero::VisualizaPlan(const ubicacion &st,
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

/**
 * @brief Convierte un plan de tubería en la lista de casillas usada
 *        por el sistema de visualización.
 *
 * @param st    Estado de partida (no utilizado directamente).
 * @param plan  Lista de pasos del plan de tubería.
 */
void ComportamientoIngeniero::VisualizaRedTuberias(const list<Paso> &plan)
{
  listaCanalizacionTuberias.clear();
  auto it = plan.begin();
  while (it != plan.end())
  {
    // 1. Imprimimos por pantalla el paso actual
    cout << "Casilla [" << it->fil << ", " << it->col << "] -> Op: " << it->op << endl;
    listaCanalizacionTuberias.push_back({it->fil, it->col, it->op});
    it++;
  }
}
