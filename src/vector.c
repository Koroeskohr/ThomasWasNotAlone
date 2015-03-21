#include "vector.h"

Vector2 vector2(float x, float y){
  Vector2 vect;
  vect.x = x;
  vect.y = y;

  return vect;
}

Vector2 sumVector2(Vector2 v1, Vector2 v2){
  Vector2 sum;
  sum.x = v1.x + v2.x;
  sum.y = v1.y + v2.y;
  return sum;
}

Vector2 diffVector2(Vector2 v1, Vector2 v2) {
  Vector2 diff;
  diff.x = v1.x - v2.x;
  diff.y = v1.y - v2.y;
  return diff;
}