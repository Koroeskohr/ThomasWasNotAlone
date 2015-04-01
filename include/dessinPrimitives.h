#ifndef _DESSINPRIMITIVES_H
#define _DESSINPRIMITIVES_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>


#define PRIM_FILLED 1
#define PRIM_EMPTY 0

typedef struct Color3f {
    float r, g, b;
} Color3f;

void dessinCarre(short filled);
void dessinRepere();
void dessinCercle(short nbSubdiv, short filled);
void dessinPoint(float x, float y);

void setColor(Color3f color);

#endif
