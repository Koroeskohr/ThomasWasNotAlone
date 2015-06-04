#include "goal.h"


Goal* goal_new(float x, float y, int width, int height){
  Goal* goal = (Goal*)malloc(sizeof(Goal));
  goal->model = rectangle_new(x, y, width, height);

  return goal;
}

void goal_draw(Goal* goal) {
  rectangle_draw(goal->model, PRIM_EMPTY);
}

Goal** goal_generateArray(int n){
  Goal** array = (Goal**)malloc(n*sizeof(Goal*));
  return array;
}


void goal_free(Goal* goal){
  free(goal->model);
  goal->model = NULL;

  free(goal);
  goal = NULL;
}

void goal_array_free(Goal** goalArray, int amount){
  int i;

  for (i = 0; i < amount; ++i) {
    goal_free(goalArray[i]);
  }

  free(goalArray);
}
