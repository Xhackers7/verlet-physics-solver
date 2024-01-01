#pragma once

#include <raylib.h>
#include <stddef.h>
#include <stdlib.h>

#define INITIAL_CAPACITY 50
#define GROWTH_FACTOR 1.5
#define ARRAY_LEN(arr) (sizeof((arr)) / sizeof((arr[0])))

typedef enum
{
    x,
    y
} Pos;

typedef struct VerletObject
{
    double oldPos[2];
    double newPos[2];
    double acc[2];
} VerletObject;



VerletObject *p_getVerletObject(double pos[2], double vel[2]);
void p_destoryObject(VerletObject *obj);

void p_applyForce(VerletObject *obj, double force[2]);
void p_updateObject(VerletObject *obj);
void p_drawObject(VerletObject *obj);
