#include "sound.h"

void initAudio()
{
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1)
    {
       printf("Error : %s\n", Mix_GetError());
    }
}

Mix_Music* loadMusic(char* musicPath){
    Mix_Music* music;
    char fullPath[200];

    sprintf(fullPath, "sound/%s", musicPath);
    music = Mix_LoadMUS(fullPath);

    return music;
}

void freeMusic(Mix_Music* music){
    Mix_FreeMusic(music);
    music = NULL;
}

void closeAudio(){
    Mix_CloseAudio();
}
