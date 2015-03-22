#include "physics.h"

/*
  si le x du coin haut gauche de r1 est avant le x du coin haut droit de r2 
  et si le x du coin haut droit de r2 est après le x du coin haut gauche de r2
  pareil pour le y
 */
int rectangle_collision(Rectangle* r1, Rectangle* r2){
  if (r1->x < r2->x + r2->width && r1->x + r1->width > r2->x && r1->y < r2->y + r2->height && r1->height + r1->y > r2->y) { 
    //il y a collision
    return 1;
  } else {
    return 0;
  }
}

void applyGravity(Player* p){
  int i;
  for(i=0; i < p->n; i++){
    p->characters[i]->speed.y += p->characters[i]->acc.y;
    if(fabs(p->characters[i]->speed.y) > MAX_SPEED){
      p->characters[i]->speed.y = p->characters[i]->speed.y > 0 ? MAX_SPEED : -MAX_SPEED;
    }
  }
}

void characterMovement(Character* chr){
  chr->speed.x += chr->acc.x;
  if(fabs(chr->speed.x) > MAX_SPEED){
    chr->speed.x = chr->speed.x > 0 ? MAX_SPEED : -MAX_SPEED;
  }
}

void jump(Character* chr){
  chr->speed.y = 5;
}

void applyMovementFromSpeed(Player* p, Rectangle** rectArray, int size){
  int i,j;
  for(i=0; i < p->n; ++i){

    p->characters[i]->pos = sumVector2(p->characters[i]->pos, p->characters[i]->speed);
    //check collisions
    for (j = 0; j < size; ++j)
    {
      if(collision_under(p->characters[i]->model, rectArray[j])){
        p->characters[i]->pos.y = rectArray[j]->y + rectArray[j]->height;
        p->characters[i]->speed.y = 0;
      }
    }

    p->characters[i]->model->x = p->characters[i]->pos.x;
    p->characters[i]->model->y = p->characters[i]->pos.y;
  }
}



int collision_under(Rectangle* r1, Rectangle* r2){
	if(r1->y >= r2->y + r2->height - 10 && rectangle_collision(r1, r2)){
    return 1;
	}
  else {
    return 0;
  }
}

// int process_collision(Rectangle** list, Rectangle* r1){
// 	int i = 0;
// 	for (i = 0; i < count; ++i)
// 	{
// 		/* code */
// 	}

// 	for list {
// 		if(rectangle_collision(r1, r2)){
// 			.
// 			.
// 			.

// 			colision->top != 0 {

// 			}*

// 		}	
// 	}
	
// }