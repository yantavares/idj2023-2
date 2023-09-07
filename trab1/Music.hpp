#ifndef MUSIC_HPP
#define MUSIC_HPP

#include <string>
#include <SDL2/SDL_mixer.h>

class Music
{
public:
    Music();
    Music(std::string file);
    ~Music();

    void Play(int times = -1);
    void Stop(int msToStop = 1500);
    void Open(std::string file);
    bool IsOpen() const;

private:
    Mix_Music *music;
};

#endif