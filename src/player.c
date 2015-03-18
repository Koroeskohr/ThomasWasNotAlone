#include "player.h"

Player* player_new(){
  Player* p = (Player*) malloc(sizeof(Player));

  p->players[0] = rectangle_new(20,16);
  p->players[1] = rectangle_new(12,10);
  p->players[2] = rectangle_new(25,25);

  return p;
}


void moveTo(Rectangle* player, Vector2 movement){
  player->x += movement.x;
  player->y += movement.y;
}