#include "rectangle.h"

Rectangle* rectangle_new(int width, int height){
  Rectangle* r = (Rectangle*)malloc(sizeof(Rectangle));
  return r;
}

void rectangle_free(Rectangle* rect){
  free(rect);
  rect = NULL;
}