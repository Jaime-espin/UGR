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
/**
 * @brief Comportamiento reactivo del ingeniero para el Nivel 0.
 *
 * Flujo general:
 * 1. Guarda visita y actualiza el mapa visible.
 * 2. Resuelve meta, giro forzado y bloqueo por el Técnico.
 * 3. Decide con visión local y memoria de visitas.
 * 4. Si no hay una opción clara, consulta el radar ampliado.
 *
 * @param sensores Datos actuales de los sensores.
 * @return Acción a realizar.
 */
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
 * @brief Comprueba si una celda se considera navegable para la exploración reactiva.
 *
 * En el nivel 0 se aceptan camino, sendero, zapatillas y meta como casillas útiles.
 * @param c Carácter que representa el tipo de superficie.
 * @return true si la celda puede usarse como paso seguro.
 */
bool ComportamientoIngeniero::es_camino(unsigned char c) const
{
  return (c == 'C' || c == 'D' || c == 'U' || c == 'S');
}

/**
 * @brief Comportamiento reactivo del ingeniero para el Nivel 1 (Exploración).
 *
 * Flujo general:
 * 1. Guarda visita y actualiza mapa visible.
 * 2. Resuelve interacción con el Técnico (si está delante).
 * 3. Continúa giros forzados si está girando.
 * 4. Elige casilla menos visitada (exploración pura, sin prioridad a meta).
 * 5. Si no hay opción clara, gira para seguir explorando.
 *
 * NOTA: Nivel 1 es EXPLORACIÓN ACTIVA. No prioriza meta ('U') ni zapatillas ('D'),
 * solo descubre el máximo de casillas y aprende qué caminos existen.
 *
 * @param sensores Datos actuales de los sensores.
 * @return Acción a realizar.
 */
