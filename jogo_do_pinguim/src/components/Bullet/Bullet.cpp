#include "Bullet.hpp"
#include "../Collider/Collider.hpp"

Bullet::Bullet(GameObject &associated, float angle, float speed, int damage, float maxDistance, string sprite, bool targetsPlayer, int frameCount) : Component(associated)
{
    Vec2 speedtmp = Vec2(speed, 0);
    associated.angle = angle * 180 / PI;

    this->speed = speedtmp.GetRotated(angle);
    this->targetsPlayer = targetsPlayer;
    distanceLeft = maxDistance;
    this->damage = damage;
    Sprite *spritetmp = new Sprite(sprite, associated, frameCount);

    associated.box.w = spritetmp->GetWidth();
    associated.box.h = spritetmp->GetHeight();
    associated.AddComponent(spritetmp);
    associated.AddComponent(new Collider(associated));
    associated.box.SetCenter(associated.box.GetCenteredVec2() + Vec2(125, 0).GetRotated(angle));
}

void Bullet::Update(float dt)
{
    Vec2 traveledDistance = Vec2(speed.x * dt, speed.y * dt);
    associated.box.SetCenter(associated.box.GetCenteredVec2() + traveledDistance);
    distanceLeft -= traveledDistance.GetMagnitude();
    if (distanceLeft <= 0)
    {
        associated.RequestDelete();
    }
}

void Bullet::Render() {}

bool Bullet::Is(string typeIdentifier)
{
    return typeIdentifier == "Bullet";
}

int Bullet::GetDamage()
{
    return damage;
}
