#include "Resources.hpp"
#include "../../game/Game/Game.hpp"

unordered_map<string, SDL_Texture *> Resources::imageTable;
unordered_map<string, Mix_Music *> Resources::musicTable;
unordered_map<string, Mix_Chunk *> Resources::soundTable;

SDL_Texture *Resources::GetImage(string filepath)
{
    auto found = imageTable.find(filepath);
    if (found == imageTable.end())
    {
        SDL_Texture *texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), filepath.c_str());
        if (!texture)
        {
            throw runtime_error(SDL_GetError());
        }
        imageTable[filepath] = texture;
        return texture;
    }
    return found->second;
}

void Resources::ClearImages()
{

    for (auto &a : imageTable)
    {
        SDL_DestroyTexture(a.second);
    }
    imageTable.clear();
}

Mix_Music *Resources::GetMusic(string filepath)
{
    auto found = musicTable.find(filepath);
    if (found == musicTable.end())
    {
        Mix_Music *music = Mix_LoadMUS(filepath.c_str());
        if (!music)
        {
            throw runtime_error(Mix_GetError());
        }
        musicTable[filepath] = music;
        return music;
    }
    return found->second;
}

void Resources::ClearMusics()
{
    for (auto &a : musicTable)
    {
        Mix_FreeMusic(a.second);
    }
    musicTable.clear();
}

Mix_Chunk *Resources::GetSound(string filepath)
{
    auto found = soundTable.find(filepath);
    if (found == soundTable.end())
    {
        Mix_Chunk *sound = Mix_LoadWAV(filepath.c_str());
        if (!sound)
        {
            throw runtime_error(Mix_GetError());
        }
        soundTable[filepath] = sound;
        return sound;
    }
    return found->second;
}

void Resources::ClearSounds()
{
    for (auto &a : soundTable)
    {
        Mix_FreeChunk(a.second);
    }
    soundTable.clear();
}
