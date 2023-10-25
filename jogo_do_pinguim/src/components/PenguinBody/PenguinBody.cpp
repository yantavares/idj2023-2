#include "PenguinBody.hpp"
#include "../PenguinCannon/PenguinCannon.hpp"
#include "../../game/Game/Game.hpp"
#include "../../game/InputManager/InputManager.hpp"

PenguinBody *PenguinBody::player = nullptr;

PenguinBody::PenguinBody(GameObject &associated) : Component(associated)
{
    speed = Vec2(0, 0);
    linearSpeed = 0;
    angle = 0;
    hp = 20;
    player = this;
}

PenguinBody::~PenguinBody()
{
    player = nullptr;
}

void PenguinBody::Render() {}

bool PenguinBody::Is(string type)
{
    return type == "PenguinBody";
}

void PenguinBody::Start()
{
    auto penguinPass = Game::GetInstance().GetState().GetObjectPtr(&associated);
    GameObject *tmp = new GameObject();
    Sprite *sprite = new Sprite("assets/img/cubngun.png", *tmp);
    tmp->box.h = sprite->GetHeight();
    tmp->box.w = sprite->GetWidth();
    tmp->box.SetCenter(associated.box.GetCenteredVec2());
    tmp->AddComponent(sprite);
    tmp->AddComponent(new PenguinCannon(*tmp, penguinPass));
    pcannon = Game::GetInstance().GetState().AddObject(tmp);
}

void PenguinBody::Update(float dt)
{
    InputManager &input = InputManager::GetInstance();

    if (input.IsKeyDown('W'))
    {
        linearSpeed += dt * CONST_ACCELERATION;
    }
    if (input.IsKeyDown('S'))
    {
        linearSpeed -= dt * CONST_ACCELERATION;
    }

    if (linearSpeed > MAX_SPEED)
        linearSpeed = MAX_SPEED;
    if (linearSpeed < -MAX_SPEED)
        linearSpeed = -MAX_SPEED;

    if (input.IsKeyDown('A'))
    {
        angle -= dt * ANGULAR_SPEED;
    }
    if (input.IsKeyDown('D'))
    {
        angle += dt * ANGULAR_SPEED;
    }

    speed.x = linearSpeed * cos(angle);
    speed.y = linearSpeed * sin(angle);
    associated.box.SetCenter(associated.box.GetCenteredVec2() + speed * dt);

    if (hp <= 0)
    {
        associated.RequestDelete();
        if (auto cannon = pcannon.lock())
        {
            cannon->RequestDelete();
        }
    }
}