#include "physics.h"


int rectangle_collision(Rectangle* r1, Rectangle* r2){
  /*
    si le x du coin haut gauche de r1 est avant le x du coin haut droit de r2 
    et si le x du coin haut droit de r2 est après le x du coin haut gauche de r2
    pareil pour le y
   */
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
  //saut proportionnel à la taille du personnage ???
  if(!chr->jumping) {
    chr->jumping = 1;
    chr->speed.y = 4;
  }

}

void applyMovementFromSpeed(Player* p, Rectangle** rectArray, int size){
  int i,j;
  int sideCollision;

  for(i=0; i < p->n; ++i){
    p->characters[i]->pos = sumVector2(p->characters[i]->pos, p->characters[i]->speed);
    //check collisions
    for (j = 0; j < size; ++j)
    {
      if(collision_above(p->characters[i], rectArray[j])){
        p->characters[i]->pos.y = rectArray[j]->y - p->characters[i]->model->height;
        p->characters[i]->speed.y = 0;
      }

      sideCollision = collision_sides(p->characters[i], rectArray[j]);
      if(sideCollision){
        if(sideCollision == -1){
          p->characters[i]->pos.x = rectArray[j]->x - p->characters[i]->model->width;
          p->characters[i]->speed.x = 0;
        }
        if (sideCollision == 1)
        {
          p->characters[i]->pos.x = rectArray[j]->x + rectArray[j]->width;
          p->characters[i]->speed.x = 0;
        }
      }
      if(collision_under(p->characters[i], rectArray[j])){
        p->characters[i]->pos.y = rectArray[j]->y + rectArray[j]->height;
        p->characters[i]->grounded = 1;
        //p->characters[i]->model->width += 0.3; //debug
        if(!p->characters[i]->jumping){
          p->characters[i]->speed.y = 0;
        }
        else {
          p->characters[i]->jumping = 0;
        }
      } 
    }

    p->characters[i]->model->x = p->characters[i]->pos.x;
    p->characters[i]->model->y = p->characters[i]->pos.y;
  }
}

/**
 * Retourne une valeur si le personnage actuel subit une collision sur ses côtés
 * @param  chr Personnage pris en compte
 * @param  bg  Element du decor actuel
 * @return     -1 si collision à gauche, 1 si collision a droite
 */
int collision_sides(Character* chr, Rectangle* bg){
  if(chr->acc.x != 0 && rectangle_collision(chr->model, bg) && !collision_under(chr,bg)){
    //si le character est a gauche
    if(chr->pos.x + chr->model->width < bg->x + 10) 
    {
      return -1;
    }
    //s'il est a droite 
    else if(chr->pos.x > bg->x + bg->width - 10)
    {
      return 1;
    } 
  }
  return 0;
}

int collision_under(Character* chr, Rectangle* bg){
	if(chr->model->y >= bg->y + bg->height - 10 && rectangle_collision(chr->model, bg)){
    return 1;
	}
  else {
    return 0;
  }
}

int collision_above(Character* chr, Rectangle* bg){
  if(chr->model->y + chr->model->height <= bg->y + 10 && rectangle_collision(chr->model, bg)){
    return 1;
  }
  else {
    return 0;
  }
}
