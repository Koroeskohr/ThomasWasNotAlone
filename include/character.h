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

  Color3f color;

  int grounded;
  int jumping;

  int chrAbove;

} Character;


Character* character_new(float x, float y, int width, int height);

void character_draw(Character* chr, short colorId);
Character** character_generateArray(int n);

void character_free(Character* chr);
void chr_array_free(Character** chrArray, int amount);

extern Color3f BLUE, RED, YELLOW, GREEN, LIGHTGREY;
extern Color3f colors[5];

#endif
