#ifndef _CHARACTER_H
#define _CHARACTER_H


#include <math.h>
#include "vector.h"
#include "rectangle.h"


typedef struct character
{
  Rectangle* model;
  Vector2 acc;
  Vector2 speed;
  Vector2 pos;

  int grounded;
  int jumping;

} Character;


Character* character_new(float x, float y, int width, int height);

void character_draw(Character* chr);


void character_free(Character* chr);

#endif