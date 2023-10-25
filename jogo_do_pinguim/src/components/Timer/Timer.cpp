#include "Timer.hpp"

Timer::Timer(float offset)
{
    time = offset;
}

void Timer::Update(float dt)
{
    time += dt;
}

void Timer::Restart()
{
    time = 0;
}

float Timer::Get()
{
    return time;
}
