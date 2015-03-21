#ifndef _PHYSICS_H
#define _PHYSICS_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include "player.h"
#include "vector.h"

#define MAX_SPEED 10

int rectangle_collision(Rectangle* r1, Rectangle* r2);
void applyGravity(Player* p);
void applyMovementFromSpeed(Player* p);

int collision_under(Rectangle* r1, Rectangle* r2);


#endif