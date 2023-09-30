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
    if (focus)
    {
        // Center the camera on the focus object
        pos.x = focus->box.x - Game::GetInstance().GetWidth() / 2 + focus->box.w / 2;
        pos.y = focus->box.y - Game::GetInstance().GetHeight() / 2 + focus->box.h / 2;
    }
    else
    {
        InputManager &input = InputManager::GetInstance();

        if (input.IsKeyDown(LEFT_ARROW_KEY))
        {
            speed.x = -SPEED_CONSTANT;
        }
        else if (input.IsKeyDown(RIGHT_ARROW_KEY))
        {
            speed.x = SPEED_CONSTANT;
        }
        else
        {
            speed.x = 0;
        }

        if (input.IsKeyDown(UP_ARROW_KEY))
        {
            speed.y = -SPEED_CONSTANT;
        }
        else if (input.IsKeyDown(DOWN_ARROW_KEY))
        {
            speed.y = SPEED_CONSTANT;
        }
        else
        {
            speed.y = 0;
        }

        pos.x += speed.x * dt;
        pos.y += speed.y * dt;
    }
}
