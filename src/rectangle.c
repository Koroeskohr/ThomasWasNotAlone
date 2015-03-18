#include "rectangle.h"

Rectangle* rectangle_new(int width, int height){
  Rectangle* r = (Rectangle*)malloc(sizeof(Rectangle));
  r->width = width;
  r->height = height;
  return r;

}

void rectangle_free(Rectangle* rect){
  free(rect);
  rect = NULL;
}

void rectangle_draw(Rectangle* rect){
  glPushMatrix();
  glTranslatef(rect->x, rect->y, 0);

  glScalef(rect->width, rect->height, 1);
  dessinCarre(1);
  glPopMatrix();
}

