#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

static const unsigned int BIT_PER_PIXEL = 32;
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;

typedef struct Vector2
{
  float x, y;
} Vector2;

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

void dessinCarre(short filled) {
  if (filled) {
    glBegin(GL_QUADS);
      glVertex2f(-.5, .5);
      glVertex2f(.5, .5);
      glVertex2f(.5, -.5);
      glVertex2f(-.5, -.5);
    glEnd();
  } else {
    glBegin(GL_LINES);
      glVertex2f(-.5, .5);
      glVertex2f(.5, .5);

      glVertex2f(.5, .5);
      glVertex2f(.5, -.5);

      glVertex2f(.5, -.5);
      glVertex2f(-.5, -.5);

      glVertex2f(-.5, -.5);
      glVertex2f(-.5, .5);
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

void dessinCercle(short nbSubdiv, short filled){
  int i;
  float angle;
  if(!filled){
    glBegin(GL_LINE_STRIP);
      for (i = 0; i < nbSubdiv+1; ++i)
      {
        angle = 2*M_PI*i/nbSubdiv;
        glVertex2f( cos(angle), sin(angle) );
      }
    glEnd();
  } else {
    glBegin(GL_TRIANGLE_FAN);
      glVertex2f(0,0);
      for (i = 0; i < nbSubdiv+1; ++i)
      {
        angle = 2*M_PI*i/nbSubdiv;
        glVertex2f( cos(angle), sin(angle) );
      }
    glEnd();
  }
}

int main(int argc, char** argv) {

  unsigned int windowWidth  = 1280;
  unsigned int windowHeight = 720;


  if(-1 == SDL_Init(SDL_INIT_VIDEO)) {
    fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
    return EXIT_FAILURE;
  }
   
  setVideoMode(windowWidth, windowHeight);

  SDL_WM_SetCaption("Thomas Is Not Alone", NULL);

  int loop = 1;
  while(loop) {

    /* temps au début de la boucle */
    Uint32 startTime = SDL_GetTicks();

    ////////////
    // DESSIN //
    ////////////
    
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


    SDL_GL_SwapBuffers();
    ////////////////
    // FIN DESSIN //
    ////////////////
    

    /*
    gérer les appuis longs
     */
    //Uint8* keystate = SDL_GetKeyState(NULL);


    SDL_Event e;
    while(SDL_PollEvent(&e)) {
      if(e.type == SDL_QUIT) {
        loop = 0;
        break;
      }
      
      switch(e.type) { 
        case SDL_VIDEORESIZE:
          windowWidth  = e.resize.w;
          windowHeight = e.resize.h;
          setVideoMode(windowWidth,windowHeight);
          break;

        default:
          break;
      }
    }
    
    Uint32 elapsedTime = SDL_GetTicks() - startTime;
    if(elapsedTime < FRAMERATE_MILLISECONDS) {
      SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
    }
  }
  
  SDL_Quit();
  
  return EXIT_SUCCESS;
}
