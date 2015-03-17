#include "windowManager.h"

void reshape(int winWidth, int winHeight) {
  glViewport(0, 0, winWidth, winHeight);
  glMatrixMode(GL_PROJECTION); //MODELVIEW -> déplacer les objets, caméras, PROJECTION -> gestion des optiques (Zooms, focale, etc)
  glLoadIdentity(); //applique la matrice identité sur la matrice courante
  gluOrtho2D(-250., 250., -250., 250.); //modifie la matrice projection
}

void setVideoMode(int winWidth, int winHeight) {
  if(NULL == SDL_SetVideoMode(winWidth, winHeight, BIT_PER_PIXEL, SDL_OPENGL | SDL_RESIZABLE)) {
    fprintf(stderr, "Impossible d'ouvrir la fenetre. Fin du programme.\n");
    exit(EXIT_FAILURE);
  }
  reshape(winWidth,winHeight);
}
