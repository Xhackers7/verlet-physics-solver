#include "physics.h"
#include <stdio.h>
#include "settings.h"
#include <math.h>

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
    double vel_x = (obj->newPos[x] - obj->oldPos[x]);
    double vel_y = (obj->newPos[y] - obj->oldPos[y]);

    if (obj->newPos[y] <= HEIGHT && obj->newPos[y] >= HEIGHT - .1)
        vel_x *= FRICTION;

    obj->oldPos[x] = obj->newPos[x];
    obj->oldPos[y] = obj->newPos[y];

    obj->newPos[x] += (vel_x);
    obj->newPos[y] += (vel_y);

    obj->newPos[x] += obj->acc[x];
    obj->newPos[y] += obj->acc[y];

    if (obj->newPos[x] > WIDTH)
    {
        obj->newPos[x] = WIDTH;
        obj->oldPos[x] = obj->newPos[x] + vel_x * BOUNCE;
    }

    else if (obj->newPos[x] < 0)
    {
        obj->newPos[x] = 0 + 0;
        obj->oldPos[x] = obj->newPos[x] + vel_x * BOUNCE;
    }

    if (obj->newPos[y] > HEIGHT)
    {
        obj->newPos[y] = HEIGHT;
        obj->oldPos[y] = obj->newPos[y] + vel_y * BOUNCE;
    }

    else if (obj->newPos[y] < 0)
    {
        obj->newPos[y] = 0 + 0;
        obj->oldPos[y] = obj->newPos[y] + vel_y * BOUNCE;
    }

    obj->acc[x] = 0;
    obj->acc[y] = 0;
}

void p_applyForce(VerletObject *obj, double force[2])
{
    obj->acc[x] = force[x];
    obj->acc[y] = force[y];
}

StickConstraint *p_getStickConstraint(VerletObject *p0, VerletObject *p1)
{
    double dx = p0->newPos[x] - p1->newPos[x];
    double dy = p0->newPos[y] - p1->newPos[y];
    double dist = sqrt(dx * dx + dy * dy);
    
    StickConstraint *stick = malloc(sizeof(stick));
    stick->p0 = p0;
    stick->p1 = p1;
    stick->length=dist;
    return stick;
}

void p_correctLength(StickConstraint *stick)
{   
    VerletObject *p0 = stick->p0;
    VerletObject *p1 = stick->p1;

    double dx = p1->newPos[x] - p0->newPos[x];
    double dy = p1->newPos[y] - p0->newPos[y];
    double dist = sqrt(dx * dx + dy * dy);
    double diff = stick->length-dist;
    double offset_percent = diff/dist/2;

    p0->newPos[x] -= dx*offset_percent;
    p0->newPos[y] -= dy*offset_percent;
        
    p1->newPos[x] += dx*offset_percent;
    p1->newPos[y] += dy*offset_percent;
    
}

void p_drawStick(StickConstraint *stick)
{
    DrawLine(stick->p0->newPos[x], stick->p0->newPos[y], stick->p1->newPos[x], stick->p1->newPos[y], BLACK);
}

void p_destoryStick(StickConstraint *stick)
{
    free(stick);
}

void p_drawObject(VerletObject *obj)
{
    DrawCircle(obj->newPos[x], obj->newPos[y], RAD, BLACK);
}