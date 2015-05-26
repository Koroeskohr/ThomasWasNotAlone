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
#include "input.h"


int main(int argc, char** argv) {

  Game game;
  initGame(&game);

  glPointSize(5); //debug

  GameData gameData;
  initLevel(&gameData, 1);

//  rectangle_bindTexture(gameData.decorArray[0], "1.jpg"); // TODO

  while(game.loop) {
    Uint32 startTime = SDL_GetTicks();

    //                    DESSIN                     //
    glClear(GL_COLOR_BUFFER_BIT);

    switch(game.gameState){
        case menu:
            processMenu(game.menuData);
            break;

        case inGame:
            processGame(&game);
            break;

        case gameEnd:
            processGameEnd(&game);
            break;

        default:
            break;
    }


    SDL_GL_SwapBuffers();
    //                  FIN DESSIN                   //
       
    // gérer les appuis longs
    Uint8* keystate = SDL_GetKeyState(NULL);

    if(keystate[SDLK_LEFT] || keystate[SDLK_q]){
      game.gameData.player->characters[game.gameData.currentChr]->acc.x = -0.1;
    }
    if(keystate[SDLK_RIGHT] || keystate[SDLK_d]){
      game.gameData.player->characters[game.gameData.currentChr]->acc.x = 0.1;
    }


    SDL_Event e;
    while(SDL_PollEvent(&e)) {

      processGlobalInput(&e, &game);

      switch(game.gameState){
        case menu:
          // détection des clicks sur le menu
          processMenuInput(&e, &game);
          break;

        case inGame:
          processInGameInput(&game.gameData, &e);
          break;

        case gameEnd:
          break;
      }
    }
    
    Uint32 elapsedTime = SDL_GetTicks() - startTime;
    if(elapsedTime < game.windowParams.FRAMERATE_MILLISECONDS) {
      SDL_Delay(game.windowParams.FRAMERATE_MILLISECONDS - elapsedTime);
    }
  }
  
  SDL_Quit();
  
  return EXIT_SUCCESS;
}
