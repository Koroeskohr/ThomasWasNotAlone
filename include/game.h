#ifndef _GAME_H
#define _GAME_H

#include <stdio.h>

#include "physics.h"
#include "rectangle.h"
#include "character.h"
#include "goal.h"
#include "player.h"
#include "camera.h"
#include "windowManager.h"



typedef struct gameData
{
  int chrAmount;
  int decorAmount;
  Character** chrArray;
  Goal** goalArray;
  Rectangle** decorArray;
  Player* player;
  int currentChr;
} GameData;

typedef struct menuData
{
    Rectangle* titre;
    Rectangle* niveaux[3];
} MenuData;

typedef enum  {menu = 0, inGame = 1, gameEnd = 2} GAMESTATE;

typedef struct game {
    GameData gameData;
    MenuData menuData;
    WindowParams windowParams;
    int loop;
    GAMESTATE gameState;
    Rectangle* gameEndScreen;
    Uint32 winTime;
} Game;

void initGame(Game* game);

int isGameWon(Player* p, Goal** goalArray);
void nextCharacter(Player* p, int* currentChr, int nb_chrs);

int initLevel(GameData* gameData, int level);
void initMenu(MenuData*);

GameData gameData_decode();

void processGame(Game *game);
void processMenu();
void processGameEnd(Game *game);


#endif
