#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>


#include "windowManager.h"
#include "physics.h"
#include "dessinPrimitives.h"
#include "player.h"
#include "rectangle.h"



int main(int argc, char** argv) {

  unsigned int windowWidth  = 1280;
  unsigned int windowHeight = 720;
  const unsigned int BIT_PER_PIXEL = 32;
  const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;

  initWindow(windowWidth, windowHeight, BIT_PER_PIXEL);

  /* Initialisation du jeu */
  Player* player = player_new();
  player->rects[0]->x = -50;
  player->rects[0]->y = -50;

  player->rects[1]->x = 60;
  player->rects[1]->y = 60;

  player->rects[2]->x = -30;
  player->rects[2]->y = 60;


  //tab de ptrs d'objets soumis à la physique
  //void** physicsables = 

  int loop = 1;
  while(loop) {

    /* temps au début de la boucle */
    Uint32 startTime = SDL_GetTicks();

    ///////////////////////////////////////////////////
    //                    DESSIN                     //
    ///////////////////////////////////////////////////
    
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3ub(255,0,0);
    rectangle_draw(player->rects[0]);
    glColor3ub(0,234,0);
    rectangle_draw(player->rects[1]);
    glColor3ub(0,0,223);
    rectangle_draw(player->rects[2]);


    SDL_GL_SwapBuffers();
    ///////////////////////////////////////////////////
    //                  FIN DESSIN                   //
    ///////////////////////////////////////////////////
    

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
          setVideoMode(windowWidth,windowHeight, BIT_PER_PIXEL);
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
