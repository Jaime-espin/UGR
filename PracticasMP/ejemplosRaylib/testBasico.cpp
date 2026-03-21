#include "raylib.h"

struct Par{
    float x, y;
};

void mover(Par & pos, Par vel){
    pos.x += vel.x;
    pos.y += vel.y;
}


void rebotar(Par pos, Par & vel, float radio){
    if ((pos.x >= (GetScreenWidth() - radio)) || (pos.x <= radio))
		    vel.x *= -1.0f;
    if ((pos.y >= (GetScreenHeight() - radio)) || (pos.y <= radio))
		    vel.y *= -1.0f;

}

void actualizar(Par & pos, Par & vel, float radio){
    mover(pos,vel);
    rebotar(pos, vel, radio);
}



int main(void)
{
    // Inicializar modo grafico
    //---------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;
    Color v[4] = {RED, BLUE, MAROON, GREEN};

    InitWindow(screenWidth, screenHeight, "Ejemplo básico raylib");

    Par pos1 = { GetScreenWidth()/2.0f, GetScreenHeight()/2.0f };
    Par vel1 = { 5.0f, 4.0f };

    Par pos2 = pos1;
    Par vel2 = { -5.1f, 4.1f };

    Par pos3 = pos1;
    Par vel3 = { 5.1f, -4.2f };

    Par pos4 = pos1;
    Par vel4 = { -5.1f, -4.1f };


    int radio = 7;

    bool pause = 0;
    int framesCounter = 0;

    SetTargetFPS(30);
    //----------------------------------------------------------

    // Bucle principal
    while (!WindowShouldClose())    // mientras no se cierra ventana o ESC
    {
        // actualizar estado de los datos/objetos
        //-----------------------------------------------------
        if (IsKeyPressed(KEY_SPACE)) 
		pause = !pause;

        if (!pause)
        {
            actualizar(pos1,vel1,radio);
            actualizar(pos2,vel2,radio);
            actualizar(pos3,vel3,radio);
            actualizar(pos4,vel4,radio);

       }
        else framesCounter++;
        //-----------------------------------------------------

        // dibujar
        //-----------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawCircle(pos1.x, pos1.y, radio, v[0]);
            DrawCircle(pos2.x, pos2.y,radio, v[1]);
            DrawCircle(pos3.x, pos3.y,radio, v[2]);
            DrawCircle(pos4.x, pos4.y,radio, v[3]);


            DrawText("PRESIONA LA BARRA PARA PAUSA", 10, GetScreenHeight() - 25, 20, LIGHTGRAY);


            if (pause)// && ((framesCounter/30)%2))
                DrawText("PAUSED", 350, 200, 30, GRAY);

            DrawFPS(10, 10);

        EndDrawing();
        //-----------------------------------------------------
    }

    // cerrar modo grafico
    //---------------------------------------------------------
    CloseWindow();
    //----------------------------------------------------------

    return 0;
}
