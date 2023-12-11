#ifndef GAME_HPP
#define GAME_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>

#include "../StageState/StageState.hpp"

using namespace std;

class Game
{
public:
    Game(string title, int width, int height);
    ~Game();
    void Run();
    SDL_Renderer *GetRenderer();
    StageState &GetStateState();
    static Game &GetInstance();
    int GetWidth();
    int GetHeight();

private:
    static Game *instance;
    SDL_Window *window;
    SDL_Renderer *renderer;
    StageState *stageState;

    int frameStart;
    float dt;
    void CalculateDeltaTime();
    float GetDeltaTime();

    int width;
    int height;
};

#endif