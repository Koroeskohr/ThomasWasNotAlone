#include "game.h"


void initGame(Game* game){
    game->loop = 1;
    game->gameState = menu;

    game->windowParams.BIT_PER_PIXEL = 32;
    game->windowParams.windowWidth = 1280;
    game->windowParams.windowHeight = 720;
    game->windowParams.FRAMERATE_MILLISECONDS = 1000 / 60;

    initWindow(game->windowParams.windowWidth, game->windowParams.windowHeight, game->windowParams.BIT_PER_PIXEL);

    initMenu(&game->menuData);
    game->gameEndScreen = rectangle_new(-250,-156,500,312);
    rectangle_bindTexture(game->gameEndScreen, "level_complete.png");

    initAudio();
}

void game_free(Game* game){
  gameData_free(&game->gameData);
  menuData_free(&game->menuData);

  free(game);
}

void gameData_free(GameData* gameData){
  chr_array_free(gameData->chrArray, gameData->chrAmount);
  printf("1\n");
  rectangle_array_free(gameData->decorArray, gameData->decorAmount);
  printf("1\n");

  goal_array_free(gameData->goalArray, gameData->chrAmount);
  printf("1\n");


  freeMusic(gameData->music);
  printf("1\n");


}

void menuData_free(MenuData* menuData){
  rectangle_free(menuData->titre);
  rectangle_free(menuData->niveaux[0]);
  rectangle_free(menuData->niveaux[1]);
  rectangle_free(menuData->niveaux[2]);
}

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
    initAudio();
    Mix_PlayMusic(gameData->music,-1);

    return EXIT_SUCCESS;
}


void initMenu(MenuData* menuData){
    menuData->titre = rectangle_new(-250, 78, 500, 78);
    rectangle_bindTexture(menuData->titre, "menu_1.png");
    menuData->niveaux[0] = rectangle_new(-250, 0, 500, 78);
    rectangle_bindTexture(menuData->niveaux[0], "menu_2.png");
    menuData->niveaux[1] = rectangle_new(-250, -78, 500, 78);
    rectangle_bindTexture(menuData->niveaux[1], "menu_3.png");
    menuData->niveaux[2] = rectangle_new(-250, -156, 500, 78);
    rectangle_bindTexture(menuData->niveaux[2], "menu_4.png");
}


GameData gameData_decode(char* level){
  GameData g;

  Rectangle** decorArray;
  Goal** goalArray;
  Character** chrArray;

  FILE* savefile;

  savefile = fopen(level,"r");
  if(savefile == NULL){
    fprintf(stderr, "Cant open file %s\n", level);
    exit(1);
  }

  int i;
  int decorAmount, chrAmount;
  float x, y, width, height;
  char musicPath[200];
  char texturePath[200];

  fscanf(savefile, "%d %d", &decorAmount, &chrAmount);

  g.chrAmount = chrAmount;
  g.decorAmount = decorAmount;

  decorArray = rectangle_generateArray(decorAmount);
  chrArray = character_generateArray(chrAmount);
  goalArray = goal_generateArray(chrAmount);

  for(i = 0; i < decorAmount; ++i) {
    fscanf(savefile, "%f %f %f %f %s", &x, &y, &width, &height, texturePath);
    decorArray[i] = rectangle_new(x, y, width, height);
    rectangle_bindTexture(decorArray[i], texturePath);
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

  fscanf(savefile, "%s", musicPath);
  g.music = loadMusic(musicPath);

  g.chrArray = chrArray;
  g.goalArray = goalArray;
  g.decorArray = decorArray;
  fclose(savefile);
  return g;
}


void processGame(Game* game){
    int i;

    setCamera(game->gameData.player->characters[game->gameData.currentChr]->pos);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    applyGravity(game->gameData.player);
    chrCollision(game->gameData.player);
    moveChrWithDecorCollision(game->gameData.player, game->gameData.decorArray, game->gameData.decorAmount);

    characterMovement(game->gameData.player, game->gameData.currentChr);
    //printf("pos x %f y %f speed x %f y %f\n", gameData.player->characters[gameData.currentChr]->pos.x,gameData.player->characters[gameData.currentChr]->pos.y, gameData.player->characters[gameData.currentChr]->speed.x,gameData.player->characters[gameData.currentChr]->speed.y);
    glColor3ub(255,255,255);
    for(i=0; i < game->gameData.decorAmount; ++i){
      rectangle_draw(game->gameData.decorArray[i], PRIM_FILLED);
    }

    glColor3ub(255,255,255);
    for(i = 0; i < game->gameData.chrAmount; ++i){
      goal_draw(game->gameData.goalArray[i]);
    }

    for(i=0; i < game->gameData.chrAmount; ++i){
      character_draw(game->gameData.player->characters[i], i);
    }

    if(isGameWon(game->gameData.player, game->gameData.goalArray)){
      game->gameState = gameEnd;
      game->winTime = SDL_GetTicks();
    }
}

void processMenu(MenuData menuData){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(-250., 250., -250./1.6, 250./1.6);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


    rectangle_draw(menuData.titre, PRIM_FILLED);
    rectangle_draw(menuData.niveaux[0], PRIM_FILLED);
    rectangle_draw(menuData.niveaux[1], PRIM_FILLED);
    rectangle_draw(menuData.niveaux[2], PRIM_FILLED);
}


void processGameEnd(Game* game)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(-250., 250., -250./1.6, 250./1.6);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    rectangle_draw(game->gameEndScreen, PRIM_FILLED);
    if(SDL_GetTicks() - game->winTime > 5000){
        Mix_CloseAudio();
        freeMusic(game->gameData.music);
        game->gameState = menu;
    }
}
