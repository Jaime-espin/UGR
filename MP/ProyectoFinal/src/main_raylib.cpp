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

// Agregar las partículas aleatorias con aceleración cero
void ensuciar(int numParticulas, ConjuntoParticulas & c){
    for (int i = 0; i < numParticulas; i++) {
        Particula p=Particula(0);
        p.setAceleracion({0,0});
        c.agregar(p);
    }
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
    ensuciar(numParticulas, habitacion);

    SetTargetFPS(45); // velocidad de la simulación
    //----------------------------------------------------------

    bool continuar = true;

    // bucle principal
    //---------------------------------------------------------
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        if(IsKeyPressed(KEY_ENTER)){
            ensuciar(numParticulas, habitacion);
        }
        if((IsKeyPressed(KEY_RIGHT) && aspirador.getVelocidad().getX()<0)|| IsKeyPressed(KEY_LEFT) && (aspirador.getVelocidad().getX()>0)){
            aspirador.setVelocidad({aspirador.getVelocidad().getX()*-1,aspirador.getVelocidad().getY()});
        }
        if((IsKeyPressed(KEY_DOWN) && aspirador.getVelocidad().getY()<0)|| (IsKeyPressed(KEY_UP) &&  aspirador.getVelocidad().getY()>0)){
            aspirador.setVelocidad({aspirador.getVelocidad().getX(),aspirador.getVelocidad().getY()*-1});
        }

        if(habitacion.size()==0){
            continuar = false;
            aspirador.setVelocidad({0,0});
        }else{
            continuar = true;
            if(aspirador.getVelocidad()==0){
                aspirador.setVelocidad(velAsp);
            }
        }
        if(continuar){
            habitacion.mover(1);
            habitacion.gestionarColisiones();
            aspirador.mover();
            aspirador.rebotar();

            for(int i=0; i<habitacion.size(); i++){
                if(aspirador.colision(habitacion[i])){
                    habitacion.borrar(i);
                }
            }
        }
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
        DrawText("ESC para salir", 50, 10, 20, BLACK);
        DrawText(("Particulas: " + to_string(habitacion.size())).c_str(), GetScreenWidth()-170, 10, 20, SKYBLUE);
        
        if (habitacion.size()==0){
            DrawText("La habitación está limpia", screenWidth/2-120, screenHeight/2, 30, GRAY);
        }
        EndDrawing();
        
        //-----------------------------------------------------
    }

    // cerrar ventana
    //---------------------------------------------------------
    CloseWindow(); 
    //----------------------------------------------------------
}
