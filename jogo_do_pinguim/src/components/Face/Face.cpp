#include "Face.hpp"
#include "../Sprite/Sprite.hpp"
#include "../Sound/Sound.hpp"
#include "../../game/Game/Game.hpp"
#include "../../game/InputManager/InputManager.hpp"
#include "../../game/Camera/Camera.hpp"

Face::Face(GameObject &associated) : Component(associated)
{
    hitpoints = 30;
}

void Face::Damage(int damage)
{
    hitpoints -= damage;
    if (hitpoints <= 0)
    {
        cout << "x_x" << endl;
        Sound *sound = (Sound *)associated.GetComponent("Sound");
        if (sound != nullptr)
        {
            sound->Play();
            // Others solutions didnt work :(
            SDL_Delay(1000);
        }
        associated.RequestDelete();
        associated.RemoveComponent(sound);
    }
}

void Face::Update(float dt)
{
    InputManager &input = InputManager::GetInstance();

    if (input.MousePress(LEFT_MOUSE_BUTTON))
    {
        int mouseX = input.GetMouseX() + Camera::pos.x;
        int mouseY = input.GetMouseY() + Camera::pos.y;

        if (mouseX >= associated.box.x && mouseX < associated.box.x + associated.box.w &&
            mouseY >= associated.box.y && mouseY < associated.box.y + associated.box.h)
        {
            cout << "Ouch" << endl;

            Damage(rand() % 10 + 1); // Damage 1-10
        }
    }
}

Face::~Face()
{
}

void Face::Render()
{
}

bool Face::Is(string type)
{
    return type == "Face";
}
