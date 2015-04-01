#include "file.h"

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