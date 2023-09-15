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
};
