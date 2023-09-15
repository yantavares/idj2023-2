#include "Face.hpp"
#include "../Sprite/Sprite.hpp"
#include "../Sound/Sound.hpp"
#include "../../game/Game/Game.hpp"

Face::Face(GameObject &associated) : Component(associated)
{
    hitpoints = 30;
}

void Face::Damage(int damage)
{
    hitpoints -= damage;
    if (hitpoints <= 0)
    {
        associated.RequestDelete();
        Component *sound = associated.GetComponent("Sound");
        if (sound != nullptr)
        {
            ((Sound *)sound)->Play();
        }
    }
}

void Face::Update(float dt)
{
}

void Face::Render()
{
}

bool Face::Is(string type)
{
    return type == "Face";
}
