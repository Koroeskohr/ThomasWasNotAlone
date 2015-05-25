#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h> //debug
#include <string.h>

#include "windowManager.h"
#include "physics.h"
#include "player.h"
#include "goal.h"
#include "game.h"
#include "camera.h"


int main(int argc, char** argv) {

  unsigned int windowWidth  = 1280;
  unsigned int windowHeight = 720;
  const unsigned int BIT_PER_PIXEL = 32;
  const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;

  initWindow(windowWidth, windowHeight, BIT_PER_PIXEL);
  glPointSize(5); //debug

  GAMESTATE gameState = menu;

  GameData gameData;
  initLevel(&gameData, 1);

//  rectangle_bindTexture(gameData.decorArray[0], "1.jpg"); // TODO

  int loop = 1;
  while(loop) {
    /* temps au début de la boucle */
    Uint32 startTime = SDL_GetTicks();

    ///////////////////////////////////////////////////
    //                    DESSIN                     //
    ///////////////////////////////////////////////////
    glClear(GL_COLOR_BUFFER_BIT);

    switch(gameState){
        case menu:
            processMenu();
            break;

        case inGame:
            processGame(gameData);
            break;
        case gameEnd:

            break;
        default:
            break;
    }


    SDL_GL_SwapBuffers();
    ///////////////////////////////////////////////////
    //                  FIN DESSIN                   //
    ///////////////////////////////////////////////////
    

    /*
    gérer les appuis longs
     */
    Uint8* keystate = SDL_GetKeyState(NULL);

    if(keystate[SDLK_LEFT] || keystate[SDLK_q]){
      gameData.player->characters[gameData.currentChr]->acc.x = -0.1;
    }
    if(keystate[SDLK_RIGHT] || keystate[SDLK_d]){
      gameData.player->characters[gameData.currentChr]->acc.x = 0.1;
    }


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

        case SDL_KEYDOWN:
          if(e.key.keysym.sym == SDLK_TAB){
            nextCharacter(gameData.player, &gameData.currentChr, gameData.chrAmount);
          }
          if(e.key.keysym.sym == SDLK_SPACE){
            jump(gameData.player->characters[gameData.currentChr]);
          }
        break;

        case SDL_KEYUP:
          if(e.key.keysym.sym == SDLK_LEFT || e.key.keysym.sym == SDLK_RIGHT || e.key.keysym.sym == SDLK_q || e.key.keysym.sym == SDLK_d){
            gameData.player->characters[gameData.currentChr]->acc.x = 0;
            gameData.player->characters[gameData.currentChr]->speed.x = 0;
          }
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
