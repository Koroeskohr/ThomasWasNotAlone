#ifndef _CAMERA_H
#define _CAMERA_H

#include <GL/glu.h>
#include "player.h"

typedef struct Bounds
{
  float min;
  float max;
} Bounds;

Bounds getMinMax(Player* p);

void setCamera(Bounds coords);


#endif