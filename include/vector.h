#ifndef _VECTOR_H
#define _VECTOR_H

typedef struct Vector2
{
  float x, y;
} Vector2;

Vector2 vector2(float x, float y);

Vector2 sumVector2(Vector2 v1, Vector2 v2);
Vector2 diffVector2(Vector2 v1, Vector2 v2);




#endif