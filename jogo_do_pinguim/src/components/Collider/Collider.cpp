#include <SDL2/SDL.h>

#include "Collider.hpp"
#include "../../game/Camera/Camera.hpp"
#include "../../game/Game/Game.hpp"

#define DEBUG 0

Collider::Collider(GameObject &associated, Vec2 scale, Vec2 offset)
    : Component(associated), scale(scale), offset(offset)
{
}

void Collider::Update(float dt)
{

    box = associated.box;
    box.w *= scale.x;
    box.h *= scale.y;

    Vec2 rotatedOffset = offset.GetRotated(associated.angle);

    box.SetCenter(associated.box.GetCenteredVec2() + rotatedOffset);
}

void Collider::Render()
{
#ifdef DEBUG
    Vec2 center(box.GetCenteredVec2());
    SDL_Point points[5];

    Vec2 point = (Vec2(box.x, box.y) - center).GetRotated(associated.angle / (180 / PI)) + center - Camera::pos;
    points[0] = {(int)point.x, (int)point.y};
    points[4] = {(int)point.x, (int)point.y};

    point = (Vec2(box.x + box.w, box.y) - center).GetRotated(associated.angle / (180 / PI)) + center - Camera::pos;
    points[1] = {(int)point.x, (int)point.y};

    point = (Vec2(box.x + box.w, box.y + box.h) - center).GetRotated(associated.angle / (180 / PI)) + center - Camera::pos;
    points[2] = {(int)point.x, (int)point.y};

    point = (Vec2(box.x, box.y + box.h) - center).GetRotated(associated.angle / (180 / PI)) + center - Camera::pos;
    points[3] = {(int)point.x, (int)point.y};

    SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 255, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawLines(Game::GetInstance().GetRenderer(), points, 5);
#endif
}

bool Collider::Is(std::string type)
{
    return type == "Collider";
}

void Collider::SetScale(Vec2 newScale)
{
    scale = newScale;
}

void Collider::SetOffset(Vec2 newOffset)
{
    offset = newOffset;
}
