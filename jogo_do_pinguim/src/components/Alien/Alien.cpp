#include "Alien.hpp"
#include "../../game/Camera/Camera.hpp"
#include "../../game/Game/Game.hpp"
#include "../../game/InputManager/InputManager.hpp"
#include <SDL2/SDL.h>

Alien::Alien(GameObject &associated, int minionCount) : Component(associated)
{
    Sprite *alienSprite = new Sprite("assets/img/alien.png", associated);
    associated.box.h = alienSprite->GetHeight();
    associated.box.w = alienSprite->GetWidth();
    associated.box.SetCenter(512, 300);
    associated.AddComponent(alienSprite);
    this->nMinions = minionCount;
    hp = 30;
    speed = Vec2(0, 0);
}

Alien::~Alien()
{
    minions.clear();
}

void Alien::Start()
{
    for (int i = 0; i < nMinions; i++)
    {
        GameObject *minionObject = new GameObject();
        Sprite *minionSprite = new Sprite("assets/img/minion.png", *minionObject);
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
    int mouseX = InputManager::GetInstance().GetMouseX() + Camera::pos.x;
    int mouseY = InputManager::GetInstance().GetMouseY() + Camera::pos.y;

    if (InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON))
        tasks.push(Action(Action::ActionType::SHOOT, mouseX, mouseY));
    else if (InputManager::GetInstance().MousePress(RIGHT_MOUSE_BUTTON))
        tasks.push(Action(Action::ActionType::MOVE, mouseX, mouseY));

    if (!tasks.empty())
    {
        Action currentAction = tasks.front();
        if (currentAction.type == Action::ActionType::MOVE)
        {
            float moveSpeed = 0.5;
            Vec2 distance = currentAction.pos - associated.box.GetCenteredVec2();
            speed = distance.GetNormalized() * moveSpeed;
            associated.box.SetCenter(associated.box.GetCenteredVec2() + speed * dt);
            if (abs((associated.box.GetCenteredVec2() - currentAction.pos).GetMagnitude()) < 2)
                tasks.pop();
        }
        else if (currentAction.type == Action::ActionType::SHOOT)
        {
            float closestDistance = FLT_MAX;
            Minion *closestMinion = nullptr;

            for (const auto &minionWeakPtr : minions)
            {
                if (auto minionObject = minionWeakPtr.lock())
                {
                    Minion *minion = static_cast<Minion *>(minionObject->GetComponent("Minion"));
                    float distance = abs((minion->GetAssociated().box.GetCenteredVec2() - currentAction.pos).GetMagnitude());
                    if (distance < closestDistance)
                    {
                        closestDistance = distance;
                        closestMinion = minion;
                    }
                }
            }

            closestMinion->Shoot(currentAction.pos);
            tasks.pop();
        }
    }

    if (hp <= 0)
        associated.RequestDelete();

    associated.angle -= (2 * PI * 0.05 * dt / 1000) * 180 / PI;
    if (associated.angle < 0)
        associated.angle += 360;
}

void Alien::Render() {}

bool Alien::Is(string type)
{
    return type == "Alien";
}

Alien::Action::Action(ActionType actionType, float x, float y)
    : type(actionType), pos(x, y) {}
