#include <raylib.h>
#include <stdio.h>
#include "physics.h"
#include "settings.h"

static VerletObject *points[4];
static StickConstraint *sticks[3];

void simulate()
{
    for (size_t i = 0; i < ARRAY_LEN(points); i++)
    {
        p_applyForce(points[i], GRAVITY);
        p_updateObject(points[i]);
    }
    for (size_t i = 0; i < ARRAY_LEN(sticks); i++)
        p_correctLength(sticks[i]);
}

int main()
{
    InitWindow(WIDTH, HEIGHT, "Something");

    SetTargetFPS(60);

    points[0] = p_getVerletObject((double[]){100, 100}, (double[]){10, 0});
    points[1] = p_getVerletObject((double[]){200, 100}, (double[]){0, 15});
    points[2] = p_getVerletObject((double[]){100, 200}, (double[]){0, 15});
    points[3] = p_getVerletObject((double[]){200, 200}, (double[]){-5, 10});

    sticks[0] = p_getStickConstraint(points[0], points[1]);
    sticks[1] = p_getStickConstraint(points[1], points[3]);
    sticks[2] = p_getStickConstraint(points[3], points[2]);
    // sticks[3] = p_getStickConstraint(points[2], points[0]);
    // sticks[3] = p_getStickConstraint(points[0], points[3]);
    // sticks[4] = p_getStickConstraint(points[1], points[2]);

    bool startSimulation = false;

    while (!WindowShouldClose())
    {
        if (IsKeyDown(KEY_R))
            startSimulation = true;
        else if (IsKeyDown(KEY_S))
            startSimulation = false;

        if (startSimulation)
            simulate();

        BeginDrawing();
        ClearBackground((Color){233, 227, 250, 255});
        for (size_t i = 0; i < ARRAY_LEN(points); i++)
            p_drawObject(points[i]);
        for (size_t i = 0; i < ARRAY_LEN(sticks); i++)
            p_drawStick(sticks[i]);

        EndDrawing();
    }

    CloseWindow();
    for (size_t i = 0; i < ARRAY_LEN(points); i++)
        p_destoryObject(points[i]);
    for (size_t i = 0; i < ARRAY_LEN(sticks); i++)
        p_destoryStick(sticks[i]);
    return 0;
}