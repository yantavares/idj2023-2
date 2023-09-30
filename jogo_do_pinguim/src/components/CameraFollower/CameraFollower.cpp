#include "CameraFollower.hpp"
#include "../../game/Camera/Camera.hpp"

CameraFollower::CameraFollower(GameObject &associated) : Component(associated) {}

void CameraFollower::Update(float dt)
{
    associated.box.x = Camera::pos.x;
    associated.box.y = Camera::pos.y;
}

bool CameraFollower::Is(string type)
{
    return type == "CameraFollower";
}
