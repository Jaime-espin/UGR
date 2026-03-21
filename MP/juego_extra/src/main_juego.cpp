#include <iostream>
#include <cassert>
#include <cmath>
#include "util.hpp"
#include "params.hpp"
#include "Particula.hpp"
#include "raylib.h"
#include "escudo.hpp"
using namespace std;


int main(){
    const int screenWidth = MAX_X;
    const int screenHeight = MAX_Y;
    Color v[4] = {RED, BLUE, MAROON, GREEN};
    InitWindow(screenWidth, screenHeight, "Juego de prueba");
    Particula p;
    Escudo e;
    const float velocidadEscudo = 10.0f;
    Vector2D inicio={GetScreenWidth()/2.0f, GetScreenHeight()/2.0f};
    p.setPosicion(inicio);
    p.setVelocidad({0,-5});
    Vector2D ace={aleatorio(-5.0,50.0),-1.0};
    p.setAceleracion(ace);

    bool pause = false;
    bool loose = false;
    bool rebota = false;
    int puntos=0;

    SetTargetFPS(30);

    // Bucle principal
    while (!WindowShouldClose())    // mientras no se cierra ventana o ESC
    {
        // actualizar estado de los datos/objetos
        //-----------------------------------------------------
        if (IsKeyPressed(KEY_SPACE)) {
		    pause = !pause;
        }

        if (!pause && !loose){
            p.mover();
            p.rebotar();
            if (IsKeyDown(KEY_LEFT)) 
                e.mover(-velocidadEscudo);
            if (IsKeyDown(KEY_RIGHT)) 
                e.mover(velocidadEscudo);
            p.rebotarEscudo(e, rebota);
            if(rebota){
                puntos++;
            }

            if(p.getPosicion().getY()+p.getRadio()>=MAX_Y){
                loose=true;
            }
            

       }
        //-----------------------------------------------------

        // dibujar
        //-----------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawCircle(p.getPosicion().getX(), p.getPosicion().getY(), p.getRadio(), v[0]);
            DrawRectangle(e.getPosicion().getX() - e.getAncho()/2, e.getPosicion().getY()-10, e.getAncho(), 10, v[3]);

            DrawText("PRESIONA LA BARRA PARA PAUSA", 10, GetScreenHeight() - 25, 20, LIGHTGRAY);
            DrawText(("Puntos: " + to_string(puntos)).c_str(), GetScreenWidth()-150, 10, 20, SKYBLUE);

            if (pause)
                DrawText("PAUSED", screenWidth/2, screenHeight/2, 30, GRAY);
            
            if (loose)
                DrawText("GAME OVER", screenWidth/2, screenHeight/2, 30, RED);

        EndDrawing();
        //-----------------------------------------------------
    }

    // cerrar modo grafico
    //---------------------------------------------------------
    CloseWindow();
    //----------------------------------------------------------
}