#ifndef _PHYSICS_H
#define _PHYSICS_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include "rectangle.h"

typedef struct Vector2
{
  float x, y;
} Vector2;

typedef Vector2 Acceleration;
typedef Vector2 Speed;
typedef Vector2 Position;

int rectangle_collision(Rectangle* r1, Rectangle* r2);

#endif