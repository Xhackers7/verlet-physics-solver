#include <raylib.h>
#include <stdio.h>
#include "physics.h"
#include "settings.h"

static VerletObject *points[2];

void simulatePoints()
{
    for (size_t i = 0; i < ARRAY_LEN(points); i++)
    {
        p_applyForce(points[i], GRAVITY);
        p_updateObject(points[i]);
    }
}

int main()
{
    InitWindow(WIDTH, HEIGHT, "Something");

    SetTargetFPS(60);

    points[0] = p_getVerletObject((double[]){100, 100}, (double[]){5,0});
    points[1] = p_getVerletObject((double[]){200, 100}, (double[]){0,0});

    bool startSimulation = false;

    while (!WindowShouldClose())
    {
        if (IsKeyDown(KEY_R))
            startSimulation = true;
        else if (IsKeyDown(KEY_S))
            startSimulation = false;

        if (startSimulation)
            simulatePoints();

        BeginDrawing();
        ClearBackground((Color){233, 227, 250, 255});
        for (size_t i = 0; i < ARRAY_LEN(points); i++)
            p_drawObject(points[i]);

        EndDrawing();
    }

    CloseWindow();
    for (size_t i = 0; i < ARRAY_LEN(points); i++)
        p_destoryObject(points[i]);
    return 0;
}