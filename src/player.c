#include "player.h"

Player* player_new(int n){
  Player* p = (Player*) malloc(sizeof(Player));
  p->n = n;

  return p;
}

void player_free(Player* p) {
  int i = 0;
  for(i=0 ; i < p->n ; i++){
    character_free(p->characters[i]);
  }
  free(p->characters);
  p->characters = NULL;
  free(p);
  p = NULL;
}
