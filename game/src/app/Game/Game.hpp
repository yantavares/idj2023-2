#ifndef GAME_HPP
#define GAME_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>

#include "../State/State.hpp"

using namespace std;

class Game
{
public:
    Game(string title, int width, int height);
    ~Game();
    void Run();
    SDL_Renderer *GetRenderer();
    State &GetState();
    static Game &GetInstance();

private:
    static Game *instance;
    SDL_Window *window;
    SDL_Renderer *renderer;
    State *state;
};

#endif