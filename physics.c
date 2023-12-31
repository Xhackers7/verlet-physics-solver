#include "physics.h"
#include <stdio.h>
#include "settings.h"

VerletObject *p_createVerletObject(double pos[2], double vel[2])
{
    double oldPos[2] = {pos[x] - vel[x], pos[y] - vel[y]};
    VerletObject *obj = malloc(sizeof(VerletObject));
    obj->oldPos[x] = oldPos[x];
    obj->oldPos[y] = oldPos[y];
    obj->newPos[x] = pos[x];
    obj->newPos[y] = pos[y];

    if (objList == NULL)
    {
        capacity = INITIAL_CAPACITY;
        objList = malloc(capacity * sizeof(VerletObject *));
    }
    else if (lastIndex >= capacity)
    {
        capacity *= GROWTH_FACTOR;
        objList = realloc(objList, capacity * sizeof(VerletObject *));
    }

    objList[lastIndex++] = obj;
    return obj;
}

void p_updateObjects()
{
    for (size_t i = 0; i < lastIndex; i++)
    {
        p_updateObject(objList[i]);
        p_drawObject(objList[i]);
    }
}

void p_updateObject(VerletObject *obj)
{
    double vel_x = FRICTION * (obj->newPos[x] - obj->oldPos[x]);
    double vel_y = FRICTION * (obj->newPos[y] - obj->oldPos[y]);
    obj->oldPos[x] = obj->newPos[x];
    obj->oldPos[y] = obj->newPos[y];

    obj->newPos[x] += vel_x;
    obj->newPos[y] += vel_y + GRAVITY;

    if (obj->newPos[x] > WIDTH - 8)
    {
        obj->newPos[x] = WIDTH - 8;
        obj->oldPos[x] += vel_x *BOUNCE;
    }
    else if (obj->newPos[x] < 0 + 8)
    {
        obj->newPos[x] = 0 + 8;
        obj->oldPos[x] += vel_x *BOUNCE;
    }

    if (obj->newPos[y] > HEIGHT - 8)
    {
        obj->newPos[y] = HEIGHT - 8;
        obj->oldPos[y] += vel_y*BOUNCE;
    }
    else if (obj->newPos[y] < 0 + 8)
    {
        obj->newPos[y] = 0 + 8;
        obj->oldPos[y] += vel_y*BOUNCE;
    }
}

void p_drawObject(VerletObject *obj)
{
    DrawCircle(obj->newPos[x], obj->newPos[y], 8, BLACK);
}