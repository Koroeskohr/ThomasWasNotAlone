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

void rectangle_draw(Rectangle* rect, int filled){
  glPushMatrix();
    glTranslatef(rect->x, rect->y, 0);
    glScalef(rect->width, rect->height, 1);
    dessinCarre(filled);
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

void rectangle_bindTexture(Rectangle* rect, char* textureRelPath){
  SDL_Surface* texture = IMG_Load(textureRelPath);
  if(image == NULL){
    fprintf(stderr, "Failed loading img %s\n", textureRelPath);
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
}
