#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>

typedef struct rectangle
{
  int x, y;
  int width, height;
  int color[3] = {0,0,0};
} Rectangle;


Rectangle* rectangle_new(int width, int height);
void rectangle_free(Rectangle* rect);
