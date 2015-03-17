#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>

const int PRIM_FILLED = 1;
const int PRIM_EMPTY = 0;

void dessinCarre(short filled);
void dessinRepere();
void dessinCercle(short nbSubdiv, short filled);