Action ComportamientoIngeniero::ComportamientoIngenieroNivel_1(Sensores sensores)
{
  // 1. Registro de visita temporal
  iteracion_actual++;
  mapaVisitas[sensores.posF][sensores.posC] = iteracion_actual;
  
  Action accion = IDLE;
  ActualizarMapa(sensores);

  // Detectamos si hemos encontrado zapatillas
  if(sensores.superficie[0]=='D') tiene_zapatillas = true;
  
  // CASO 1: Interacción con el Técnico (Estrategia: El Ingeniero tiene PRIORIDAD)
  // Si el Técnico está delante:
  // - Si acabamos de verlo (last_action==IDLE): gira a DERECHA (45°*2=90°) para apartarse.
  //   Dirección opuesta a Técnico permite evitar colisión en ángulos.
  // - Si ya estábamos haciendo algo: ESPERA (IDLE) con prioridad hasta que Técnico se aparte.
  //   El Técnico, al verlo, debería girar automáticamente y despejar.
  if(sensores.agentes[2]=='t'){
    if(last_action==IDLE){
      // Acaba de detectar al Técnico: inicia giro a la derecha (45° cada paso)
      girando = 2;  // 2 pasos * 45° = 90° de giro total
      accion=TURN_SR;
    }else{
      // Ya estaba explorando: se queda quieto ejerciendo prioridad
      accion=IDLE;
    }
  } 
  // CASO 2: Continuar giro forzado en curso
  else if(girando > 0){
    accion=TURN_SR;
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
      // Bloqueado: girar a la derecha para buscar salida
      cout << "  -> ACCION: TURN_SR (Sin opciones, explorando)" << endl;
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
    
    // FIX 1: Asunción de espacio libre para poder explorar
    if (terreno[sig.f][sig.c] == '?') return true;

    // WALK exige celda destino no bloqueante y desnivel admisible.
    bool noObstaculo = terreno[sig.f][sig.c] != 'P' and terreno[sig.f][sig.c] != 'M' and terreno[sig.f][sig.c] != 'B';
    int maxDif = st.zapatillas ? 2 : 1;
    bool alturaValida = abs((int)altura[sig.f][sig.c] - (int)altura[st.site.f][st.site.c]) <= maxDif;
    
    return noObstaculo and alturaValida;
}

// Comprueba si el JUMP es válido
bool EsAccesibleJumpI(const EstadoI &st, const vector<vector<unsigned char>> &terreno, const vector<vector<unsigned char>> &altura) {
    ubicacion intermedia = DelanteSt(st.site);
    ubicacion destino = Delante2(st.site);
    
    // Comprobar límites del mapa para ambas casillas
    if (destino.f < 0 || destino.c < 0 || destino.f >= terreno.size() || destino.c >= terreno[0].size()) return false;
    if (intermedia.f < 0 || intermedia.c < 0 || intermedia.f >= terreno.size() || intermedia.c >= terreno[0].size()) return false;

    // 1. La casilla intermedia DEBE ser transitable. Si la conocemos, comprobamos que no sea obstáculo.
    if (terreno[intermedia.f][intermedia.c] != '?') {
        if (terreno[intermedia.f][intermedia.c] == 'P' || 
            terreno[intermedia.f][intermedia.c] == 'M' || 
            terreno[intermedia.f][intermedia.c] == 'B') {
            return false;
        }
    }

    // 2. La casilla destino DEBE ser transitable y cumplir el desnivel.
    if (terreno[destino.f][destino.c] != '?') {
        if (terreno[destino.f][destino.c] == 'P' || 
            terreno[destino.f][destino.c] == 'M' || 
            terreno[destino.f][destino.c] == 'B') {
            return false;
        }
        int maxDif = st.zapatillas ? 2 : 1;
        if (abs((int)altura[destino.f][destino.c] - (int)altura[st.site.f][st.site.c]) > maxDif) {
            return false;
        }
    }

    return true;
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

/**
 * @brief BFS (Breadth-First Search) para encontrar la ruta más corta del Ingeniero a la meta.
 * 
 * Estrategia: Exploración por niveles (FIFO frontier).
 * - Garantiza la ruta con MENOS ACCIONES (optimal para costo uniforme).
 * - Costo de cada acción: 1 (todas las acciones cuentan igual).
 * - Meta: Llegar a la posición de Belkanita (U en mapa).
 * 
 * Espacio de acciones: {WALK, JUMP, TURN_SR, TURN_SL}
 * - WALK: Movimiento en línea recta (avanza 1 casilla en dirección actual).
 * - JUMP: Salto (avanza 2 casillas, solo Ingeniero, requiere altura compatible).
 * - TURN_SR: Giro derecha 45° (cambia orientación).
 * - TURN_SL: Giro izquierda 45° (cambia orientación).
 * 
 * Restricciones de movimiento (aplicadas en applyI):
 * - Altura máxima sin zapatillas: ±1 de la casilla actual.
 * - Altura máxima con zapatillas: ±2 de la casilla actual.
 * - Terrenos no transitables: Precipicio (P), Agua (A), Obstáculos Mario (M).
 * - Terreno especial Bosque (B): Solo con zapatillas.
 * 
 * Comprobación de meta:
 * - SOLO después de acciones de movimiento (WALK, JUMP).
 * - NO después de rotaciones (girar no cambia posición).
 * 
 * Estructuras de datos:
 * - frontier: Cola FIFO para expansión por niveles.
 * - explored: Nodos ya procesados (evita reprocesamiento).
 * - discovered: Nodos ya vistos (evita duplicados en frontier).
 * 
 * @param inicio Estado inicial (posición, orientación, zapatillas).
 * @param fin Estado objetivo (posición de meta, orientación no importa).
 * @param terreno Matriz de tipos de terreno.
 * @param altura Matriz de altura de cada casilla.
 * @return Lista de acciones que conducen a la meta, vacía si no hay solución.
 */
list<Action> BFS_Ingeniero(EstadoI inicio, EstadoI fin, const vector<vector<unsigned char>> &terreno, const vector<vector<unsigned char>> &altura) {
    // Inicializar estructura de BFS.
    list<NodoI> frontier;           // Cola FIFO: nodos a expandir.
    set<NodoI> explored;            // Nodos ya procesados.
    set<NodoI> discovered;          // Nodos ya en frontier (evita inserciones repetidas).
    list<Action> plan;              // Ruta encontrada (secuencia de acciones).
    
    // Verificar si ya estamos en la meta.
    bool SolutionFound = (inicio.site.f == fin.site.f and inicio.site.c == fin.site.c);
    
    // Inicializar frontier con nodo inicial.
    NodoI current_node;
    current_node.estado = inicio;
    frontier.push_back(current_node);
    discovered.insert(NodoI{inicio, {}});

    // Expansión por niveles (BFS): procesar nodos en orden FIFO.
    while (!frontier.empty() and !SolutionFound) {
        // Extraer siguiente nodo a expandir.
        current_node = frontier.front();
        frontier.pop_front();
        explored.insert(current_node);

        // Espacio de acciones disponibles para el Ingeniero.
        vector<Action> acciones = {WALK, JUMP, TURN_SR, TURN_SL};
        
        for (Action acc : acciones) {
            if (SolutionFound) break;

            // Aplicar acción al estado actual: simular movimiento/rotación.
            EstadoI nuevo_estado = applyI(acc, current_node.estado, terreno, altura);
            
            // Comprobación de meta: SOLO después de movimientos (WALK/JUMP).
            // Rotaciones no cambian posición; no es necesario verificar meta tras girar.
            if ((acc == WALK || acc == JUMP) && 
                nuevo_estado.site.f == fin.site.f && nuevo_estado.site.c == fin.site.c) {
                
                // SOLUCIÓN ENCONTRADA: construir ruta completa.
                plan = current_node.secuencia;
                plan.push_back(acc);
                SolutionFound = true;
            }
            // Si el nuevo estado no ha sido visitado, agregarlo a frontier.
            else if (explored.find(NodoI{nuevo_estado, {}}) == explored.end() && 
                     discovered.find(NodoI{nuevo_estado, {}}) == discovered.end()) {
                NodoI child;
                child.estado = nuevo_estado;
                child.secuencia = current_node.secuencia;
                child.secuencia.push_back(acc);
                frontier.push_back(child);
                discovered.insert(NodoI{nuevo_estado, {}});
            }
        }
    }
    
    // Devolver plan: lista de acciones (vacía si no hay solución).
    return plan;
}

// Niveles avanzados (Uso de búsqueda)
/**
 * ============================================================================
 * NIVEL 2: BÚSQUEDA CON MAPA CONOCIDO - INGENIERO
 * ============================================================================
 * 
 * @brief Comportamiento deliberativo: el Ingeniero planifica la ruta completa
 *        hacia Belkanita usando BFS, luego ejecuta las acciones paso a paso.
 * 
 * ESTRATEGIA:
 * - Fase planificación (si no hay plan válido):
 *   1. Construir estado inicial (posición, orientación, zapatillas) desde sensores.
 *   2. Construir estado objetivo (posición de Belkanita).
 *   3. Ejecutar BFS para encontrar la ruta más corta (menos acciones).
 *   4. Guardar plan en list<Action> y marcar hayPlan=true.
 * 
 * - Fase ejecución (si hay plan):
 *   1. Extraer primera acción del plan.
 *   2. Remover acción del plan.
 *   3. Devolver acción al motor de juego.
 *   4. Esperar siguiente ciclo para obtener sensores actualizados.
 * 
 * INVALIDACIÓN DE PLAN:
 * - Si sensores.choque==true: última acción no se ejecutó (obstáculo imprevisto).
 * - Si sensores.reset==true: el mundo fue restaurado (reinicio de nivel).
 * - Acción: Limpiar plan, marcar hayPlan=false, replantificar en siguiente ciclo.
 * 
 * GESTIÓN DE ZAPATILLAS:
 * - Persistencia: tiene_zapatillas se mantiene entre ciclos.
 * - Sincronización: Si sensor detecta 'D' en casilla actual, activar zapatillas.
 * - Impacto: Zapatillas permite mayor desplazamiento vertical (±2 vs ±1).
 * 
 * COSTO DE PLAN:
 * - BFS busca ruta con MENOS ACCIONES (costo uniforme: 1 por acción).
 * - NO considera consumo energético (a diferencia de Nivel 3+ con A*).
 * - Ventaja: Rápido, predecible; Desventaja: Puede usar terreno caro.
 * 
 * EJECUCIÓN PASO A PASO:
 * - Un ciclo = una acción (WALK, JUMP, TURN_SR, TURN_SL).
 * - Motor de juego procesa acción y devuelve sensores actualizados.
 * - Control de loop: Si plan vacío, replantificar automáticamente.
 * 
 * FLUJO COMPLETO:
 *   ┌─ Sin plan válido ─┐
 *   │                    ├─→ BFS ─→ plan
 *   └────────────────────┘
 *         ↑ (choque/reset)
 *         │
 *   Con plan ──→ Extraer acción ──→ Devolver
 *         │
 *         └─ Si vacío ──→ Replantificar
 * 
 * @param sensores Sensor data: posición actual, orientación, zapatillas detectadas, etc.
 * @return Acción: Primera del plan, o IDLE si plan vacío y sin solución.
 */
Action ComportamientoIngeniero::ComportamientoIngenieroNivel_2(Sensores sensores)
{
  Action accion = IDLE;

  // 1) Sensor superficie[0]: material de la casilla actual.
  // Si es 'D' (zapatillas), activar persistentemente para futuras acciones.
  if (sensores.superficie[0] == 'D') {
    tiene_zapatillas = true;
  }

  // 2) Replanificar si el mundo real invalida la ejecución prevista.
  // Si la última acción no pudo ejecutarse, invalidar el plan actual.
  if (sensores.choque || sensores.reset) {
    hayPlan = false;
    plan.clear();
  }

  // ─────────────────────────────────────────────────────────────
  // 3. PLANIFICACIÓN: Si no hay plan válido, generar nuevo
  // ─────────────────────────────────────────────────────────────
  if (!hayPlan) {
      // Construir estado inicial desde sensores actuales.
      EstadoI inicio, fin;
      inicio.site.f = sensores.posF;
      inicio.site.c = sensores.posC;
      inicio.site.brujula = sensores.rumbo;
      inicio.zapatillas = tiene_zapatillas;  // Incluir estado de zapatillas en búsqueda.
      
      // Construir estado objetivo: posición de Belkanita.
      fin.site.f = sensores.BelPosF;
      fin.site.c = sensores.BelPosC;
      
      // Ejecutar BFS: encuentra ruta con menos acciones hacia meta.
      plan = BFS_Ingeniero(inicio, fin, mapaResultado, mapaCotas);
      VisualizaPlan(inicio.site, plan);  // Mostrar plan en mapa (debug).
      hayPlan = (plan.size() > 0);       // Marcar si se encontró solución.
  }

  // ─────────────────────────────────────────────────────────────
  // 4. EJECUCIÓN: Extraer y devolver primera acción del plan
  // ─────────────────────────────────────────────────────────────
  if (hayPlan && plan.size() > 0) {
      // Extraer primera acción (orden FIFO).
      accion = plan.front();
      plan.pop_front();
  }

  // ─────────────────────────────────────────────────────────────
  // 5. CONTROL DE CICLO: Si plan agotado, marcar para replantificar
  // ─────────────────────────────────────────────────────────────
  // En el siguiente ciclo, sensores tendrán nueva posición.
  // Si hayPlan==false, volveremos a FASE 3 para generar nuevo plan.
  if (plan.size() == 0) hayPlan = false;

  return accion;
}

/**
 * ============================================================================
 * NIVEL 3: REACCIÓN AVANZADA Y EVASIÓN (INGENIERO)
 * ============================================================================
 *
 * Descripción general:
 * - Nivel 3 mejora la reactividad frente a la presencia del Técnico delante.
 * - Si el Técnico está delante (sensor agentes[2]=='t') se intenta una maniobra
 *   de evasión rápida: girar lateralmente y avanzar, o saltar si es necesario.
 * - El Ingeniero mantiene `tiene_zapatillas` y replanifica si hay choque/reset.
 *
 * Política de evasión (resumen):
 * 1) Construir estados virtuales a izquierda/derecha para evaluar viabilidad.
 * 2) Si hay hueco lateral libre (walk viable y sensor de agente en esa casilla '_'),
 *    preferir moverse lateralmente: girar hacia el hueco y hacer `WALK`.
 * 3) Si ambos laterales libres, alternar giro según `last_action` para reducir
 *    oscilaciones (desempate).
 * 4) Si no hay huecos laterales, intentar `JUMP` por encima (si es viable y
 *    sensor de la casilla por encima está libre), si no, girar a la derecha.
 * 5) Finalmente, añadir `WALK` para avanzar tras maniobra (comportamiento
 *    original conserva este paso adicional).
 *
 * Notas de diseño:
 * - `EsAccesibleWalkI` / `EsAccesibleJumpI` validan restricciones de altura y
 *   terreno (se tienen en cuenta zapatillas).
 * - Se usa `plan` (FIFO) para almacenar la secuencia de acciones de evasión;
 *   se ejecuta una acción por ciclo.
 * - No se modifica la lógica funcional; solo se documenta para facilitar
 *   comprensión y mantenimiento.
 *
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
  
  if(operacion == 0){
    // Coste base por INSTALAR la tubería
    switch (terreno) {
      case 'A': impacto += 50; break;
      case 'H': impacto += 45; break;
      case 'S': impacto += 25; break;
      case 'C': case 'U': impacto += 15; break;
      default: impacto += 30; break;
    }
  }
  // Coste extra por MODIFICAR el terreno (operacion: 1 = RAISE, -1 = DIG)
  else if (operacion == 1) { // RAISE
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
    char tipo_actual = terreno[f_actual][c_actual];
        
    // 2. Obstáculos duros: Muros, Precipicios y Bosques no se pueden transitar
    if (tipo_terreno == 'P' || tipo_terreno == 'M' || tipo_terreno == 'B') continue;

    int h_mapa = altura[nf][nc];

    // OPCIÓN 1: La tubería sigue plana (misma altura que la actual)
    
    int op_plana = h_actual - h_mapa;

    // Comprobamos si esta opción plana es legal
    if (abs(op_plana) <= 1) { // Regla de modificación +-1
      if (!(tipo_terreno == 'A' && op_plana != 0)){ // Si es agua, op_plana debe ser 0
        int impacto_sucesor = CosteInstalacionTuberia(tipo_actual) + CosteInstalacionTuberia(tipo_terreno);
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
        if (operacion_altura_valida) {
          int impacto_con_sucesor = nodo_actual.impacto + impacto_sucesor;
          
          // CRUCIAL: Validar presupuesto ANTES de crear sucesor
          if (impacto_con_sucesor <= limite_eco) {
            NodoTuberia sucesor_plano = nodo_actual;
            sucesor_plano.estado_tub.site.f = nf;
            sucesor_plano.estado_tub.site.c = nc;
            sucesor_plano.estado_tub.altura_tuberia = h_actual;
            sucesor_plano.secuencia.push_back(Paso{nf, nc, op_plana});
            sucesor_plano.g_cost++;
            sucesor_plano.impacto = impacto_con_sucesor;
                        
            sucesores.push_back(sucesor_plano);
          }
        }
      }
    }
  

    // OPCIÓN 2: La tubería baja un nivel por gravedad
    int h_bajada = h_actual - 1;
    int op_bajada = h_bajada - h_mapa;

    // Comprobamos si esta opción en bajada es legal
    if (abs(op_bajada) <= 1) { // Regla de modificación +-1
      if (!(tipo_terreno == 'A' && op_bajada != 0)){ // Si es agua, op_bajada debe ser 0
        int impacto_sucesor = CosteInstalacionTuberia(tipo_actual) + CosteInstalacionTuberia(tipo_terreno);
        bool operacion_altura_valida = true;

        
        // 2. Coste de MODIFICAR el terreno de esta casilla (RAISE o DIG)
        if (op_bajada == 1) { // RAISE
            if (h_bajada < 9) { // Precondición: no se puede RAISE si altura es 9
                impacto_sucesor += CalcularImpactoEcologico(tipo_terreno, 1);
            } else {
                operacion_altura_valida = false; // Ilegal
            }
        } else if (op_bajada == -1) { // DIG
            if (h_mapa > 1) { // Precondición: no se puede DIG si altura es 0 o 1
                impacto_sucesor += CalcularImpactoEcologico(tipo_terreno, -1);
            } else {
                operacion_altura_valida = false; // Ilegal
            }
        }

        // Si la operación de altura es válida y no superamos el límite ecológico
        if (operacion_altura_valida) {
          int impacto_con_sucesor = nodo_actual.impacto + impacto_sucesor;
          
          // CRUCIAL: Validar presupuesto ANTES de crear sucesor
          if (impacto_con_sucesor <= limite_eco) {
            NodoTuberia sucesor_bajada = nodo_actual;
            sucesor_bajada.estado_tub.site.f = nf;
            sucesor_bajada.estado_tub.site.c = nc;
            sucesor_bajada.estado_tub.altura_tuberia = h_bajada;
            sucesor_bajada.secuencia.push_back(Paso{nf, nc, op_bajada});
            sucesor_bajada.g_cost++;
            sucesor_bajada.impacto = impacto_con_sucesor;
            
            sucesores.push_back(sucesor_bajada);
          }
        }
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
        
        start_node.impacto = 0;
        if (op != 0) {
          start_node.impacto += CalcularImpactoEcologico(tipo_inicio, op);
        }

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
        // La primera 'U' que sacamos con impacto valido es la ruta óptima.
        if (terreno[f][c] == 'U') {
            if (current.impacto <= limite_eco) {
                plan_final = current.secuencia;
                break; // Detenemos la búsqueda de inmediato
            }
            // Si excede presupuesto, ignorar este nodo e intentar otro camino
        }

        // 4. Generar sucesores
        vector<NodoTuberia> sucesores = GenerarSucesoresTuberia(current, terreno, altura, limite_eco);

        for (NodoTuberia sucesor : sucesores) {
          EstadoTuberia estado_suc = sucesor.estado_tub;
          int nuevo_g = sucesor.g_cost;
          int nuevo_impacto = sucesor.impacto;
          bool dominado = false;
          
          // ✅ VALIDACIÓN: Asegurar que el sucesor respeta el presupuesto
          if (nuevo_impacto > limite_eco) {
              continue;  // Descartar sucesores que superen presupuesto
          }
            
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
/**
 * ============================================================================
 * NIVEL 4: PLANIFICACIÓN ESTRATÉGICA DE RED DE TUBERÍAS (INGENIERO)
 * ============================================================================
 * 
 * @brief Planificación offline de la red de tuberías hacia plantas de tratamiento.
 *        NO ejecuta acciones; solo calcula y visualiza la ruta óptima.
 * 
 * OBJETIVO DEL NIVEL 4:
 * Encontrar la red de tuberías más eficiente (menor impacto ecológico) que:
 * 1. Comienza en Belkanita (posición inicial de la tubería madre).
 * 2. Alcanza al menos una planta de tratamiento ('U' en mapa).
 * 3. Respeta el presupuesto ecológico máximo (sensores.max_ecologico).
 * 4. Permite modificaciones de terreno (RAISE, DIG) donde sea necesario.
 * 
 * ESTRATEGIA:
 * - Se ejecuta UNA SOLA VEZ (si !hayPlan).
 * - Construye un EstadoTuberia inicial en Belkanita.
 * - Llama a A_Star_Tuberias para encontrar la red óptima.
 * - Si se encuentra solución, visualiza y marca hayPlan=true.
 * - Devuelve siempre IDLE (sin ejecución de acciones en Nivel 4).
 * 
 * MODELO DE BÚSQUEDA:
 * Algoritmo: A* multinivel con optimización ecológica y geométrica.
 * - Estado: EstadoTuberia{ubicacion site, int altura_tuberia}
 * - Nodo: NodoTuberia{estado_tub, g_cost, f_cost, impacto_eco, secuencia}
 * - Meta: Alcanzar cualquier casilla 'U' (planta de tratamiento).
 * - Costo: Suma de impactos ecológicos (INSTALL + RAISE/DIG).
 * - Heurística: Distancia mínima a cualquier 'U' (admisible).
 * - Ordenamiento: Prioriza menor f_cost; en empate, menor impacto_eco.
 * 
 * COMPONENTES:
 * 1. A_Star_Tuberias: Búsqueda principal (busca ruta a cualquier 'U').
 * 2. GenerarSucesoresTuberia: Expande un nodo (genera tubería en 8 direcciones).
 * 3. HeuristicaTuberias: Distancia mínima a cualquier 'U'.
 * 4. CosteInstalacionTuberia / CalcularImpactoEcologico: Valúan cada casilla.
 * 5. VisualizaRedTuberias: Muestra la red en el monitor.
 * 
 * MODIFICACIONES DE TERRENO:
 * - RAISE (op=+1): Elevar terreno (+5 ecología base, +altura_mod).
 * - DIG (op=-1): Excavar terreno (-2 ecología base, +altura_mod).
 * - op=0: Sin modificación.
 * - Restricciones: No modificar agua ('A'), ni exceder cotas del mapa (0-9).
 * 
 * LIMITACIONES CONOCIDAS:
 * - Presupuesto ecológico es GLOBAL para toda la planificación.
 * - No se replantifica si falla (marcar hayPlan previene reintentos).
 * - No ejecuta el plan en Nivel 4 (puro cálculo).
 * - Nivel 5 añade la ejecución física de la red.
 * 
 * @param sensores Sensores con posición de Belkanita y presupuesto ecológico.
 * @return Siempre IDLE (solo planificación, sin ejecución en Nivel 4).
 */
Action ComportamientoIngeniero::ComportamientoIngenieroNivel_4(Sensores sensores)
{
  // ─────────────────────────────────────────────────────────────
  // 1. PLANIFICACIÓN: Calcular red de tuberías si no existe
  // ─────────────────────────────────────────────────────────────
  if (!hayPlan) {
      // Construir estado inicial: raíz de la red en Belkanita.
      EstadoTuberia inicio;
      inicio.site.f = sensores.BelPosF;
      inicio.site.c = sensores.BelPosC;
      inicio.altura_tuberia = mapaCotas[sensores.BelPosF][sensores.BelPosC];

      // Presupuesto ecológico disponible: límite máximo de impacto total.
      int limite_eco = sensores.max_ecologico;

      // ─────────────────────────────────────────────────────────────
      // 2. BUSCAR RED ÓPTIMA: A* hacia cualquier planta ('U')
      // ─────────────────────────────────────────────────────────────
      // A_Star_Tuberias devuelve lista de Paso{fil, col, op}:
      // - fil, col: posición de la casilla en la red.
      // - op: operación de terreno (-1=DIG, 0=mantener, +1=RAISE).
      // La búsqueda respeta todas las restricciones físicas y presupuestarias.
      list<Paso> plan_tub = A_Star_Tuberias(inicio, mapaResultado, mapaCotas, limite_eco);

      // ─────────────────────────────────────────────────────────────
      // 3. RESULTADO: Visualizar y marcar como exitoso
      // ─────────────────────────────────────────────────────────────
      if (plan_tub.size() > 0) {
          // Visualizar la red en el monitor (para debug/seguimiento).
          VisualizaRedTuberias(plan_tub);
          hayPlan = true;  // Marcar como planificado exitosamente.
          cout << "Plan de tuberías trazado con éxito!" << endl;
      } else {
          // No se encontró solución viable (presupuesto insuficiente, etc).
          cout << "No se encontró un camino válido para las tuberías." << endl;
          // ✅ IMPORTANTE: Marcar hayPlan=false explícitamente para permitir reintentos
          hayPlan = false;
      }
  }

  // ─────────────────────────────────────────────────────────────
  // 4. NIVEL 4 NO EJECUTA: Devolver IDLE siempre
  // ─────────────────────────────────────────────────────────────
  // Nivel 4 es solo planificación offline.
  // La ejecución física de la red ocurre en Nivel 5.
  return IDLE;
}

/**
 * @brief Comportamiento del ingeniero para el Nivel 5 - INSTALACIÓN DE RED DE TUBERÍAS.
 * 
 * ═══════════════════════════════════════════════════════════════════════════════
 * ALGORITMO COORDINADO INGENIERO-TÉCNICO:
 * ═══════════════════════════════════════════════════════════════════════════════
 * 
 * El Ingeniero ejecuta 5 fases para construir la red de tuberías junto al Técnico:
 * 
 * FASE 0 (PLANIFICACIÓN): 
 *   - Se ejecuta UNA SOLA VEZ al inicio del nivel.
 *   - Utiliza A* para planificar la ruta óptima de tuberías (respetando el
 *     presupuesto ecológico).
 *   - Almacena el plan en planTuberiasVec[] para acceso rápido con tramo_idx.
 *   - Transición → FASE 1.
 * 
 * FASE 1 (MOVIMIENTO):
 *   - El Ingeniero se mueve hacia el tramo actual del plan (posición planTuberiasVec[tramo_idx]).
 *   - Una vez llega, si es necesario, ejecuta RAISE o DIG para modificar el terreno.
 *   - Cuando la casilla está lista, envía COME (señal para el Técnico).
 *   - Transición → FASE 2.
 * 
 * FASE 2 (INSTALACIÓN):
 *   - El Ingeniero deja una "migita de pan" (COME) para que el Técnico se dirija aquí.
 *   - Esta acción también le sirve al Ingeniero para abandonar la casilla.
 *   - Transición → FASE 3 (en el siguiente tick).
 * 
 * FASE 3 (PREPARACIÓN):
 *   - El Ingeniero se mueve al siguiente tramo (planTuberiasVec[tramo_idx+1]).
 *   - Prepara el terreno (RAISE/DIG) si es necesario.
 *   - Cuando está listo, se gira hacia el Técnico.
 *   - Transición → FASE 4.
 * 
 * FASE 4 (SINCRONIZACIÓN):
 *   - El Ingeniero y el Técnico se miran a los ojos (enfrente).
 *   - Cuando se ven, AMBOS ejecutan INSTALL simultáneamente.
 *   - Después de INSTALL, el índice avanza y se vuelve a FASE 2 para el siguiente tramo.
 * 
 * ═══════════════════════════════════════════════════════════════════════════════
 * NOTAS IMPORTANTES:
 * ═══════════════════════════════════════════════════════════════════════════════
 * - El ciclo se repite hasta cubrir todos los tramos: tramo_idx va de 0 hasta
 *   planTuberiasVec.size()-1.
 * - El Ingeniero y el Técnico están siempre separados por 1 casilla: cuando el
 *   Ingeniero está en tramo_idx+1, el Técnico está en tramo_idx.
 * - Si el Técnico bloquea el paso del Ingeniero, se activa evasión reactiva.
 * - Si hay colisión o reset, se borra el plan de movimiento y se replanifica.
 * 
 * @param sensores Datos actuales de los sensores.
 * @return Acción a realizar en este tick.
 */
Action ComportamientoIngeniero::ComportamientoIngenieroNivel_5(Sensores sensores)
{
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
  // FASE 0: PLANIFICACIÓN OFFLINE DE LA RED DE TUBERÍAS (Ejecuta 1 sola vez)
  // ─────────────────────────────────────────────────────────────────────────
  if (faseNivel5 == 0) {
    EstadoTuberia inicio;
    inicio.site.f = sensores.BelPosF;
    inicio.site.c = sensores.BelPosC;
    inicio.altura_tuberia = mapaCotas[sensores.BelPosF][sensores.BelPosC];
    
    // Planificar la red completa usando A* respetando presupuesto ecológico
    list<Paso> planTuberias = A_Star_Tuberias(inicio, mapaResultado, mapaCotas, sensores.max_ecologico);

    if (!planTuberias.empty()) {
      VisualizaRedTuberias(planTuberias);
      
      // Convertir lista a vector para acceso indexado eficiente durante ejecución
      for (auto p : planTuberias) planTuberiasVec.push_back(p);
      
      faseNivel5 = 1;  // Pasar a FASE 1 (movimiento al primer tramo)
      tramo_idx = 0;   // Comenzar desde el primer tramo
    }
    return IDLE;
  }

  // ─────────────────────────────────────────────────────────────────────────
  // VALIDACIÓN: Detectar fin de red (todos los tramos completados)
  // ─────────────────────────────────────────────────────────────────────────
  if (tramo_idx + 1 >= planTuberiasVec.size()) return IDLE;

  // ─────────────────────────────────────────────────────────────────────────
  // FASE 1: MOVIMIENTO HACIA EL TRAMO ACTUAL
  // ─────────────────────────────────────────────────────────────────────────
  // Objetivo: Alcanzar planTuberiasVec[tramo_idx] y preparar su terreno (RAISE/DIG).
  // Una vez completado, envía COME al Técnico.
  // ─────────────────────────────────────────────────────────────────────────
  if (faseNivel5 == 1) {
    Paso target = planTuberiasVec[tramo_idx];
    
    // SUBCASO 1.1: Ya estamos en la casilla del tramo
    if (sensores.posF == target.fil && sensores.posC == target.col) {
      // Modificar terreno si es necesario (RAISE/DIG)
      if (target.op == 1) { 
        planTuberiasVec[tramo_idx].op = 0;  // Marcar como completado
        return RAISE; 
      }
      if (target.op == -1) { 
        planTuberiasVec[tramo_idx].op = 0;  // Marcar como completado
        return DIG; 
      }
      
      // La casilla está lista → enviar señal COME al Técnico y pasar a FASE 2
      faseNivel5 = 2;
      hayPlan = false;
      plan.clear();
      return IDLE;
    }

    // SUBCASO 1.2: No hemos llegado aún → planificar ruta
    if (!hayPlan) {
      EstadoI start, goal;
      start.site.f = sensores.posF;
      start.site.c = sensores.posC;
      start.site.brujula = sensores.rumbo;
      start.zapatillas = tiene_zapatillas;
      goal.site.f = target.fil;
      goal.site.c = target.col;

      plan = BFS_Ingeniero(start, goal, mapaResultado, mapaCotas);
      VisualizaPlan(start.site, plan);
      hayPlan = !plan.empty();
    }

    // SUBCASO 1.3: Ejecutar el plan de movimiento (con evasión reactiva si es necesario)
    if (hayPlan && !plan.empty()) {
      // Si el Técnico está en el camino, activar evasión
      if ((plan.front() == WALK && sensores.agentes[2] == 't') || 
          (plan.front() == JUMP && sensores.agentes[6] == 't')) {
        
        // Intentar ir a izquierda o derecha del Técnico
        plan.clear();
        EstadoI st_actual = {ubicacion{sensores.posF, sensores.posC, (Orientacion)sensores.rumbo}, tiene_zapatillas};
        EstadoI st_izq = st_actual; 
        st_izq.site.brujula = (Orientacion)((st_izq.site.brujula + 7) % 8);
        EstadoI st_dch = st_actual; 
        st_dch.site.brujula = (Orientacion)((st_dch.site.brujula + 1) % 8);

        bool izq_viable = EsAccesibleWalkI(st_izq, mapaResultado, mapaCotas) && sensores.agentes[1] == '_';
        bool dch_viable = EsAccesibleWalkI(st_dch, mapaResultado, mapaCotas) && sensores.agentes[3] == '_';

        if (izq_viable) { plan.push_back(TURN_SL); plan.push_back(WALK); } 
        else if (dch_viable) { plan.push_back(TURN_SR); plan.push_back(WALK); } 
        else {
          bool salto_viable = EsAccesibleJumpI(st_actual, mapaResultado, mapaCotas) && sensores.agentes[6] == '_';
          if (salto_viable) plan.push_back(JUMP);
          else plan.push_back(TURN_SR);  // Girar esperando
        }
        hayPlan = true;
        Action a = plan.front(); 
        plan.pop_front();
        return a;
      }

      // Ejecutar acción siguiente del plan
      Action a = plan.front();
      plan.pop_front();
      if (plan.empty()) hayPlan = false;
      return a;
    }
    return IDLE;
  }

  // ─────────────────────────────────────────────────────────────────────────
  // FASE 2: DEJAR MIGITA DE PAN (COME)
  // ─────────────────────────────────────────────────────────────────────────
  // El Ingeniero deja una señal para que el Técnico sepa dónde ir.
  // Esto también sirve para que el Ingeniero se mueva a la siguiente posición.
  // ─────────────────────────────────────────────────────────────────────────
  if (faseNivel5 == 2) {
    faseNivel5 = 3;  // Pasar a FASE 3 (en el siguiente tick)
    hayPlan = false;
    plan.clear();
    return COME;  // Dejar "migita de pan" para el Técnico
  }

  // ─────────────────────────────────────────────────────────────────────────
  // FASE 3: PREPARACIÓN DEL SIGUIENTE TRAMO
  // ─────────────────────────────────────────────────────────────────────────
  // Objetivo: Alcanzar planTuberiasVec[tramo_idx+1] y preparar su terreno (RAISE/DIG).
  // El Técnico está en planTuberiasVec[tramo_idx], ambos listos para sincronización.
  // ─────────────────────────────────────────────────────────────────────────
  if (faseNivel5 == 3) {
    Paso target = planTuberiasVec[tramo_idx + 1];
    
    // SUBCASO 3.1: Ya estamos en el siguiente tramo
    if (sensores.posF == target.fil && sensores.posC == target.col) {
      // Modificar terreno si es necesario (RAISE/DIG)
      if (target.op == 1) { 
        planTuberiasVec[tramo_idx + 1].op = 0;  // Marcar como completado
        return RAISE;
      }
      if (target.op == -1) { 
        planTuberiasVec[tramo_idx + 1].op = 0;  // Marcar como completado
        return DIG;
      }
      
      // Terreno preparado → pasar a FASE 4 (girarse hacia el Técnico)
      faseNivel5 = 4;
      hayPlan = false;
      plan.clear();
      return IDLE;
    }
    
    // Calcular distancia Manhattan y desnivel máximo permitido
    int dist = abs(target.fil - sensores.posF) + abs(target.col - sensores.posC);
    int maxDif = tiene_zapatillas ? 2 : 1;
    int difAltura = abs((int)mapaCotas[target.fil][target.col] - (int)sensores.cota[0]);

    // SUBCASO 3.2: Objetivo cercano (distancia=1) → control reactivo directo
    if (dist == 1 && difAltura <= maxDif) {
      if (hayPlan) { hayPlan = false; plan.clear(); }
      
      // Calcular orientación ideal hacia la casilla
      int dF = target.fil - sensores.posF;
      int dC = target.col - sensores.posC;
      Orientacion ideal;

      if (dF < 0 && dC == 0) ideal = norte;
      else if (dF == 0 && dC > 0) ideal = este;
      else if (dF > 0 && dC == 0) ideal = sur;
      else if (dF == 0 && dC < 0) ideal = oeste;
      else ideal = (Orientacion)sensores.rumbo;  // Salvaguarda

      // Si no miramos la dirección, giramos
      if (sensores.rumbo != ideal) {
        int diff = (ideal - sensores.rumbo + 8) % 8;
        if (diff <= 4) return TURN_SR;
        else return TURN_SL;
      }
      
      // Ya miramos → avanzar o esquivar al Técnico
      if (sensores.agentes[2] == 't') return TURN_SR;  // Técnico adelante → girar esperando
      return WALK;
    }
    
    // SUBCASO 3.3: Objetivo lejano → usar BFS para planificación
    if (!hayPlan) {
      EstadoI start, goal;
      start.site.f = sensores.posF;
      start.site.c = sensores.posC;
      start.site.brujula = (Orientacion)sensores.rumbo;
      start.zapatillas = tiene_zapatillas;
      goal.site.f = target.fil;
      goal.site.c = target.col;
      
      plan = BFS_Ingeniero(start, goal, mapaResultado, mapaCotas);
      VisualizaPlan(start.site, plan);
      hayPlan = !plan.empty();
    }

    // Ejecutar el plan de movimiento (con evasión reactiva si es necesario)
    if (hayPlan && !plan.empty()) {
      // Si el Técnico está en el camino, activar evasión
      if ((plan.front() == WALK && sensores.agentes[2] == 't') || 
          (plan.front() == JUMP && sensores.agentes[6] == 't')) {
        
        // Intentar ir a izquierda o derecha del Técnico
        plan.clear();
        EstadoI st_actual = {ubicacion{sensores.posF, sensores.posC, (Orientacion)sensores.rumbo}, tiene_zapatillas};
        EstadoI st_izq = st_actual; 
        st_izq.site.brujula = (Orientacion)((st_izq.site.brujula + 7) % 8);
        EstadoI st_dch = st_actual; 
        st_dch.site.brujula = (Orientacion)((st_dch.site.brujula + 1) % 8);

        bool izq_viable = EsAccesibleWalkI(st_izq, mapaResultado, mapaCotas) && sensores.agentes[1] == '_';
        bool dch_viable = EsAccesibleWalkI(st_dch, mapaResultado, mapaCotas) && sensores.agentes[3] == '_';

        if (izq_viable) { plan.push_back(TURN_SL); plan.push_back(WALK); } 
        else if (dch_viable) { plan.push_back(TURN_SR); plan.push_back(WALK); } 
        else {
          bool salto_viable = EsAccesibleJumpI(st_actual, mapaResultado, mapaCotas) && sensores.agentes[6] == '_';
          if (salto_viable) plan.push_back(JUMP);
          else plan.push_back(TURN_SR);
        }
        hayPlan = true;
        Action a = plan.front();
        plan.pop_front();
        return a;
      }

      // Ejecutar acción siguiente del plan
      Action a = plan.front();
      plan.pop_front();
      if (plan.empty()) hayPlan = false;
      return a;
    }
    return IDLE;
  }

  // ─────────────────────────────────────────────────────────────────────────
  // FASE 4: SINCRONIZACIÓN CON TÉCNICO
  // ─────────────────────────────────────────────────────────────────────────
  // Objetivo: Mirarse a los ojos con el Técnico (enfrente) y ejecutar INSTALL.
  // Después, incrementar índice y volver a FASE 2 para el siguiente tramo.
  // ─────────────────────────────────────────────────────────────────────────
  if (faseNivel5 == 4) {
    // Si nos miramos a los ojos ¡INSTALAR!
    if (sensores.enfrente) {
      tramo_idx++;  // Avanzar al siguiente tramo (ya fue construido)
      faseNivel5 = 2;  // Volver a FASE 2 para siguiente ciclo
      return INSTALL;
    }
    
    // No nos miramos aún → calcular orientación ideal hacia el Técnico
    Paso tech_pos = planTuberiasVec[tramo_idx];
    int dF = tech_pos.fil - sensores.posF;
    int dC = tech_pos.col - sensores.posC;
    Orientacion ideal;

    // Calcular orientación en 8 direcciones hacia el Técnico
    if (dF < 0 && dC == 0) ideal = norte;
    else if (dF < 0 && dC > 0) ideal = noreste;
    else if (dF == 0 && dC > 0) ideal = este;
    else if (dF > 0 && dC > 0) ideal = sureste;
    else if (dF > 0 && dC == 0) ideal = sur;
    else if (dF > 0 && dC < 0) ideal = suroeste;
    else if (dF == 0 && dC < 0) ideal = oeste;
    else if (dF < 0 && dC < 0) ideal = noroeste;
    else ideal = (Orientacion)sensores.rumbo;

    // Si no miramos la dirección ideal, girar hacia ella por el camino más corto
    if (sensores.rumbo != ideal) {
      int diff = (ideal - sensores.rumbo + 8) % 8;
      // Elegir dirección de giro más corta: horario (≤4) o antihorario (>4)
      if (diff <= 4) return TURN_SR;  // Giro horario
      else return TURN_SL;            // Giro antihorario
    }
    
    return IDLE;  // Mirando al Técnico, esperar a que llegue
  }

  return IDLE;
}

int CalcularCosteEnergiaI(Action accion, char terreno_inicio, int altura_inicio, int altura_destino) {
  int coste_base = 1;
  int mod_altura = 0;
  bool aplica_mod_altura = false;
  if (accion == WALK) {
    aplica_mod_altura = false;
    switch (terreno_inicio) {
      case 'A': coste_base = 60; aplica_mod_altura = true; break;
      case 'H': coste_base = 6;  aplica_mod_altura = true; break;
      case 'S': coste_base = 3;  aplica_mod_altura = true; break;
    }
  }else if(accion == JUMP){
    aplica_mod_altura = true;
    switch (terreno_inicio) {
      case 'A': coste_base = 90; break;
      case 'H': coste_base = 10; break;
      case 'S': coste_base = 4; break;
      default:  coste_base = 3; break;
    }
  }else if (accion == TURN_SL || accion == TURN_SR) {
    switch (terreno_inicio) {
      case 'A': coste_base= 5; break;
      case 'H': coste_base= 2; break;
      case 'S': coste_base= 1; break;
    }
  }
  
  if (aplica_mod_altura) {
      int dif = altura_destino - altura_inicio;
      if (dif > 0) mod_altura = 5;
      else if (dif < 0) mod_altura = -2;

      coste_base += mod_altura;
  }
  return coste_base;
}

int Heuristica(const EstadoI &actual, const EstadoI &meta) {
  // Movimiento en 8 direcciones: cota inferior admisible = distancia de Chebyshev.
  return max(abs(actual.site.f - meta.site.f), abs(actual.site.c - meta.site.c));
}

list<Action> A_Star_Ingeniero(EstadoI inicio, EstadoI fin, const vector<vector<unsigned char>> &terreno, const vector<vector<unsigned char>> &altura) {
  priority_queue<NodoI_Astar> frontier; 
  map<EstadoI, int> best_g_cost;
  list<Action> plan;
    
  bool SolutionFound = false;

  NodoI_Astar start_node;
  start_node.estado = inicio;
  start_node.g_cost = 0;
  start_node.f_cost = Heuristica(inicio, fin);
  frontier.push(start_node);

  best_g_cost[inicio] = 0; // Coste de llegar al inicio es 0

  while (!frontier.empty() and !SolutionFound) {
    NodoI_Astar current_node = frontier.top();
    frontier.pop();      
    EstadoI estado_actual = current_node.estado;

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
    vector<Action> acciones = {WALK, JUMP, TURN_SR, TURN_SL};
        
    for (Action acc : acciones) {
      EstadoI nuevo_estado = applyI(acc, estado_actual, terreno, altura);
            
      // Verificamos que la acción haya tenido efecto
      if (!(nuevo_estado == estado_actual) || acc == TURN_SR || acc == TURN_SL) {
                
        int coste_paso = 0;
        char terr_inicio = terreno[estado_actual.site.f][estado_actual.site.c];

        if (acc == WALK || acc == JUMP) {
          int alt_inicio = altura[estado_actual.site.f][estado_actual.site.c];
          int alt_destino = altura[nuevo_estado.site.f][nuevo_estado.site.c];
          coste_paso = CalcularCosteEnergiaI(acc, terr_inicio, alt_inicio, alt_destino);
        } else {
          coste_paso = CalcularCosteEnergiaI(acc, terr_inicio, 0, 0);
        }

        int nuevo_g = current_node.g_cost + coste_paso;
        // SOLO añadimos el hijo si nunca hemos estado ahí, o si hemos encontrado un camino MÁS BARATO
        if (best_g_cost.find(nuevo_estado) == best_g_cost.end() || nuevo_g < best_g_cost[nuevo_estado]) {
                  
          best_g_cost[nuevo_estado] = nuevo_g; // Actualizamos el récord
          int nuevo_f = nuevo_g + Heuristica(nuevo_estado, fin);

          NodoI_Astar child;
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


// ---------------------------------------------------------------------
// MÉTODOS AUXILIARES PARA EL NIVEL 6 (CÓDIGO REFACTORIZADO)
// ---------------------------------------------------------------------

void ComportamientoIngeniero::ChequearReinicioNivel6(int vida_actual) {
    if (vida_inicial == -1 || vida_actual > vida_inicial) {
        vida_inicial = vida_actual;
        niebla_inaccesible.clear();
    plan.clear();
    hayPlan = false;
    plan_temporal.clear();
    planTuberiasVec.clear();
    faseNivel5 = 0;
    faseNivel6 = 0;
    belkanitaPaso1 = true;
    tramo_idx = 0;
    metas_descubiertas = 0;
    meta_f = -1;
    meta_c = -1;
    }
}

bool ComportamientoIngeniero::BuscarNuevaNiebla(const Sensores &sensores, int radio_maximo) {
    int target_f = -1, target_c = -1;
    int min_dist = 999999;

    // Para no dejar al ingeniero atrapado si ESTÁ fuera de la valla, el muro 
    // se coloca en max(radio_maximo, distancia_actual_ingeniero).
    int dist_ingeniero = abs(sensores.posF - sensores.BelPosF) + abs(sensores.posC - sensores.BelPosC);
    int radio_muro = max(radio_maximo, dist_ingeniero);
    // 1. LA VALLA ESTRICTA: Recortamos el mapa
    vector<vector<unsigned char>> mapaAcotado = mapaResultado;
    for (int i = 0; i < mapaAcotado.size(); i++) {
        for (int j = 0; j < mapaAcotado[0].size(); j++) {
            int dist_origen = abs(i - sensores.BelPosF) + abs(j - sensores.BelPosC);
            if (dist_origen > radio_muro) {
                mapaAcotado[i][j] = 'M'; // Convertimos el exterior en un muro impenetrable
            }
        }
    }

    // 2. Buscamos el '?' válido más cercano
    for (int i = 0; i < mapaAcotado.size(); i++) {
        for (int j = 0; j < mapaAcotado[0].size(); j++) {
            // Toda la niebla fuera de la valla ahora es 'M', el 'if' la ignora directamente.
            if (mapaAcotado[i][j] == '?' && niebla_inaccesible.find({i, j}) == niebla_inaccesible.end()) {
                int dist_origen = abs(i - sensores.BelPosF) + abs(j - sensores.BelPosC);
                // Aseguramos matemáticamente que no explore nada más allá de su radio_maximo
                if (dist_origen <= radio_maximo) {
                    int dist_a_mi = abs(i - sensores.posF) + abs(j - sensores.posC);
                    if (dist_a_mi < min_dist) {
                        min_dist = dist_a_mi;
                        target_f = i;
                        target_c = j;
                    }
                }
            }
        }
    }

    if (target_f != -1) {
        EstadoI start, goal;
        start.site.f = sensores.posF; start.site.c = sensores.posC;
        start.site.brujula = (Orientacion)sensores.rumbo; start.zapatillas = tiene_zapatillas;
        goal.site.f = target_f; goal.site.c = target_c;
        
        // ¡ATENCIÓN! Le pasamos el mapaAcotado. El A* NO PUEDE salir de la valla.
        plan = A_Star_Ingeniero(start, goal, mapaAcotado, mapaCotas);
        
        if (plan.empty()) {
            niebla_inaccesible.insert({target_f, target_c});
            return true; // Encontramos niebla pero no podemos llegar. 
        }
        return true; // Plan trazado con éxito
    }
    return false; // No queda niebla útil (Fin de exploración natural)
}

  bool ComportamientoIngeniero::ReplanificarTuberiasDesdeInstalado(const Sensores &sensores) {
    if (planTuberiasVec.empty()) {
      return false;
    }

    const vector<Paso> plan_original = planTuberiasVec;
    int indice_inicio = tramo_idx;
    if (indice_inicio < 0) indice_inicio = 0;
    if (indice_inicio >= static_cast<int>(plan_original.size())) {
      indice_inicio = static_cast<int>(plan_original.size()) - 1;
    }

    for (int indice = indice_inicio; indice >= 0; --indice) {
      EstadoTuberia inicio;
      inicio.site.f = plan_original[indice].fil;
      inicio.site.c = plan_original[indice].col;
      inicio.altura_tuberia = mapaCotas[inicio.site.f][inicio.site.c];

      list<Paso> nuevo_plan = A_Star_Tuberias(inicio, mapaResultado, mapaCotas, sensores.max_ecologico);
      if (nuevo_plan.empty()) {
        continue;
      }

      vector<Paso> nuevo_vector;
      for (int i = 0; i <= indice; ++i) {
        nuevo_vector.push_back(plan_original[i]);
      }

      bool primer_paso = true;
      for (const Paso &paso : nuevo_plan) {
        if (primer_paso) {
          primer_paso = false;
          continue;
        }
        nuevo_vector.push_back(paso);
      }

      if (nuevo_vector.size() <= static_cast<size_t>(indice)) {
        continue;
      }

      planTuberiasVec = nuevo_vector;
      plan_temporal = nuevo_plan;
      tramo_idx = indice;
      hayPlan = false;
      plan.clear();
      list<Paso> plan_visual(nuevo_vector.begin(), nuevo_vector.end());
      VisualizaRedTuberias(plan_visual);
      return true;
    }

    return false;
  }

Action ComportamientoIngeniero::EjecutarConEscudoYEvasion(const Sensores &sensores, Action a) {
    int maxDif = tiene_zapatillas ? 2 : 1;
    
    // 1. ESCUDO ANTI-CAÍDAS
    if (a == WALK) {
        bool frenteLibre = (sensores.superficie[2] != 'P' && sensores.superficie[2] != 'M' && sensores.superficie[2] != 'B');
        int difAltura = abs((int)sensores.cota[2] - (int)sensores.cota[0]);
        if (!frenteLibre || difAltura > maxDif) { plan.clear(); return IDLE; }
    } else if (a == JUMP) {
        bool interLibre = (sensores.superficie[2] != 'P' && sensores.superficie[2] != 'M' && sensores.superficie[2] != 'B');
        bool destLibre = (sensores.superficie[6] != 'P' && sensores.superficie[6] != 'M' && sensores.superficie[6] != 'B');
        int difAltura = abs((int)sensores.cota[6] - (int)sensores.cota[0]);
        if (!interLibre || !destLibre || difAltura > maxDif) { plan.clear(); return IDLE; }
    }

    // 2. EVASIÓN DEL TÉCNICO
    if ((a == WALK && sensores.agentes[2] == 't') || 
        (a == JUMP && sensores.agentes[6] == 't')) {
        
        plan.clear();
        EstadoI st_actual = {ubicacion{sensores.posF, sensores.posC, (Orientacion)sensores.rumbo}, tiene_zapatillas};
        EstadoI st_izq = st_actual; st_izq.site.brujula = (Orientacion)((st_izq.site.brujula + 7) % 8);
        EstadoI st_dch = st_actual; st_dch.site.brujula = (Orientacion)((st_dch.site.brujula + 1) % 8);

        bool izq_viable = EsAccesibleWalkI(st_izq, mapaResultado, mapaCotas) && sensores.agentes[1] == '_';
        bool dch_viable = EsAccesibleWalkI(st_dch, mapaResultado, mapaCotas) && sensores.agentes[3] == '_';

        if (izq_viable) { plan.push_back(TURN_SL); plan.push_back(WALK); } 
        else if (dch_viable) { plan.push_back(TURN_SR); plan.push_back(WALK); } 
        else {
            bool salto_viable = EsAccesibleJumpI(st_actual, mapaResultado, mapaCotas) && sensores.agentes[6] == '_';
            if (salto_viable) plan.push_back(JUMP);
            else plan.push_back(TURN_SR); // Dar vueltas esperando
        }
        Action evasion = plan.front(); plan.pop_front();
        return evasion;
    }
    
    return a;
}
bool ComportamientoIngeniero::NuevaMeta(const vector<vector<unsigned char>> &terreno, int bel_f, int bel_c, int &meta_cercana_f, int &meta_cercana_c){
  bool nuevo = false;
  int n_metas = 0;
  vector<pair<int, int>> coordenadas_metas; // 1. Vector para almacenar las metas
  for (int f = 0; f < terreno.size(); f++) {
        for (int c = 0; c < terreno[0].size(); c++) {
            if (terreno[f][c] == 'U') {
                n_metas++;
                coordenadas_metas.push_back({f, c});
            }
        }
    }
    if(n_metas > metas_descubiertas){
      metas_descubiertas = n_metas;
      // 2. Calculamos cuál coordenada está más cerca del Belkanita
      int min_dist = 999999;
        
      for (auto meta : coordenadas_metas) {
        // Distancia Manhattan
        int dist = abs(meta.first - bel_f) + abs(meta.second - bel_c);
            
        if (dist < min_dist) {
          min_dist = dist;
          meta_cercana_f = meta.first;
          meta_cercana_c = meta.second;
        }
      }
      nuevo = true;
    }
    return nuevo;
}
// ---------------------------------------------------------------------
// LÓGICA PRINCIPAL
// ---------------------------------------------------------------------

/**
 * @brief Comportamiento del ingeniero para el Nivel 6.
 * @param sensores Datos actuales de los sensores.
 * @return Acción a realizar.
 */
Action ComportamientoIngeniero::ComportamientoIngenieroNivel_6(Sensores sensores)
{
    ActualizarMapa(sensores);
    if (sensores.superficie[0] == 'D') tiene_zapatillas = true;

    ChequearReinicioNivel6(sensores.vida);

   
    // =====================================================================
    // FASE 0: EXPLORACIÓN ACOTADA
    // Objetivo: Encontrar la mejor meta y explorar solo dentro de su radio
    // =====================================================================
    if (faseNivel6 == 0) {
      int radio_maximo = 999999;

      // Primero nos dirigimos directamente a la Belkanita, conocida desde el inicio.
      if (belkanitaPaso1) {
        if (sensores.posF == sensores.BelPosF && sensores.posC == sensores.BelPosC) {
          belkanitaPaso1 = false;
          hayPlan = false;
          plan.clear();
        } else {
          if (!hayPlan) {
            EstadoI start, goal;
            start.site.f = sensores.posF;
            start.site.c = sensores.posC;
            start.site.brujula = (Orientacion)sensores.rumbo;
            start.zapatillas = tiene_zapatillas;
            goal.site.f = sensores.BelPosF;
            goal.site.c = sensores.BelPosC;
            goal.site.brujula = (Orientacion)sensores.rumbo;
            goal.zapatillas = tiene_zapatillas;

            plan = BFS_Ingeniero(start, goal, mapaResultado, mapaCotas);
            VisualizaPlan(start.site, plan);
            hayPlan = !plan.empty();
          }

          if (hayPlan && !plan.empty()) {
            Action a = plan.front();
            Action accion_segura = EjecutarConEscudoYEvasion(sensores, a);

            if (accion_segura == IDLE) {
              hayPlan = false;
              plan.clear();
            } else if (accion_segura == a) {
              plan.pop_front();
              if (plan.empty()) {
                hayPlan = false;
                belkanitaPaso1 = false;
              }
            } else {
              hayPlan = true;
            }

            if (sensores.choque || sensores.reset) {
              hayPlan = false;
              plan.clear();
              return IDLE;
            }

            return accion_segura;
          }

          return TURN_SR;
        }
      }
        
      // 1. EVALUAR SI HAY NUEVA META MÁS CERCANA
      if(NuevaMeta(mapaResultado, sensores.BelPosF, sensores.BelPosC, meta_f, meta_c)){
        cout << "Ing: Nueva meta encontrada en (" << meta_f << ", " << meta_c << ")" << endl;
        plan_temporal.clear();
      }

      if (meta_f != -1 && meta_c != -1) {
        radio_maximo = (abs(meta_f - sensores.BelPosF) + abs(meta_c - sensores.BelPosC))+5;
      }
        
        // 2. BUSCAR NIEBLA ÚTIL (si no hay plan de exploración activo)
        if (!hayPlan) {
          // Buscar niebla útil dentro del radio
          bool hay_niebla_util = BuscarNuevaNiebla(sensores, radio_maximo);
          hayPlan = !plan.empty();

          // Si no hay niebla útil y ya tenemos meta: ir a construcción
          if (!hay_niebla_util && meta_f != -1 && meta_c != -1) {
          cout << "Ing: Exploración completada. Mejor meta: (" << meta_f << ", " << meta_c << "). Pasando a FASE 2..." << endl;

          EstadoTuberia inicio;
          inicio.site.f = sensores.BelPosF;
          inicio.site.c = sensores.BelPosC;
          inicio.altura_tuberia = mapaCotas[sensores.BelPosF][sensores.BelPosC];

          plan_temporal = A_Star_Tuberias(inicio, mapaResultado, mapaCotas, sensores.max_ecologico);
          if (!plan_temporal.empty()) {
            VisualizaRedTuberias(plan_temporal);
            planTuberiasVec.assign(plan_temporal.begin(), plan_temporal.end());
            faseNivel6 = 2;
            faseNivel5 = 1;
            tramo_idx = 0;
            hayPlan = false;
            plan.clear();
            return IDLE;
          } else {
            // No ha sido posible generar la red hacia la meta encontrada.
            // Marcamos la meta como no válida para evitar reintentos infinitos
            // y continuamos con la exploración restante.
            cout << "Ing: No ha sido posible planificar tuberias a la meta (" << meta_f << ", " << meta_c << "). Continuo explorando." << endl;
            niebla_inaccesible.insert({meta_f, meta_c});
            meta_f = -1; meta_c = -1;
            hayPlan = false;
            plan.clear();
          }
            }
            else if (!hay_niebla_util) {
              // No hay niebla útil y tampoco tenemos meta: puede ocurrir si marcamos
              // nieblas como inaccesibles por error o por bloqueo temporal. Intentamos
              // limpiar la lista de nieblas inaccesibles y reintentar una vez expandiendo
              // el radio. Si sigue sin encontrar nada, evitamos quedar girando retornando
              // un giro como recurso de emergencia.
              niebla_inaccesible.clear();
              int radio_expand = max(radio_maximo * 2, radio_maximo + 10);
              bool hay_niebla_reintentada = BuscarNuevaNiebla(sensores, radio_expand);
              hayPlan = !plan.empty();
              if (!hay_niebla_reintentada) {
                // Nada reachable: forzamos un giro para salir del estancamiento
                return TURN_SR;
              }
            }
        }
        
        // 3. EJECUTAR LA EXPLORACIÓN CON ESCUDO DE SEGURIDAD
        if (hayPlan && !plan.empty()) {
            Action a = plan.front();
            Action accion_segura = EjecutarConEscudoYEvasion(sensores, a);
            
            // Gestionar resultado de la acción
            if (accion_segura == IDLE) {
                // El escudo bloqueó la acción (precipicio o choque con técnico)
                hayPlan = false;
            } else if (accion_segura != a) {
                // Se activó una evasión (técnico en el camino)
                hayPlan = true;
            } else {
                // Acción ejecutada normalmente
                plan.pop_front();
                if (plan.empty()) hayPlan = false;
            }
            
            if (sensores.choque || sensores.reset) {
                hayPlan = false;
                plan.clear();
                return IDLE;
            }
            return accion_segura;
        }
        
        // Fallback: si no hay nada que hacer, exploramos girando
        return TURN_SR;
    }
    // =====================================================================
    // FASE 2: CONSTRUCCIÓN Y REPLANIFICACIÓN DE EMERGENCIA
    // =====================================================================
    if (faseNivel6 == 2) {
        if (planTuberiasVec.empty()) {
          EstadoTuberia inicio;
          inicio.site.f = sensores.BelPosF;
          inicio.site.c = sensores.BelPosC;
          inicio.altura_tuberia = mapaCotas[sensores.BelPosF][sensores.BelPosC];

          plan_temporal = A_Star_Tuberias(inicio, mapaResultado, mapaCotas, sensores.max_ecologico);
          if (plan_temporal.empty()) {
            cout << "Ing: No se pudo inicializar la red de tuberías. Volviendo a exploración." << endl;
            faseNivel6 = 0;
            return IDLE;
          }

          planTuberiasVec.assign(plan_temporal.begin(), plan_temporal.end());
          VisualizaRedTuberias(plan_temporal);
          faseNivel5 = 1;
          tramo_idx = 0;
        }

        if (sensores.choque || sensores.reset) {
          cout << "Ing: ¡Obstáculo imprevisto en la construcción! Replanificando desde lo ya instalado..." << endl;
          if (!ReplanificarTuberiasDesdeInstalado(sensores)) {
            cout << "Ing: No ha sido posible replanificar. Volviendo a exploración." << endl;
            faseNivel6 = 0;
            hayPlan = false;
            plan.clear();
          }
            return IDLE;
        }

        // Dejamos que el Nivel 5 calcule la ruta a la tubería
        Action accion_n5 = ComportamientoIngenieroNivel_5(sensores);
        
        // Pasamos su acción por nuestro escudo definitivo
        Action accion_segura = EjecutarConEscudoYEvasion(sensores, accion_n5);

        if (accion_segura == IDLE && accion_n5 != IDLE) {
          cout << "Ing: ¡Precipicio fantasma detectado! Replanificando desde lo ya instalado..." << endl;
          if (!ReplanificarTuberiasDesdeInstalado(sensores)) {
            faseNivel6 = 0;
            hayPlan = false;
            plan.clear();
          }
          return IDLE;
        }

        return accion_segura;
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
