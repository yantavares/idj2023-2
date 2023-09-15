#include "Vec2.hpp"

Vec2::Vec2()
{
    x = 0;
    y = 0;
}

Vec2::Vec2(float x, float y)
{
    this->x = x;
    this->y = y;
}

Vec2 Vec2::GetRotated(float rad)
{
    return Vec2(x * cos(rad) - y * sin(rad), y * cos(rad) + x * sin(rad));
}

Vec2 Vec2::operator+(Vec2 b)
{
    return Vec2(x + b.x, y + b.y);
}