#ifndef _DESSINPRIMITIVES_H
#define _DESSINPRIMITIVES_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>


#define PRIM_FILLED 1
#define PRIM_EMPTY 0



void dessinCarre(short filled);
void dessinRepere();
void dessinCercle(short nbSubdiv, short filled);

#endif