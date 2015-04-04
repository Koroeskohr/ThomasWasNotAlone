#include "game.h"

int isGameWon(Player* p, Goal** goalArray){
  int i;
  int won = 1;
  for (i = 0; i < p->n; ++i)
  {
    if(!rectangle_collision(p->characters[i]->model, goalArray[i]->model)){
      won = 0;
      break;
    }
  }
  return won;
}

void nextCharacter(Player* p, int* currentChr, int nb_chrs){
  p->characters[*currentChr]->speed.x = 0;
  p->characters[*currentChr]->acc.x = 0;
  *currentChr += 1;
  *currentChr = *currentChr % nb_chrs;
}
