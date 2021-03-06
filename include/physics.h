#ifndef _PHYSICS_H
#define _PHYSICS_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include "player.h"
#include "vector.h"

#define MAX_SPEED_Y 6
#define MAX_SPEED_X 4

int rectangle_collision(Rectangle* r1, Rectangle* r2);
void applyGravity(Player* p);
void characterMovement(Player* p, int currentChr);
void moveChrWithDecorCollision(Player* p, Rectangle** rectArray, int size);
void chrCollision(Player* p);
void jump(Character* chr);


int collision_under(Character* chr, Rectangle* bg);
int collision_sides(Character* chr, Rectangle* bg);
int collision_above(Character* chr, Rectangle* bg);


#endif
