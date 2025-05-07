
#include "raylib.h"
#include "Punto2D.h"
#include <iostream>
#include <cmath>

const int screenWidth = 600;
const int screenHeight = 600;
const float  DESP = 4.0;
const float  RADIO = 4.0;
const int MAX = 30;

using namespace std;
void pintaPunto(const Punto2D & p, float radio, Color c) {
    DrawCircle(p.getX(), p.getY(), radio, c);
}


int main(void)
{
    // Initializar ventana y objetos
    //---------------------------------------------------------
    srand(time(0));
    Color paleta[8] = {GREEN, YELLOW, BLACK, RED, BLUE, MAGENTA, PINK, GRAY};
    Punto2D *nube;
    nube = new Punto2D[MAX];
   
    InitWindow(screenWidth, screenHeight, "Modulo de prueba");

      
    Punto2D ref(screenWidth/2.0, screenHeight/2.0);
    SetTargetFPS(10);
    int grados = 3;
    int contador = 1;
    
    double rads = grados * (M_PI/180.0);
    //----------------------------------------------------------
    while (!WindowShouldClose())    
    {
        // actualizar objetos
        //-----------------------------------------------------
 
            for(int i = 0; i < MAX; i++){
                nube[i].rotar(ref, rads);
                nube[i].moverHacia(ref,5.0);
            }
            contador++;
        //-----------------------------------------------------
        // Dibujar
        //-----------------------------------------------------
            
        BeginDrawing();

          ClearBackground(RAYWHITE);
          for(int i = 0; i < MAX; i++)
              pintaPunto(nube[i], RADIO/2, paleta[i%8]);
          
           pintaPunto(ref, 2*RADIO, RED);  
           string s = "Iters: " + to_string(contador);
          DrawText(s.c_str(), 10, 10, 10, BLACK);
            
        EndDrawing();
        //-----------------------------------------------------
    }

    
    //---------------------------------------------------------
    CloseWindow();        
    //----------------------------------------------------------

    delete [] nube;
    return 0;
}
