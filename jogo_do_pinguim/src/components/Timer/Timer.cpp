#include "Timer.hpp"

Timer::Timer(float offset)
{
    time = offset;
}

void Timer::Update(float dt)
{
    time += dt / 1000;
}

void Timer::Restart()
{
    time = 0;
}

float Timer::Get()
{
    return time;
}
