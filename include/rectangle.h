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
  int top, right, bottom, left;

} Rectangle;


Rectangle* rectangle_new(int width, int height);
void rectangle_free(Rectangle* rect);
void rectangle_draw(Rectangle* rect);

#endif