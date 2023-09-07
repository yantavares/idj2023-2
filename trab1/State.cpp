#include "State.hpp"

State::State()
{
    quitRequested = false;
    bg.Open("ocean.jpg");
    music.Open("audio/stageState.ogg");
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
    music.Play();
}

bool State::QuitRequested()
{
    return quitRequested;
}