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

// Niveles avanzados (Uso de búsqueda)
/**
 * @brief Comportamiento del ingeniero para el Nivel 2 (búsqueda).
 * @param sensores Datos actuales de los sensores.
 * @return Acción a realizar.
 */
Action ComportamientoIngeniero::ComportamientoIngenieroNivel_2(Sensores sensores)
{
  // TODO: Implementar búsqueda para el Nivel 2.
  return IDLE;
}

/**
 * @brief Comportamiento del ingeniero para el Nivel 3.
 * @param sensores Datos actuales de los sensores.
 * @return Acción a realizar.
 */
Action ComportamientoIngeniero::ComportamientoIngenieroNivel_3(Sensores sensores)
{
  return IDLE;
}

/**
 * @brief Comportamiento del ingeniero para el Nivel 4.
 * @param sensores Datos actuales de los sensores.
 * @return Acción a realizar.
 */
Action ComportamientoIngeniero::ComportamientoIngenieroNivel_4(Sensores sensores)
{
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
    listaCanalizacionTuberias.push_back({it->fil, it->col, it->op});
    it++;
  }
}
