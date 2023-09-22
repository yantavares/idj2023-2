#include "Sound.hpp"

Sound::Sound(GameObject &associated) : Component(associated)
{
    this->associated = associated;
    chunk = nullptr;
}

Sound::Sound(GameObject &associated, string file) : Component(associated)
{
    this->associated = associated;
    Open(file);
}

Sound::~Sound()
{
    if (chunk != nullptr)
    {
        Mix_HaltChannel(channel);
    }
    Mix_FreeChunk(chunk);
}

void Sound::Play(int times)
{
    channel = Mix_PlayChannel(-1, chunk, times);
}

void Sound::Stop()
{
    Mix_HaltChannel(channel);
}

void Sound::Open(std::string file)
{
    chunk = Mix_LoadWAV(file.c_str());
}

bool Sound::IsOpen()
{
    return chunk != nullptr;
}

void Sound::Update(float dt)
{
}

void Sound::Render()
{
}

bool Sound::Is(string type)
{
    return type == "Sound" ? true : false;
}