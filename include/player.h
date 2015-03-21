#ifndef _PLAYER_H
#define _PLAYER_H

#include "vector.h"
#include "character.h"


typedef struct player
{
  int n;
  Character** characters;

} Player;

Player* player_new(int n);
void player_free();

void move(Player* p, Rectangle** decor);



#endif