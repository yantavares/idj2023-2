#ifndef VEC2_HPP
#define VEC2_HPP

#include <cmath>

#define PI 3.1415

class Vec2
{
private:
public:
    float x, y;
    Vec2();
    Vec2(float x, float y);
    Vec2 GetRotated(float rad);
    Vec2 operator+(Vec2 b);
    Vec2 operator-(Vec2 b);
    Vec2 operator*(float d);
    void operator+=(Vec2 b);
    Vec2 operator/(float d);
    float GetMagnitude();
    float GetSlope();
    Vec2 GetNormalized();
};

#endif