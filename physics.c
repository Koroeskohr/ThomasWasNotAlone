#include "physics.h"

int rectangle_collision(Rectangle* r1, Rectangle* r2){
  if (r1.x < r2.x + r2.width //si le x du coin haut gauche de r1 est avant le x du coin haut droit de r2 
   && r1.x + r1.width > r2.x //et si le x du coin haut droit de r2 est après le x du coin haut gauche de r2
   && r1.y < r2.y + r2.height //pareil pour le y
   && r1.height + r1.y > r2.y) { 
   //il y a collision
   return 1;
  } else {
    return 0;
  }
}