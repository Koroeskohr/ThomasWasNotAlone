#include "physics.h"

int rectangle_collision(Rectangle* r1, Rectangle* r2){
  if (r1->x < r2->x + r2->width && r1->x + r1->width > r2->x && r1->y < r2->y + r2->height && r1->height + r1->y > r2->y) { 
    //il y a collision
    return 1;
  } else {
    return 0;
  }
}

//si le x du coin haut gauche de r1 est avant le x du coin haut droit de r2 
//et si le x du coin haut droit de r2 est après le x du coin haut gauche de r2
//pareil pour le y

// int collision_under(Rectangle* r1, Rectangle* r2){
// 	if(r1->y+r1->height <= r2->y){

// 	}
// }

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