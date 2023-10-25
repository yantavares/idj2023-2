#ifndef COLLIDER_HPP
#define COLLIDER_HPP

#include <string>

#include "Vec2.hpp"
#include "Rect.hpp"
#include "Component.hpp"
#include "GameObject.hpp"

class Collider : public Component
{
public:
    Collider(GameObject &associated, Vec2 scale = {1, 1}, Vec2 offset = {0, 0});

    void Update(float dt);
    void Render();
    bool Is(std::string type);

    void SetScale(Vec2 scale);
    void SetOffset(Vec2 offset);

    Rect box;

private:
    Vec2 scale;
    Vec2 offset;
};

#endif
