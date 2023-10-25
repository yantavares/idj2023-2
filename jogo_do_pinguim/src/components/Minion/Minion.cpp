#include "Minion.hpp"
#include "../../game/Game/Game.hpp"
#include "../Bullet/Bullet.hpp"

Minion::Minion(GameObject &associated, GameObject &alien, float arcOffsetDeg) : Component(associated), alien(alien)
{
    arc = arcOffsetDeg;
}

void Minion::Update(float dt)
{
    Vec2 pos = Vec2(150, 0);
    float rotationSpeedFactor = 0.5;
    pos = pos.GetRotated(arc);
    pos += alien.box.GetCenteredVec2();
    associated.box.SetCenter(pos);
    associated.angle = arc * 180 / PI - 90;
    arc += 2 * PI * rotationSpeedFactor * dt / 1000;
    if (arc > 2 * PI)
        arc -= 2 * PI;
}

void Minion::Render() {}

bool Minion::Is(string type)
{
    return type == "Minion";
}

void Minion::Shoot(Vec2 pos)
{
    Vec2 shootDir = pos - associated.box.GetCenteredVec2();
    GameObject *bulletObj = new GameObject();
    bulletObj->box.x = associated.box.GetCenteredVec2().x;
    bulletObj->box.y = associated.box.GetCenteredVec2().y;
    Bullet *bullet = new Bullet(*bulletObj, shootDir.GetSlope(), 0.5, 10, 1000, "../public/img/minionbullet2.png");
    bulletObj->AddComponent(bullet);
    Game::GetInstance().GetState().AddObject(bulletObj);
}