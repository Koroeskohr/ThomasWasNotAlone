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
#include "file.h"


int main(int argc, char** argv) {

  unsigned int windowWidth  = 1280;
  unsigned int windowHeight = 720;
  const unsigned int BIT_PER_PIXEL = 32;
  const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;

  initWindow(windowWidth, windowHeight, BIT_PER_PIXEL);
  glPointSize(5); //debug

  int i;

  /* Initialisation du jeu */
  GameData gameData = gameData_decode("level1.lvl");

  int nb_chrs = gameData.chrAmount;
  int nb_decor = gameData.decorAmount;
  Player* player = player_new(nb_chrs); //to free

  //init des characters
  player->characters = gameData.chrArray; // to free

  //définition du chr courant
  int currentChr = 0;

  //init des Goal
  Goal** goalArray = gameData.goalArray; //to free

  //init du tableau des décors tangibles
  Rectangle** decorArray = gameData.decorArray; //to free



  /* Fin de l'initialisation du jeu */

  int loop = 1;
  while(loop) {

    /* temps au début de la boucle */
    Uint32 startTime = SDL_GetTicks();

    ///////////////////////////////////////////////////
    //                    DESSIN                     //
    ///////////////////////////////////////////////////
    
    glClear(GL_COLOR_BUFFER_BIT);

    setCamera(player->characters[currentChr]->pos);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    characterMovement(player->characters[currentChr]);
    applyGravity(player);
    applyMovementFromSpeed(player, decorArray, 2);


    //printf("pos x %f y %f speed x %f y %f\n", player->characters[currentChr]->pos.x,player->characters[currentChr]->pos.y, player->characters[currentChr]->speed.x,player->characters[currentChr]->speed.y);
    /// TODO : fonction pour dessiner chaque ensemble d'elements
    glColor3ub(255,255,255);
    for(i=0; i < nb_decor; ++i){
      rectangle_draw(decorArray[i], PRIM_FILLED); //rajouter une délégation pour le décor ?
    }

    for(i=0; i < nb_chrs; ++i){
      character_draw(player->characters[i], i);
    }

    glColor3ub(255,255,255);
    for(i = 0; i < nb_chrs; ++i){
      goal_draw(goalArray[i]);
    }
    
    if(isGameWon(player, goalArray)){
      player->characters[0]->model->width = 200;
    }

    SDL_GL_SwapBuffers();
    ///////////////////////////////////////////////////
    //                  FIN DESSIN                   //
    ///////////////////////////////////////////////////
    

    /*
    gérer les appuis longs
     */
    Uint8* keystate = SDL_GetKeyState(NULL);

    if(keystate[SDLK_LEFT]){
      player->characters[currentChr]->acc.x = -0.1;
    }
    if(keystate[SDLK_RIGHT]){
      player->characters[currentChr]->acc.x = 0.1;
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
          if(e.key.keysym.sym == SDLK_LSHIFT){
            player->characters[currentChr]->speed.x = 0;
            currentChr += 1;
            currentChr = currentChr % nb_chrs;
          }
          if(e.key.keysym.sym == SDLK_SPACE){
            jump(player->characters[currentChr]);
          }
        break;

        case SDL_KEYUP:
          if(e.key.keysym.sym == SDLK_LEFT || e.key.keysym.sym == SDLK_RIGHT){
            player->characters[currentChr]->acc.x = 0;
            player->characters[currentChr]->speed.x = 0;
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
