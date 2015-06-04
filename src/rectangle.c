#include "rectangle.h"

Rectangle* rectangle_new(float x, float y, int width, int height){
  Rectangle* r = (Rectangle*)malloc(sizeof(Rectangle));
  r->width = width;
  r->height = height;
  r->x = x;
  r->y = y;

  r->textureId = -1;
  return r;
}

void rectangle_free(Rectangle* rect){
  free(rect);
  rect = NULL;
}

void rectangle_array_free(Rectangle** rectArray, int amount){
  int i;
  for(i = 0; i < amount; ++i){
    rectangle_free(rectArray[i]);
  }
  free(rectArray);
}

int isPointInRectangle(float x, float y, Rectangle* rect){
    return (rect->x < x && rect->x + rect->width > x) && (rect->y < y && rect->y + rect->height > y);
}

void rectangle_draw(Rectangle* rect, int filled){
  glPushMatrix();
    glTranslatef(rect->x, rect->y, 0);
    glScalef(rect->width, rect->height, 1);
    if(rect->textureId <= 0 ){
      dessinCarre(filled);      
    }
    else {
      glEnable(GL_TEXTURE_2D);
      glBindTexture(GL_TEXTURE_2D, rect->textureId);
      dessinCarreAvecTexture();
      glBindTexture(GL_TEXTURE_2D, 0);
      glDisable(GL_TEXTURE_2D);
    }
  glPopMatrix();
  
//  glColor3ub(255,0,0);
//  dessinPoint(rect->x, rect->y);
//  glColor3ub(0,0,255);
//  dessinPoint(rect->x, rect->y + rect->height);
  glColor3ub(255,255,255);
}

Rectangle** rectangle_generateArray(int n){
  Rectangle** array = (Rectangle**)malloc(n*sizeof(Rectangle*));
  return array;
}

int rectangle_bindTexture(Rectangle* rect, char* textureRelPath){
  char texturePath[200];
  char path[200];

  strcpy(texturePath, "img");
  realpath(texturePath, path);
  strcat(path, "/");
  strcat(path, textureRelPath);

  SDL_Surface* texture = IMG_Load(path);
  if(texture == NULL){
    fprintf(stderr, "Failed loading img %s\n", path);
    printf("failed: %s\n", IMG_GetError());
    return EXIT_FAILURE;
  }
  glGenTextures(1, &rect->textureId);
  glBindTexture(GL_TEXTURE_2D, rect->textureId);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  GLenum format;
  switch(texture->format->BytesPerPixel){
    case 1:
      format = GL_RED;
      break;

    case 3:
      format = GL_RGB;
      break;

    case 4:
      format = GL_RGBA;
      break;

    default:
      fprintf(stderr, "Couldnt handle image format");
      return EXIT_FAILURE;
  }
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture->w, texture->h, 0, format, GL_UNSIGNED_BYTE, texture->pixels);
  glBindTexture(GL_TEXTURE_2D, 0);
  SDL_FreeSurface(texture);
  return EXIT_SUCCESS;
}
