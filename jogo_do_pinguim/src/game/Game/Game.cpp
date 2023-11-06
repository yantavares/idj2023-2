#include "Game.hpp"
#include "../InputManager/InputManager.hpp"

Game *Game::instance = nullptr;

Game::Game(string title, int width, int height)
{

    frameStart = 0;
    dt = 0.0f;
}

Game &Game::GetInstance()
{

    if (instance == nullptr)
    {
        instance = new Game("Yan Tavares, 202041323 :)", 1024, 600);
    }
    return *instance;
}

int Game::GetWidth()
{
    return width;
}

int Game::GetHeight()
{
    return height;
}

/* Game &Game::GetInstance()
{

    if (instance == nullptr)
    {
        instance = new Game("Yan Tavares, 202041323 :)", 1024, 600);
        instance->width = 1024;
        instance->height = 600;
    }
    return *instance;
} */

Game::~Game()
{
    if (storedState != nullptr)
    {
        delete storedState;
    }

    // Clear the states from the stack
    while (!stateStack.empty())
    {
        stateStack.pop();
    }

    Mix_CloseAudio();
    Mix_Quit();

    IMG_Quit();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
}

State &Game::GetState()
{

    return *state;
}

SDL_Renderer *Game::GetRenderer()
{
    return renderer;
}

State &Game::GetCurrentState()
{

    return *stateStack.top();
}

void Game::Push(State *state)
{
    storedState = state;
}

void Game::CalculateDeltaTime()
{
    dt = (SDL_GetTicks() - frameStart);
    frameStart = SDL_GetTicks();
}

float Game::GetDeltaTime()
{
    return dt;
}

void Game::Run()
{
    if (storedState == nullptr)
    {
        cerr << "Error: No initial game state provided." << endl;
        exit(1);
    }

    stateStack.emplace(storedState);
    storedState = nullptr;

    stateStack.top()->Start();

    while (!stateStack.empty())
    {
        if (stateStack.top()->QuitRequested())
        {
            stateStack.pop();
            if (!stateStack.empty())
            {
                stateStack.top()->Resume();
            }
            continue;
        }

        if (storedState != nullptr)
        {
            stateStack.top()->Pause();
            stateStack.emplace(storedState);
            stateStack.top()->Start();
            storedState = nullptr;
        }

        CalculateDeltaTime();
        stateStack.top()->Update(GetDeltaTime());
        stateStack.top()->Render();
        SDL_RenderPresent(renderer);

        InputManager &input = InputManager::GetInstance();

        while (!state->QuitRequested())
        {
            CalculateDeltaTime();

            SDL_RenderPresent(Game::GetInstance().GetRenderer());
            input.Update();
        }
    }
}