#include "player.h"

Player* player_new(){
  Player* p = (Player*) malloc(sizeof(Player));

  p->rects[0] = rectangle_new(15,35);
  p->rects[1] = rectangle_new(12,25);
  p->rects[2] = rectangle_new(20,20);

  return p;
}

void player_free(Player* p) {
  int i = 0;
  for(i=0;i<3;i++){
    free(p->rects[i]);
    p->rects[i] = NULL;
  }
  free(p);
  p = NULL;
}

void moveTo(Rectangle* player, Vector2 movement){
  player->x += movement.x;
  player->y += movement.y;
}