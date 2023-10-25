#include "State.hpp"
#include "../../geometry/Rect/Rect.hpp"
#include "../../geometry/Vec2/Vec2.hpp"
#include "../../components/Sound/Sound.hpp"
#include "../../components/TileMap/TileMap.hpp"
#include "../../components/TileSet/TileSet.hpp"
#include "../InputManager/InputManager.hpp"
#include "../Camera/Camera.hpp"
#include "../../components/CameraFollower/CameraFollower.hpp"
#include "../../components/Alien/Alien.hpp"
#include "../../components/Resources/Resources.hpp"
#include "../../components/PenguinBody/PenguinBody.hpp"
#include "../../components/PenguinCannon/PenguinCannon.hpp"
#include "../../components/Collider/Collider.hpp"

State::State()
{
    music = nullptr;
    quitRequested = false;
    started = false;
}

void State::LoadAssets()
{
    GameObject *background = new GameObject();
    Sprite *bg = new Sprite("../public/img/ocean.jpg", *background);
    background->box = {0, 0, bg->GetWidth(), bg->GetHeight()};
    background->AddComponent(bg);

    TileSet *tileSet = new TileSet(*background, 64, 64, "../public/img/tileset.png");
    TileMap *tileMap = new TileMap(*background, "../public/map/tileMap.txt", tileSet);
    background->AddComponent(tileMap);

    CameraFollower *cameraFollower = new CameraFollower(*background);
    background->AddComponent(cameraFollower);

    GameObject *alien = new GameObject();
    alien->AddComponent(new Alien(*alien, 3));

    GameObject *penguin = new GameObject();
    Sprite *penguinsprite = new Sprite("../public/img/penguin.png", *penguin);
    penguin->box.SetCenter(704, 640);
    penguin->box.h = penguinsprite->GetHeight();
    penguin->box.w = penguinsprite->GetWidth();
    penguin->AddComponent(penguinsprite);
    penguin->AddComponent(new PenguinBody(*penguin));

    objectArray.emplace_back(penguin);
    objectArray.emplace_back(background);
    objectArray.emplace_back(alien);

    music = new Music("../public/audio/stageState.ogg");
    music->Play();
}

bool State::QuitRequested()
{
    return quitRequested;
}

State::~State()
{
    Resources::ClearImages();
    Resources::ClearMusics();
    Resources::ClearSounds();
    objectArray.clear();
}

void State::Update(float dt)
{
    quitRequested = false;

    if (InputManager::GetInstance().QuitRequested())
    {
        quitRequested = true;
    }

    else if (InputManager::GetInstance().KeyPress(ESCAPE_KEY))
    {
        quitRequested = true;
    }
    for (int i = 0; i < objectArray.size(); i++)
    {
        objectArray[i]->Update(dt);
    }
    for (unsigned int i = 0; i < objectArray.size(); i++)
    {
        Collider *a = (Collider *)objectArray[i]->GetComponent("Collider");
        if (a != nullptr)
        {
            for (unsigned int j = i + 1; j < objectArray.size(); j++)
            {
                Collider *b = (Collider *)objectArray[j]->GetComponent("Collider");
                if (b != nullptr)
                {
                    if (Collision::IsColliding(a->box, b->box, a->associated.angleDeg, b->associated.angleDeg))
                    {
                        objectArray[i]->NotifyCollision(*objectArray[j]);
                        objectArray[j]->NotifyCollision(*objectArray[i]);
                    }
                }
            }
        }
    }
    for (int i = 0; i < objectArray.size(); i++)
    {
        if (objectArray[i]->IsDead())
        {
            objectArray.erase(objectArray.begin() + i);
            i--;
        }
    }
    Camera::Update(dt);
}

void State::Render()
{
    for (int i = 0; i < objectArray.size(); i++)
    {
        objectArray[i]->Render();
    }
}

void State::Start()
{
    LoadAssets();
    for (auto &obj : objectArray)
    {
        obj->Start();
    }
    started = true;
}

weak_ptr<GameObject> State::AddObject(GameObject *go)
{
    shared_ptr<GameObject> sharedGo(go);
    objectArray.emplace_back(sharedGo);
    if (!sharedGo->started)
    {
        sharedGo->Start();
    }
    return weak_ptr<GameObject>(sharedGo);
}

weak_ptr<GameObject> State::GetObjectPtr(GameObject *go)
{
    for (auto &obj : objectArray)
    {
        if (obj.get() == go)
        {
            return weak_ptr<GameObject>(obj);
        }
    }
    return weak_ptr<GameObject>();
}
