#include "windowManager.h"

void reshape(int winWidth, int winHeight) {
  glViewport(0, 0, winWidth, winHeight);
  glMatrixMode(GL_PROJECTION); //MODELVIEW -> déplacer les objets, caméras, PROJECTION -> gestion des optiques (Zooms, focale, etc)
  glLoadIdentity(); //applique la matrice identité sur la matrice courante
  gluOrtho2D(-250., 250., -250./1.6, 250./1.6); //modifie la matrice projection

  /// TODO : faire en sorte qu'il n'y ait pas de déformation
}

void setVideoMode(int winWidth, int winHeight, const int BIT_PER_PIXEL) {
  if(NULL == SDL_SetVideoMode(winWidth, winHeight, BIT_PER_PIXEL, SDL_OPENGL | SDL_RESIZABLE)) {
    fprintf(stderr, "Impossible d'ouvrir la fenetre. Fin du programme.\n");
    exit(EXIT_FAILURE);
  }
  reshape(winWidth,winHeight);
}

void initWindow(int windowWidth, int windowHeight, const int BIT_PER_PIXEL){
  if(-1 == SDL_Init(SDL_INIT_VIDEO)) {
    fprintf(stderr, "Impossible d'initialiser la SDL : %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }
   
  setVideoMode(windowWidth, windowHeight, BIT_PER_PIXEL);

  SDL_WM_SetCaption("Thomas Is Not Alone", NULL);
}
