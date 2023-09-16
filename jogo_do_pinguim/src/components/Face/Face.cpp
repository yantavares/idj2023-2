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
        Sound *sound = (Sound *)associated.GetComponent("Sound");
        associated.RequestDelete();
        if (sound != nullptr)
        {
            sound->Play();

            // Others solutions didnt work :(
            SDL_Delay(1000);
        }
        associated.RemoveComponent(sound);
    }
}

void Face::Update(float dt)
{
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
