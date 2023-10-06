#include "Camera.hpp"
#include "../Game/Game.hpp"
#include "../InputManager/InputManager.hpp"

#define SPEED_CONSTANT 100

Vec2 Camera::pos(0, 0);
Vec2 Camera::speed(0, 0);
GameObject *Camera::focus = nullptr;

void Camera::Follow(GameObject *newFocus)
{
    focus = newFocus;
}

void Camera::Unfollow()
{
    focus = nullptr;
}

void Camera::Update(float dt)
{
    float speedamnt = 0.5;
    bool flag[2] = {false, false};
    if (focus != nullptr)
    {
        pos = Vec2(focus->box.x + 1024 / 2 - focus->box.w / 2, focus->box.y + 600 / 2 - focus->box.h / 2);
    }
    else
    {
        if (InputManager::GetInstance().IsKeyDown(LEFT_ARROW_KEY))
        {
            speed.x = -speedamnt;
            flag[0] = true;
        }
        if (InputManager::GetInstance().IsKeyDown(RIGHT_ARROW_KEY))
        {
            speed.x = speedamnt;
            flag[0] = true;
        }
        if (InputManager::GetInstance().IsKeyDown(UP_ARROW_KEY))
        {
            speed.y = -speedamnt;
            flag[1] = true;
        }
        if (InputManager::GetInstance().IsKeyDown(DOWN_ARROW_KEY))
        {
            speed.y = speedamnt;
            flag[1] = true;
        }
        if (!flag[0])
        {
            speed.x = 0;
        }
        if (!flag[1])
        {
            speed.y = 0;
        }
        pos += speed * dt;
    }
}
