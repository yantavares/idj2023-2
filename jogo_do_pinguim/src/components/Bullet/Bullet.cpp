#include "Bullet.hpp"

Bullet::Bullet(GameObject &associated, float angle, float bulletSpeed, int damageValue, float maxTravelDistance, string bulletSprite, int frameCount, float frameTime)
    : Component(associated)
{
    Vec2 calculatedSpeed = Vec2(bulletSpeed, 0);
    associated.angle = angle * 180 / PI;
    speed = calculatedSpeed.GetRotated(angle);
    distanceLeft = maxTravelDistance;
    damage = damageValue;
    Sprite *bulletImage = new Sprite(bulletSprite, associated);
    associated.box.w = bulletImage->GetWidth();
    associated.box.h = bulletImage->GetHeight();
    associated.AddComponent(bulletImage);
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
