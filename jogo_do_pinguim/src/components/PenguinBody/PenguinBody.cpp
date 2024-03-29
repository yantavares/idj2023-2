#include "PenguinBody.hpp"
#include "../PenguinCannon/PenguinCannon.hpp"
#include "../../game/Game/Game.hpp"
#include "../../game/InputManager/InputManager.hpp"
#include "../Collider/Collider.hpp"
#include "../../game/Camera/Camera.hpp"
#include "../Sound/Sound.hpp"
#include "../Bullet/Bullet.hpp"

PenguinBody *PenguinBody::player = nullptr;

PenguinBody::PenguinBody(GameObject &associated) : Component(associated)
{
    dead = false;

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
    if (InputManager::GetInstance().IsKeyDown(W_KEY) && linearSpeed < MAX_SPEED)
        linearSpeed += CONST_ACCELERATION * dt;
    else if (InputManager::GetInstance().IsKeyDown(S_KEY) && linearSpeed > -MAX_SPEED)
        linearSpeed -= CONST_ACCELERATION * dt;
    if (InputManager::GetInstance().IsKeyDown(A_KEY))
        angle -= ANGULAR_SPEED * dt;
    else if (InputManager::GetInstance().IsKeyDown(D_KEY))
        angle += ANGULAR_SPEED * dt;
    speed = Vec2(linearSpeed, 0).GetRotated(angle);
    associated.angle = angle * 180 / PI;
    associated.box.SetCenter(associated.box.GetCenteredVec2() + speed * dt);

    if (hp <= 0 && !dead)
    {
        Camera::Unfollow();

        associated.RemoveComponent("Sprite");

        auto cannon = pcannon.lock();
        cannon->RemoveComponent("Sprite");

        Sprite *sprite = new Sprite("../public/img/penguindeath.png", associated, 5, 0.2, 1);
        associated.box.w = sprite->GetWidth();
        associated.box.h = sprite->GetHeight();
        associated.box.SetCenter(associated.box.GetCenteredVec2());
        associated.AddComponent(sprite);

        Sound *boom = new Sound(associated, "../public/audio/boom.wav");
        boom->Play();
        associated.AddComponent(boom);

        linearSpeed = 0;
        dead = true;
    }
}

void PenguinBody::NotifyCollision(GameObject &other)
{
    Bullet *bullet = (Bullet *)other.GetComponent("Bullet");
    if (bullet != nullptr && bullet->targetsPlayer)
    {
        hp -= bullet->GetDamage();
    }
}