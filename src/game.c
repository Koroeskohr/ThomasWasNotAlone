#include "game.h"

int isGameWon(Player* p, Goal** goalArray){
  int i;
  int won = 1;
  for (i = 0; i < p->n; ++i)
  {
    printf("not won\n");
    if(!rectangle_collision(p->characters[i]->model, goalArray[i]->model)){
      won = 0;
      break;
    }


  }

  return won;
}