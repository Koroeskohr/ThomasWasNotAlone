#ifndef _RECTANGLE_H
#define _RECTANGLE_H

#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include "dessinPrimitives.h"

typedef struct rectangle
{
  float x, y;
  float width, height;
} Rectangle;


Rectangle* rectangle_new(float x, float y, int width, int height);



Rectangle** rectangle_generateArray(int n);
void rectangle_draw(Rectangle* rect);




void rectangle_free(Rectangle* rect);

#endif