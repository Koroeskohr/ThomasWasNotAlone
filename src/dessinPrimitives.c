#include "dessinPrimitives.h"


void dessinCarre(short filled) {
  if (filled) {
    glBegin(GL_QUADS);
      glVertex2f(0, 0);
      glVertex2f(0, 1);
      glVertex2f(1, 1);
      glVertex2f(1, 0);
    glEnd();
  } else {
    glBegin(GL_LINE_STRIP);
      glVertex2f(0, 0);
      glVertex2f(0, -1);
      glVertex2f(1, -1);
      glVertex2f(1, 0);
      glVertex2f(0, 0);
    glEnd();
  }
}

void dessinRepere(){
  glBegin(GL_LINES);
    glColor3ub(255,0,0);
    glVertex2f(0, 0);
    glVertex2f(0, 1);

    glColor3ub(0,255,0);
    glVertex2f(0, 0);
    glVertex2f(1, 0);
  glEnd();
  glColor3ub(255,255,255);
}

void dessinPoint(float x, float y){
  glBegin(GL_POINTS);
    glVertex2f(x,y);
  glEnd();
}

void dessinCercle(short nbSubdiv, short filled){
  int i;
  if(!filled){
    glBegin(GL_LINE_STRIP);
      for (i = 0; i < nbSubdiv+1; ++i)
      {
        float angle = 2*M_PI*i/nbSubdiv;
        glVertex2f( cos(angle), sin(angle) );
      }
    glEnd();
  } else {
    glBegin(GL_TRIANGLE_FAN);
      glVertex2f(0,0);
      for (i = 0; i < nbSubdiv+1; ++i)
      {
        float angle = 2*M_PI*i/nbSubdiv;
        glVertex2f( cos(angle), sin(angle) );
      }
    glEnd();
  }
}