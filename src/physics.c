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

void characterMovement(Player *p, int currentChr){
  Character* chr = p->characters[currentChr];
  chr->speed.x += chr->acc.x;
  if(fabs(chr->speed.x) > MAX_SPEED){
    chr->speed.x = chr->speed.x > 0 ? MAX_SPEED : -MAX_SPEED;
  }

  if(chr->chrAbove != -1){
    printf("Passage du mouvement de %d a %d", currentChr, chr->chrAbove);
    characterMovement(p, chr->chrAbove);
  }
}

void jump(Character* chr){
  //saut proportionnel à la taille du personnage ???
  if(!chr->jumping) {
    chr->jumping = 1;
    chr->speed.y = 4;
  }

}

void moveChrWithDecorCollision(Player* p, Rectangle** decorArray, int size){
  int i,j;
  int sideCollision;

  for(i=0; i < p->n; ++i){
    p->characters[i]->pos = sumVector2(p->characters[i]->pos, p->characters[i]->speed);
    //check collisions
    for (j = 0; j < size; ++j)
    {
      if(collision_above(p->characters[i], decorArray[j])){
        p->characters[i]->pos.y = decorArray[j]->y - p->characters[i]->model->height;
        p->characters[i]->speed.y = 0;
      }

      sideCollision = collision_sides(p->characters[i], decorArray[j]);
      if(sideCollision){
        if(sideCollision == -1){
          p->characters[i]->pos.x = decorArray[j]->x - p->characters[i]->model->width;
          p->characters[i]->speed.x = 0;
        }
        if (sideCollision == 1)
        {
          p->characters[i]->pos.x = decorArray[j]->x + decorArray[j]->width;
          p->characters[i]->speed.x = 0;
        }
      }

      if(collision_under(p->characters[i], decorArray[j])){
        p->characters[i]->pos.y = decorArray[j]->y + decorArray[j]->height;
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


void chrCollision(Player* p){
  int i,j;
  int sideCollision;

  for(i=0; i < p->n; ++i){
    //check collisions
    for (j = 0; j < p->n; ++j)
    {
      if(i != j){

        /*if(collision_above(p->characters[i], p->characters[j]->model)){
          printf("Collision chr above : %d under %d\n", i, j);
          //p->characters[i]->pos.y = p->characters[j]->model->y - p->characters[i]->model->height;
          //p->characters[i]->speed.y = 0;
          p->characters[i]->chrAbove = j;
        }
        else{
          p->characters[i]->chrAbove = -1;
        }*/

        sideCollision = collision_sides(p->characters[i], p->characters[j]->model);
        if(sideCollision){
          if(sideCollision == -1){
            p->characters[i]->pos.x = p->characters[j]->model->x - p->characters[i]->model->width;
            p->characters[i]->speed.x = 0;
          }
          {
          if (sideCollision == 1)
            p->characters[i]->pos.x = p->characters[j]->model->x + p->characters[j]->model->width;
            p->characters[i]->speed.x = 0;
          }
        }
        if(collision_under(p->characters[i], p->characters[j]->model)){
          //printf("Collision chr under : %d on %d\n", i, j);
          p->characters[j]->chrAbove = i;
          p->characters[i]->pos.y = p->characters[j]->model->y + p->characters[j]->model->height;
          p->characters[i]->grounded = 1;
          //p->characters[i]->model->width += 0.3; //debug
          if(!p->characters[i]->jumping){
            p->characters[i]->speed.y = 0;
          }
          else {
            p->characters[i]->jumping = 0;
          }
        }
        else{
          p->characters[j]->chrAbove = -1;
          //printf("pas collision under\n");
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
