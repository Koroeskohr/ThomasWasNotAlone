#ifndef _GAME_H
#define _GAME_H

#include "physics.h"
#include "rectangle.h"
#include "goal.h"
#include "character.h"

typedef struct gameData
{
  int chrAmount;
  int decorAmount;
  Character** chrArray;
  Goal** goalArray;
  Rectangle** decorArray;
} GameData;

int isGameWon(Player* p, Goal** goalArray);


#endif