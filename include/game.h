#ifndef _GAME_H
#define _GAME_H

#include <stdio.h>

#include "physics.h"
#include "rectangle.h"
#include "character.h"
#include "goal.h"
#include "player.h"
#include "camera.h"

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

typedef enum  {menu = 0, inGame = 1, gameEnd = 2} GAMESTATE;

int isGameWon(Player* p, Goal** goalArray);
void nextCharacter(Player* p, int* currentChr, int nb_chrs);

int initLevel(GameData* gameData, int level);

GameData gameData_decode();

void processGame(GameData gameData);



#endif
