#include "Sound.hpp"

Sound::Sound(GameObject &associated) : Component(associated)
{
    chunk = nullptr;
    this->associated = associated;
}

Sound::Sound(GameObject &associated, string file) : Component(associated)
{
    chunk = nullptr;
    this->associated = associated;
    Open(file);
}

void Sound::Play(int times = 1)
{
    channel = Mix_PlayChannel(-1, chunk, times - 1);
}

void Sound::Stop()
{
    Mix_HaltChannel(channel);
}

void Sound::Open(string file)
{
    chunk = Mix_LoadWAV(file.c_str());
    if (chunk == nullptr)
    {
        cout << "Mix_LoadWAV: " << SDL_GetError() << endl;
        exit(-1);
    }
}

Sound::~Sound()
{
    if (chunk != nullptr)
    {
        Mix_FreeChunk(chunk);
    }
}