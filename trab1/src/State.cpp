#include "State.hpp"

State::State()
{
    quitRequested = false;
    bg.Open("img/ocean.jpg");
    music.Open("audio/stageState.ogg");
    music.Play(-1);
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
}

bool State::QuitRequested()
{
    return quitRequested;
}