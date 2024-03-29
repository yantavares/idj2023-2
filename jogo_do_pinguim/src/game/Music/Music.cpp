#include <iostream>

#include "Music.hpp"

Music::Music()
{
    music = nullptr;
}

Music::Music(string file)
{
    music = nullptr;
    Open(file);
}

Music::~Music()
{
    Stop();
    if (music != nullptr)
    {
        Mix_FreeMusic(music);
    }
}

void Music::Play(int times)
{
    if (music != nullptr)
    {
        Mix_PlayMusic(music, times);
    }
}

void Music::Stop(int msToStop)
{
    if (music != nullptr)
    {
        if (msToStop == 0)
        {
            Mix_HaltMusic();
        }
        else
        {
            Mix_FadeOutMusic(msToStop);
        }
    }
}

void Music::Open(string file)
{
    music = Mix_LoadMUS(file.c_str());
    if (music == nullptr)
    {
        cerr << "Failed to load music file: " << Mix_GetError() << endl;
    }
}

bool Music::IsOpen()
{
    return music != nullptr;
}