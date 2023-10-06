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

Vec2 Vec2::operator*(float d)
{
    return Vec2(x * d, y * d);
}

Vec2 Vec2::operator-(Vec2 b)
{
    return Vec2(x - b.x, y - b.y);
}

Vec2 Vec2::operator+(Vec2 b)
{
    return Vec2(x + b.x, y + b.y);
}

void Vec2::operator+=(Vec2 b)
{
    x += b.x;
    y += b.y;
}

float Vec2::GetMagnitude()
{
    return sqrt(x * x + y * y);
}

float Vec2::GetSlope()
{
    return atan2(y, x);
}

Vec2 Vec2::GetNormalized()
{
    return Vec2(x / GetMagnitude(), y / GetMagnitude());
}
