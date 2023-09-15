#include "Rect.hpp"

Rect::Rect()
{
    x = 0;
    y = 0;
    w = 0;
    h = 0;
}

Rect::Rect(float x, float y, float w, float h)
{
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
}

bool Rect::Contains(float x, float y)
{
    return x >= this->x && x <= this->x + w && y >= this->y && y <= this->y + h;
}

bool Rect::Contains(Vec2 b)
{
    return b.x >= this->x && b.x <= this->x + w && b.y >= this->y && b.y <= this->y + h;
}