#ifndef GAME_HPP
#define GAME_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>

#include "../StageState/StageState.hpp"
#include "../State/State.hpp"

using namespace std;

class Game
{
public:
    Game(string title, int width, int height);
    ~Game();
    void Run();

    SDL_Renderer *GetRenderer();
    State &GetCurrentState();
    static Game &GetInstance();
    int GetWidth();
    int GetHeight();

    vector<shared_ptr<State>> stateStack;
    State* storedState;


private:
    static Game *instance;
    SDL_Window *window;
    SDL_Renderer *renderer;
    State *storedState;

    int frameStart;
    float dt;
    void CalculateDeltaTime();
    float GetDeltaTime();

    void Push(State* state);
    void Run();

    int width;
    int height;
};

#endif