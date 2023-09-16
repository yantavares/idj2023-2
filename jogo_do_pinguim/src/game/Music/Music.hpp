#ifndef MUSIC_HPP
#define MUSIC_HPP

#include <iostream>
#include <SDL2/SDL_mixer.h>

using namespace std;

class Music
{
public:
    Music();
    Music(string file);
    ~Music();

    void Play(int times = -1);
    void Stop(int msToStop = 1500);
    void Open(string file);
    bool IsOpen();

private:
    Mix_Music *music;
};

#endif