#ifndef _INPUT_H
#define _INPUT_H

#include <SDL/SDL.h>
#include "game.h"
#include "windowManager.h"
#include "physics.h"

void processGlobalInput(SDL_Event* e, Game* game);
void processMenuInput(SDL_Event* e, Game* game);
void processInGameInput(GameData* gameData, SDL_Event* e);



#endif
