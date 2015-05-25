#ifndef _RECTANGLE_H
#define _RECTANGLE_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include "dessinPrimitives.h"
#include <string.h>
#include <stdlib.h>

typedef struct rectangle
{
  float x, y;
  float width, height;
  GLuint textureId;
} Rectangle;


Rectangle* rectangle_new(float x, float y, int width, int height);



Rectangle** rectangle_generateArray(int n);
void rectangle_draw(Rectangle* rect, int filled);

int rectangle_bindTexture(Rectangle* rect, char* textureRelPath);



void rectangle_free(Rectangle* rect);

#endif
