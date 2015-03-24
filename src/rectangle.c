#include "rectangle.h"

Rectangle* rectangle_new(float x, float y, int width, int height){
  Rectangle* r = (Rectangle*)malloc(sizeof(Rectangle));
  r->width = width;
  r->height = height;
  r->x = x;
  r->y = y;
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
    dessinCarre(PRIM_FILLED);
  glPopMatrix();
  
  glColor3ub(255,0,0);
  dessinPoint(rect->x, rect->y);
  glColor3ub(0,0,255);
  dessinPoint(rect->x, rect->y + rect->height);
}

Rectangle** rectangle_generateArray(int n){
  Rectangle** array = (Rectangle**)malloc(n*sizeof(Rectangle*));
  return array;
}