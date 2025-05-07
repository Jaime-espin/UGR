
#include "raylib.h"
#include "Punto2D.h"
#include <cmath>
#include <iostream>

const int screenWidth = 1200;
const int screenHeight = 800;

const float RADIO = 7.0;


using namespace std;

void pintaPunto(const Punto2D & p, Color c) {
    DrawCircle(p.getX(), p.getY(), RADIO, c);
}


void pintaLinea(const Punto2D & p1, const Punto2D & p2, Color c){
    DrawLine(p1.getX(), p1.getY(), p2.getX(), p2.getY(), c);
    
}


int main(void) {
    // activación de ventana gráfica
    //---------------------------------------------------------
    InitWindow(screenWidth, screenHeight, "Modulo de prueba");

    // creación de objetos
    float centroY = screenHeight / 2.0;
    float centroX = screenWidth / 2.0;
    //---------------------------------------------------------
    Punto2D bola1(centroX - 50, centroY);
    Punto2D bola2(centroX, centroY + 50);
    
    Punto2D *fija = &bola1;
    Punto2D *movil = &bola2;
    Punto2D *aux;
    
    SetTargetFPS(45); // velocidad de la simulación
    //----------------------------------------------------------

    int grados = 3;
    
    double rads = grados * (M_PI/180.0);
    bool continuar = true;
    

    // bucle principal
    //---------------------------------------------------------
    int tick = 0;
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        
          movil->rotar(*fija, rads);
          
          if (tick > (360 / 5)){
              
              fija->mover(1.5, 1.5);
              aux = movil;
              movil = fija;
              fija = aux;
              tick = 0;
          }

        //-----------------------------------------------------
        // pintar los objetos
        //-----------------------------------------------------
        BeginDrawing();

         ClearBackground(RAYWHITE);
 
         pintaLinea(*fija, *movil, BLACK);
         pintaPunto(*fija, RED);
         pintaPunto(*movil, BLUE);
         string s = "ticks: " + to_string(tick);
         DrawText(s.c_str(), 10, 10, 10, BLACK);
         DrawText("ESC para salir", 60, 10, 20, BLACK);
        
        
        EndDrawing();
        
        tick++;
        //-----------------------------------------------------
    }

    // cerrar ventana
    //---------------------------------------------------------
    CloseWindow(); 
    //----------------------------------------------------------

    
    return 0;
}
