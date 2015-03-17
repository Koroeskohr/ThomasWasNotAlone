#include "rectangle.h"
#include "dessinPrimitives.h"

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
  float previousColor[4]
  glGetFloatv(GL_CURRENT_COLOR, previousColor);

  glScalef(rect->width, rect->height);
  glColor3f(rect->color[0],rect->color[1],rect->color[2]);

  dessinCarre(1);

  glColor3f(previousColor[0],previousColor[1],previousColor[2]);



  glPopMatrix();
}
