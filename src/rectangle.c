#include "rectangle.h"

Rectangle* rectangle_new(int width, int height){
  Rectangle* r = (Rectangle*)malloc(sizeof(Rectangle));
  return r;
}

void rectangle_free(Rectangle* rect){
  free(rect);
  rect = NULL;
}

void rectangle_draw(Rectangle* rect){
  glPushMatrix();
  glScalef(rect->width, rect->height, 1);
  dessinCarre(1);
  glPopMatrix();
}

