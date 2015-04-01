#include "character.h"

Color3f CHRCOLORS[5] = {{0,0,1}, {1,0,0}, {0,1,1}, {0,1,0}, {0.8, 0.8, 0.8}};

Character* character_new(float x, float y, int width, int height){
  Character* chr = (Character*)malloc(sizeof(Character));
  chr->model = rectangle_new(x, y, width, height);
  chr->acc = vector2(0, -0.2);
  chr->speed = vector2(0, 0);
  chr->pos = vector2(x,y);
  chr->grounded = 0;
  chr->jumping = 0;

  return chr;
}

void character_draw(Character* chr, short colorId) {
  setColor(CHRCOLORS[colorId]);
  rectangle_draw(chr->model, PRIM_FILLED);
}

Character** character_generateArray(int n){
  Character** chrArray = (Character**)malloc(n*sizeof(Character*));
  return chrArray;
}


void character_free(Character* chr){
  free(chr->model);
  chr->model = NULL;

  free(chr);
  chr = NULL;
}


