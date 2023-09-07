#ifndef STATE_HPP
#define STATE_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>

#include "Sprite.hpp"
#include "Music.hpp"

class Music;

class State
{
public:
    State();
    bool QuitRequested();
    void LoadAssets();
    void Update(float dt);
    void Render();

private:
    Sprite bg;
    Music music;
    bool quitRequested;
};

#endif