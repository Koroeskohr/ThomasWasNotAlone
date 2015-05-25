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

int initLevel(GameData* gameData, int level){
    char filename[150];
    sprintf(filename, "level%d.lvl", level);

    *gameData = gameData_decode(filename);

    gameData->player = player_new(gameData->chrAmount);
    gameData->player->characters = gameData->chrArray;

    gameData->currentChr = 0;

    return EXIT_SUCCESS;
}


void initMenu(MenuData* menuData){
    menuData->titre = rectangle_new(-250, 78, 500, 78);
    rectangle_bindTexture(menuData->titre, "1.jpg");
    menuData->niveaux[0] = rectangle_new(-250, 0, 500, 78);
    rectangle_bindTexture(menuData->niveaux[0], "2.png");
    menuData->niveaux[1] = rectangle_new(-250, -78, 500, 78);
    rectangle_bindTexture(menuData->niveaux[1], "1.jpg");
    menuData->niveaux[2] = rectangle_new(-250, -156, 500, 78);
    rectangle_bindTexture(menuData->niveaux[2], "1.png");
}


GameData gameData_decode(char* level){
  GameData g;

  Rectangle** decorArray;
  Goal** goalArray;
  Character** chrArray;

  FILE* savefile;

  savefile = fopen(level,"r");
  if(savefile == NULL){
    fprintf(stderr, "Cant open file\n");
    exit(1);
  }

  int i;
  int decorAmount, chrAmount;
  float x, y, width, height;

  fscanf(savefile, "%d %d", &decorAmount, &chrAmount);

  g.chrAmount = chrAmount;
  g.decorAmount = decorAmount;

  decorArray = rectangle_generateArray(decorAmount);
  chrArray = character_generateArray(chrAmount);
  goalArray = goal_generateArray(chrAmount);

  for(i = 0; i < decorAmount; ++i) {
    fscanf(savefile, "%f %f %f %f", &x, &y, &width, &height);
    decorArray[i] = rectangle_new(x, y, width, height);
    printf("decor %d : x %f y %f wd %f he %f \n", i, x,y,width,height);
  }

  for(i = 0; i < chrAmount; ++i) {
    fscanf(savefile, "%f %f %f %f", &x, &y, &width, &height);
    chrArray[i] = character_new(x, y, width, height);
    printf("chr %d : x %f y %f wd %f he %f \n", i, x,y,width,height);

  }

  for(i = 0; i < chrAmount; ++i) {
    fscanf(savefile, "%f %f %f %f", &x, &y, &width, &height);
    goalArray[i] = goal_new(x, y, width, height);
    printf("goal %d : x %f y %f wd %f he %f \n", i, x,y,width,height);

  }

  g.chrArray = chrArray;
  g.goalArray = goalArray;
  g.decorArray = decorArray;

  fclose(savefile);

  return g;
}


void processGame(GameData gameData){
    int i;

    setCamera(gameData.player->characters[gameData.currentChr]->pos);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    applyGravity(gameData.player);
    chrCollision(gameData.player);
    moveChrWithDecorCollision(gameData.player, gameData.decorArray, 2);

    characterMovement(gameData.player, gameData.currentChr);
    //printf("pos x %f y %f speed x %f y %f\n", gameData.player->characters[gameData.currentChr]->pos.x,gameData.player->characters[gameData.currentChr]->pos.y, gameData.player->characters[gameData.currentChr]->speed.x,gameData.player->characters[gameData.currentChr]->speed.y);
    glColor3ub(255,255,255);
    for(i=0; i < gameData.decorAmount; ++i){
      rectangle_draw(gameData.decorArray[i], PRIM_FILLED); //rajouter une délégation pour le décor ?
    }

    for(i=0; i < gameData.chrAmount; ++i){
      character_draw(gameData.player->characters[i], i);
    }

    glColor3ub(255,255,255);
    for(i = 0; i < gameData.chrAmount; ++i){
      goal_draw(gameData.goalArray[i]);
    }

    if(isGameWon(gameData.player, gameData.goalArray)){
      gameData.player->characters[0]->model->width = 200;
    }
}

void processMenu(MenuData menuData){
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    rectangle_draw(menuData.titre, PRIM_FILLED);
    rectangle_draw(menuData.niveaux[0], PRIM_FILLED);
    rectangle_draw(menuData.niveaux[1], PRIM_FILLED);
    rectangle_draw(menuData.niveaux[2], PRIM_FILLED);
}
