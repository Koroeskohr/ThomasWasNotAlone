#ifndef _WINDOWMANAGER_H
#define _WINDOWMANAGER_H

#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>


void reshape(int winWidth, int winHeight);

void setVideoMode(int winWidth, int winHeight, const int BIT_PER_PIXEL);
void initWindow(int windowWidth, int windowHeight, const int BIT_PER_PIXEL);

#endif