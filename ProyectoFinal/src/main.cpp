#include "raylib.h"
#include "ConjuntoParticulas.hpp"
#include "params.hpp"
#include "util.hpp"
#include <cmath>
#include <iostream>

const int screenWidth = MAX_X;
const int screenHeight = MAX_Y;


using namespace std;

void pintaPunto(const Particula & p, Color c) {
    DrawCircle(p.getPosicion().getX(), p.getPosicion().getY(), p.getRadio(), c);
}

int main(int argc, char *argv[]) {

    if (argc != 3) {
        cout << "Uso: " << argv[0] << " <radio_aspirador> <num_particulas>" << endl;
        return 1;
    }

    int radioAsp = atoi(argv[1]);
    int numParticulas = atoi(argv[2]);
    
    if (radioAsp <= 0 || numParticulas < 0) {
        cout << "Error: El radio debe ser positivo y el número de partículas debe ser no negativo." << endl;
        return 1;
    }

    // activación de ventana gráfica
    //---------------------------------------------------------
    InitWindow(screenWidth, screenHeight, "Modulo de prueba");

    // creación de objetos
    float centroY = screenHeight / 2.0;
    float centroX = screenWidth / 2.0;
    //---------------------------------------------------------
    // Creación del aspirador con el radio especificado
    Vector2D posAsp(MIN_X+radioAsp, MIN_Y+radioAsp);
    Vector2D velAsp(aleatorio(-MAX_VEL, MAX_VEL), aleatorio(-MAX_VEL, MAX_VEL));
    Vector2D acelAsp(0, 0);
    Particula aspirador(posAsp, velAsp, acelAsp, radioAsp, 1);
    // Crear conjunto de partículas con aceleración cero
    ConjuntoParticulas habitacion(0);
    
    // Agregar las partículas aleatorias con aceleración cero
    for (int i = 0; i < numParticulas; i++) {
        // Crear posición aleatoria
        Vector2D pos(aleatorio(MIN_X, MAX_X), aleatorio(MIN_Y, MAX_Y));
        
        // Crear velocidad aleatoria
        Vector2D vel(aleatorio(-MAX_VEL, MAX_VEL), aleatorio(-MAX_VEL, MAX_VEL));
        
        // Aceleración cero
        Vector2D acel(0, 0);
        
        // Radio aleatorio
        double radio = aleatorio(MIN_R, MAX_R);
        
        // Crear partícula y agregarla al conjunto
        Particula p(pos, vel, acel, radio, 0);
        habitacion.agregar(p);
    }

    SetTargetFPS(45); // velocidad de la simulación
    //----------------------------------------------------------

    bool continuar = true;
    

    // bucle principal
    //---------------------------------------------------------
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        habitacion.mover(1);
        aspirador.mover();
        aspirador.rebotar();
        //-----------------------------------------------------
        // pintar los objetos
        //-----------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);
        // Dibujar todas las partículas
        for (int i = 0; i < habitacion.getNumeroParticulas(); i++) {
            pintaPunto(habitacion[i], BLUE);
        }
        pintaPunto(aspirador, RED);
        DrawText("ESC para salir", 60, 10, 20, BLACK);
        
        
        EndDrawing();
        
        //-----------------------------------------------------
    }

    // cerrar ventana
    //---------------------------------------------------------
    CloseWindow(); 
    //----------------------------------------------------------

    
    return 0;
}
