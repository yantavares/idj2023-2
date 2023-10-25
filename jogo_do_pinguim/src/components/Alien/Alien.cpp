#include "Alien.hpp"
#include "../../game/Camera/Camera.hpp"
#include "../../game/Game/Game.hpp"
#include "../../game/InputManager/InputManager.hpp"
#include "../PenguinBody/PenguinBody.hpp"
#include "../Sound/Sound.hpp"
#include <SDL2/SDL.h>

int Alien::alienCount = 0;

Alien::Alien(GameObject &associated, int minionCount) : Component(associated)
{
    Sprite *alienSprite = new Sprite("../public/img/alien.png", associated);
    associated.box.h = alienSprite->GetHeight();
    associated.box.w = alienSprite->GetWidth();
    associated.box.SetCenter(512, 300);
    associated.AddComponent(alienSprite);
    this->nMinions = minionCount;
    hp = 30;
    speed = Vec2(0, 0);

    alienCount++;
    state = RESTING;
}

Alien::~Alien()
{
    minions.clear();
    alienCount--;
}

void Alien::Start()
{
    for (int i = 0; i < nMinions; i++)
    {
        GameObject *minionObject = new GameObject();
        Sprite *minionSprite = new Sprite("../public/img/minion.png", *minionObject);
        float scale = (rand() % 5 + 10) / 10.0;
        minionSprite->SetScale(scale, scale);
        minionObject->box.w = minionSprite->GetWidth();
        minionObject->box.h = minionSprite->GetHeight();
        minionObject->box.x = associated.box.x;
        minionObject->box.y = associated.box.y;
        minionObject->AddComponent(minionSprite);
        minionObject->AddComponent(new Minion(*minionObject, associated, i * 2 * PI / nMinions));
        minions.push_back(Game::GetInstance().GetState().AddObject(minionObject));
    }
}

void Alien::Update(float dt)
{
    if (state == RESTING)
    {
        restTimer.Update(dt);
        if (restTimer.Get() > 5)
        {
            if (PenguinBody::player != nullptr)
            {
                destination = PenguinBody::player->GetAssociated().box.GetCenteredVec2();
                speed = (destination - associated.box.GetCenteredVec2()).GetNormalized();
                speed = speed * 0.5;
                state = MOVING;
            }
        }
    }
    if (state == MOVING)
    {
        associated.box.SetCenter(associated.box.GetCenteredVec2() + speed * dt);
        if ((associated.box.GetCenteredVec2() - destination).GetMagnitude() < dt)
        {
            destination = PenguinBody::player->GetAssociated().box.GetCenteredVec2();
            Minion *selected = nullptr;
            float min = FLT_MAX;
            for (unsigned int i = 0; i < minions.size(); i++)
            {
                shared_ptr<GameObject> tmp = minions[i].lock();
                float dist = (tmp->box.GetCenteredVec2() - destination).GetMagnitude();
                if (dist < min)
                {
                    selected = (Minion *)tmp->GetComponent("Minion");
                    min = dist;
                }
            }
            selected->Shoot(PenguinBody::player->GetAssociated().box.GetCenteredVec2());
            state = RESTING;
            restTimer.Restart();
        }
    }
    if (hp <= 0)
    {
        associated.RemoveComponent("Sprite");
        Sprite *sprite = new Sprite("../public/img/aliendeath.png", associated, 4, 0.25, 1.25);
        associated.box.w = sprite->GetWidth();
        associated.box.h = sprite->GetHeight();
        associated.box.SetCenter(associated.box.GetCenteredVec2());
        associated.AddComponent(sprite);
        Sound *boom = new Sound(associated, "../public/audio/boom.wav");
        boom->Play();
        for (unsigned int i = 0; i < minions.size(); i++)
        {
            auto minion = minions[i].lock();
            Sprite *minionsprite = new Sprite("../public/img/miniondeath.png", *minion, 4, 0.25, 1);
            minion->box.w = minionsprite->GetWidth();
            minion->box.h = minionsprite->GetHeight();
            minion->RemoveComponent("Sprite");
            minion->AddComponent(minionsprite);
        }
        associated.AddComponent(boom);
    }
    associated.angle -= (2 * PI * 0.05 * dt / 1000) * 180 / PI;
    if (associated.angle < 0)
    {
        associated.angle += 360;
    }
}

void Alien::Render() {}

bool Alien::Is(string type)
{
    return type == "Alien";
}

Alien::Action::Action(ActionType actionType, float x, float y)
    : type(actionType), pos(x, y) {}
