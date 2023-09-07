#include <State.hpp>

State::State() : quitRequested(false), bg()
{
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
}

bool State::QuitRequested()
{
    return quitRequested;
}