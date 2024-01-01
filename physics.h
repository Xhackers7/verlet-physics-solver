#pragma once

#include <raylib.h>
#include <stddef.h>
#include <stdlib.h>

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

typedef struct StickConstraint 
{
    VerletObject *p0, *p1;
    double length
} StickConstraint;


StickConstraint *p_getStickConstraint(VerletObject *p0, VerletObject *p1);
void p_destoryStick(StickConstraint *stick);
void p_correctLength(StickConstraint *stick);
void p_drawStick(StickConstraint *stick);

VerletObject *p_getVerletObject(double pos[2], double vel[2]);
void p_destoryObject(VerletObject *obj);

void p_applyForce(VerletObject *obj, double force[2]);
void p_updateObject(VerletObject *obj);
void p_drawObject(VerletObject *obj);
