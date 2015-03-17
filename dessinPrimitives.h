#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>

typedef struct Vector2
{
  float x, y;
} Vector2;

void dessinCarre(short filled);
void dessinRepere();
void dessinCercle(short nbSubdiv, short filled);