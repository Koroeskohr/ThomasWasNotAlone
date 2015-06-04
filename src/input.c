#include "input.h"

void processGlobalInput(SDL_Event* e, Game* game){
    switch(e->type){
        case SDL_VIDEORESIZE:
            setVideoMode(e->resize.w, e->resize.h, game->windowParams.BIT_PER_PIXEL);
            break;
        case SDL_QUIT:
            game->loop = 0;
            break;
        default:
            break;
    }
}

void processMenuInput(SDL_Event* e, Game* game){
    float xGl, yGl;
    int i;

    switch(e->type){
        case SDL_MOUSEBUTTONDOWN:
        xGl = -250. + 500. * (float)e->button.x/(float)game->windowParams.windowWidth;
        yGl = -(-156. + 312.*(float)e->button.y/(float)game->windowParams.windowHeight);
        for(i = 0 ; i < 3 ; ++i){
            if(isPointInRectangle(xGl, yGl, game->menuData.niveaux[i])) {
                game->gameState = inGame;
                initLevel(&game->gameData, i+1);
                break;
            }
        }

        break;
    }
}

void processInGameInput(GameData* gameData, SDL_Event* e){
    switch(e->type) {

      case SDL_KEYDOWN:
        if(e->key.keysym.sym == SDLK_TAB){
          nextCharacter(gameData->player, &gameData->currentChr, gameData->chrAmount);
        }
        if(e->key.keysym.sym == SDLK_SPACE){
          jump(gameData->player->characters[gameData->currentChr]);
        }

      break;

      case SDL_KEYUP:
        if(e->key.keysym.sym == SDLK_LEFT || e->key.keysym.sym == SDLK_RIGHT || e->key.keysym.sym == SDLK_q || e->key.keysym.sym == SDLK_d){
          gameData->player->characters[gameData->currentChr]->acc.x = 0;
          gameData->player->characters[gameData->currentChr]->speed.x = 0;
        }
        break;

      default:
        break;
    }
}
