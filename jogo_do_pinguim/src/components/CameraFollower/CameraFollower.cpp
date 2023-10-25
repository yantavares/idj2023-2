#include "CameraFollower.hpp"
#include "../../game/Camera/Camera.hpp"

CameraFollower::CameraFollower(GameObject &associated) : Component(associated) {}

void CameraFollower::Update(float dt)
{
    associated.box.SetCenter(Camera::pos + Vec2(1024, 600) / 2);
}

bool CameraFollower::Is(string type)
{
    return type == "CameraFollower";
}
