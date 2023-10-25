#ifndef TIMER_H
#define TIMER_H

class Timer
{
public:
    Timer(float offset = 0);

    void Update(float dt);
    void Restart();
    float Get();

private:
    float time;
};

#endif
