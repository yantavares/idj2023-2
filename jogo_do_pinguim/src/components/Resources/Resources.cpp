#include <SDL2/SDL_ttf.h>

#include "Resources.hpp"
#include "../../game/Game/Game.hpp"

unordered_map<string, SDL_Texture *> Resources::imageTable;
unordered_map<string, Mix_Music *> Resources::musicTable;
unordered_map<string, Mix_Chunk *> Resources::soundTable;
unordered_map<string, TTF_Font *> Resources::fontTable;

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

TTF_Font *Resources::GetFont(std::string file, int size)
{
    if (fontTable.find(file + std::to_string(size)) != fontTable.end())
    {
        return fontTable.at(file + std::to_string(size));
    }
    else
    {
        OpenFont(file, size);
        return fontTable.at(file + std::to_string(size));
    }
}

void Resources::ClearFonts()
{
    for (auto it = fontTable.begin(); it != fontTable.end(); it++)
    {
        TTF_CloseFont(std::get<1>(*it));
    }
    fontTable.clear();
    return;
}

void Resources::OpenFont(std::string file, int size)
{
    TTF_Font *font;
    if (fontTable.find(file + std::to_string(size)) == fontTable.end())
    {
        font = TTF_OpenFont(file.c_str(), size);
        if (font == nullptr)
        {
            std::cout << SDL_GetError();
        }
    }
    fontTable.insert({file + std::to_string(size), font});
    return;
}