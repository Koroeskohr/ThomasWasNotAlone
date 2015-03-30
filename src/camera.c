#include "camera.h"

/*
  To eventually add : 
  - camera could take acceleration into account 
 */

void setCamera(Vector2 coords){
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(coords.x-250, coords.x+250, coords.y/1.6-250, coords.y/1.6+250);
}