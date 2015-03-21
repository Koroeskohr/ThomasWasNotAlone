#include "character.h"

Character* character_new(float x, float y, int width, int height){
  Character* chr = (Character*)malloc(sizeof(Character));
  chr->model = rectangle_new(x, y, width, height);
  chr->acc = vector2(0,-0.1);
  chr->speed = vector2(0, 0);
  chr->pos = vector2(x,y);

  return chr;
}

void character_draw(Character* chr) {
  chr->model->x = chr->pos.x;
  chr->model->y = chr->pos.y;
  rectangle_draw(chr->model);
}


void character_free(Character* chr){
  free(chr->model);
  chr->model = NULL;

  free(chr);
  chr = NULL;
}