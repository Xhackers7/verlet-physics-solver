#include "physics.h"
#include <stdio.h>
#include "settings.h"

VerletObject *p_getVerletObject(double pos[2], double vel[2])
{
    double oldPos[2] = {pos[x] - vel[x], pos[y] - vel[y]};
    VerletObject *obj = malloc(sizeof(VerletObject));
    obj->oldPos[x] = oldPos[x];
    obj->oldPos[y] = oldPos[y];
    obj->newPos[x] = pos[x];
    obj->newPos[y] = pos[y];
    obj->acc[x] = 0.0;
    obj->acc[y] = 0.0;
    return obj;
}

void p_destoryObject(VerletObject *obj)
{
    free(obj);
}

void p_updateObject(VerletObject *obj)
{
    double vel_x = (obj->newPos[x] - obj->oldPos[x]) + obj->acc[x];
    double vel_y = (obj->newPos[y] - obj->oldPos[y]) + obj->acc[y];
    obj->oldPos[x] = obj->newPos[x];
    obj->oldPos[y] = obj->newPos[y];

    if (obj->newPos[y] <= HEIGHT && obj->newPos[y] >= HEIGHT - .1)
        vel_x *= FRICTION;

    obj->newPos[x] += (vel_x);
    obj->newPos[y] += (vel_y);

    if (obj->newPos[x] > WIDTH)
    {
        obj->newPos[x] = WIDTH;
        obj->oldPos[x] += vel_x * BOUNCE;
    }

    else if (obj->newPos[x] < 0)
    {
        obj->newPos[x] = 0 + 0;
        obj->oldPos[x] += vel_x * BOUNCE;
    }

    if (obj->newPos[y] > HEIGHT)
    {
        obj->newPos[y] = HEIGHT;
        obj->oldPos[y] += vel_y * BOUNCE;
    }

    else if (obj->newPos[y] < 0)
    {
        obj->newPos[y] = 0 + 0;
        obj->oldPos[y] += vel_y * BOUNCE;
    }

    obj->acc[x] = 0;
    obj->acc[y] = 0;
}

void p_applyForce(VerletObject *obj, double force[2])
{
    obj->acc[x] = force[x];
    obj->acc[y] = force[y];
}

void p_drawObject(VerletObject *obj)
{
    DrawCircle(obj->newPos[x], obj->newPos[y], RAD, BLACK);
}