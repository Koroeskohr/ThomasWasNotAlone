#include "camera.h"

Bounds getMinMax(Player* p){
  float min = 10000, max = -10000;
  int i;

  for(i = 0; i < p->n; ++i){
    if(p->characters[i]->model->x + p->characters[i]->model->width > max)
      max = p->characters[i]->model->x + p->characters[i]->model->width;
    if(p->characters[i]->model->x < min)
      min = p->characters[i]->model->x;
  }

  Bounds m;
  m.max = max;
  m.min = min;
  return m;
}

void setCamera(Bounds coords){
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  int width = coords.max - coords.min;
  if (width < 400)
  {
    int toAdd = 400 - width;
    coords.max += toAdd/2.;
    coords.min -= toAdd/2.;
  }
  gluOrtho2D(coords.min, coords.max, coords.min/1.6, coords.max/1.6);
}