#include "PenguinCannon.hpp"
#include "../../game/Game/Game.hpp"
#include "../../game/InputManager/InputManager.hpp"
#include "../Bullet/Bullet.hpp"
#include "../PenguinBody/PenguinBody.hpp"
#include "../Sprite/Sprite.hpp"
#include "../../game/Camera/Camera.hpp"
#include "../../geometry/Vec2/Vec2.hpp"

PenguinCannon::PenguinCannon(GameObject &associated, weak_ptr<GameObject> penguinBody) : Component(associated)
{
    pbody = penguinBody;
}

void PenguinCannon::Update(float dt)
{
    if (pbody.lock() == nullptr)
    {
        associated.RequestDelete();
    }
    else
    {
        auto &p = *pbody.lock();
        associated.box.SetCenter(p.box.GetCenteredVec2());
        Vec2 mousePos(InputManager::GetInstance().GetMouseX(), InputManager::GetInstance().GetMouseY());
        angle = (mousePos + Camera::pos - associated.box.GetCenteredVec2()).GetSlope();
        associated.angle = angle * 180 / PI;
    }
}

void PenguinCannon::Shoot()
{
    GameObject *tmp = new GameObject();
    tmp->box.SetCenter(associated.box.GetCenteredVec2());
    Bullet *bullet = new Bullet(*tmp, angle, 0.5, 10, 1000, "assets/img/penguinbullet.png", false, 4);
    tmp->AddComponent(bullet);
    Game::GetInstance().GetState().AddObject(tmp);
}

void PenguinCannon::Render() {}

bool PenguinCannon::Is(string type)
{
    return type == "PenguinCannon";
}
