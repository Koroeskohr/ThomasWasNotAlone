#ifndef _PLAYER_H
#define _PLAYER_H

#include "rectangle.h"
#include "physics.h"


typedef struct player
{
  Rectangle* players[3];
} Player;

Player* player_new();

void moveTo(Rectangle* player, Vector2 movement);

#endif