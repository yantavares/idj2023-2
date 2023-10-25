#include "PenguinBody.hpp"
#include "../PenguinCannon/PenguinCannon.hpp"
#include "../../game/Game/Game.hpp"
#include "../../game/InputManager/InputManager.hpp"
#include "../Collider/Collider.hpp"
#include "../../game/Camera/Camera.hpp"
#include "../Sound/Sound.hpp"

PenguinBody *PenguinBody::player = nullptr;

PenguinBody::PenguinBody(GameObject &associated) : Component(associated)
{
    speed = Vec2(0, 0);
    linearSpeed = 0;
    angle = 0;
    hp = 20;
    player = this;
    associated.AddComponent(new Collider(associated));
    Camera::Follow(&associated);
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
    Sprite *sprite = new Sprite("../public/img/cubngun.png", *tmp);
    tmp->box.h = sprite->GetHeight();
    tmp->box.w = sprite->GetWidth();
    tmp->box.SetCenter(associated.box.GetCenteredVec2());
    tmp->AddComponent(sprite);
    tmp->AddComponent(new PenguinCannon(*tmp, penguinPass));
    pcannon = Game::GetInstance().GetState().AddObject(tmp);
}

void PenguinBody::Update(float dt)
{
    if (InputManager::GetInstance().IsKeyDown(W_KEY) && linearSpeed < 0.25)
        linearSpeed += 0.01;
    else if (InputManager::GetInstance().IsKeyDown(S_KEY) && linearSpeed > -0.25)
        linearSpeed -= 0.01;
    if (InputManager::GetInstance().IsKeyDown(A_KEY))
        angle -= 0.001 * dt;
    else if (InputManager::GetInstance().IsKeyDown(D_KEY))
        angle += 0.001 * dt;
    speed = Vec2(linearSpeed, 0).GetRotated(angle);
    associated.angle = angle * 180 / PI;
    associated.box.SetCenter(associated.box.GetCenteredVec2() + speed * dt);
    if (hp <= 0)
    {
        Camera::Unfollow();
        associated.RemoveComponent("Sprite");
        auto cannon = pcannon.lock();
        cannon->RemoveComponent("Sprite");
        Sprite *sprite = new Sprite("assets/img/penguindeath.png", associated, 5, 0.2, 1);
        associated.box.w = sprite->GetWidth();
        associated.box.h = sprite->GetHeight();
        associated.box.SetCenter(associated.box.GetCenteredVec2());
        associated.AddComponent(sprite);
        Sound *boom = new Sound(associated, "assets/audio/boom.wav");
        boom->Play();
        associated.AddComponent(boom);
        linearSpeed = 0;
    }
}