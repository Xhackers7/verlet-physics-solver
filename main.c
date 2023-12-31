#include <raylib.h>
#include <stdio.h>
#include "physics.h"
#include "settings.h"


int main()
{
    InitWindow(WIDTH, HEIGHT, "Something");

    SetTargetFPS(144);
    
    p_createVerletObject((double[]){20+100, 300}, (double[]){-11, 100});
    
    bool startSimulation = false;
      
    while (!WindowShouldClose())
    {
        if (IsKeyDown(KEY_R)) {
            startSimulation = true;
        }
        BeginDrawing();
        ClearBackground((Color){233, 227, 250, 255});
        if (startSimulation)
            p_updateObjects();
        EndDrawing();
    }

    CloseWindow();
    return 0;
    
}