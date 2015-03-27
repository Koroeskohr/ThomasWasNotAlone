#ifndef _GOAL_H
#define _GOAL_H

#include "vector.h"
#include "rectangle.h"


typedef struct goal
{
  Rectangle* model;
} Goal;


Goal* goal_new(float x, float y, int width, int height);

void goal_draw(Goal* goal);
Goal** goal_generateArray(int n);

void goal_free(Goal* goal);

#endif