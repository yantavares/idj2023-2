#include "State.hpp"

State::State()
{
    quitRequested = false;
    bg.Open("ocean.jpg");
    music.Open("stageState.ogg");
}

void State::LoadAssets()
{
}

void State::Update(float dt)
{
    if (SDL_QuitRequested())
    {
        quitRequested = true;
    }
}

void State::Render()
{
    bg.Render(0, 0);
    music.Play(100);
}

bool State::QuitRequested()
{
    return quitRequested;
}