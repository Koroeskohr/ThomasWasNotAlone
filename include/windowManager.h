#ifndef _WINDOWMANAGER_H
#define _WINDOWMANAGER_H

#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <string.h>


typedef struct windowParameters {
    unsigned int windowWidth;
    unsigned int windowHeight;
    unsigned int BIT_PER_PIXEL;
    Uint32 FRAMERATE_MILLISECONDS;
} WindowParams;

void reshape(int winWidth, int winHeight);

void setVideoMode(int winWidth, int winHeight, const int BIT_PER_PIXEL);
void initWindow(int windowWidth, int windowHeight, const int BIT_PER_PIXEL);

#endif
