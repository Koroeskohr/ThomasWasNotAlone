#ifndef _SOUND_H
#define _SOUND_H

#include <SDL/SDL_mixer.h>
#include <string.h>

void initAudio();

Mix_Music* loadMusic(char* musicPath);
void freeMusic(Mix_Music* music);


void closeAudio();


#endif
