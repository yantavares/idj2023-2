#include <State.hpp>

State::State() : quitRequested(false), bg("img/ocean.jpg")
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
    bg.Render(0, 0);
}

bool State::QuitRequested()
{
    return quitRequested;
}