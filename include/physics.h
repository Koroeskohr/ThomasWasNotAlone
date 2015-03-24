#ifndef _PHYSICS_H
#define _PHYSICS_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include "player.h"
#include "vector.h"

#define MAX_SPEED 4

int rectangle_collision(Rectangle* r1, Rectangle* r2);
void applyGravity(Player* p);
void characterMovement(Character* chr);
void applyMovementFromSpeed(Player* p, Rectangle** rectArray, int size);
void jump(Character* chr);


int collision_under(Character* chr, Rectangle* bg);
int collision_sides(Character* chr, Rectangle* bg);
int collision_above(Character* chr, Rectangle* bg);


#endif