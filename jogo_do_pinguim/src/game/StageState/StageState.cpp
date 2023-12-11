#include "StageState.hpp"
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
#include "../Collision/Collision.hpp"

StageState::StageState()
{
    music = nullptr;
    quitRequested = false;
    started = false;
}

void StageState::LoadAssets()
{
    GameObject *background = new GameObject();
    Sprite *bg = new Sprite("../public/img/ocean.jpg", *background);
    background->box = {0, 0, bg->GetWidth(), bg->GetHeight()};
    background->AddComponent(bg);

    GameObject *tileMap = new GameObject();
    TileSet *ts = new TileSet(*tileMap, 64, 64, "../public/img/tileset.png");
    TileMap *tm = new TileMap(*tileMap, "../public/map/tileMap.txt", ts);
    tileMap->AddComponent(tm);

    CameraFollower *cameraFollower = new CameraFollower(*background);
    background->AddComponent(cameraFollower);

    GameObject *alien = new GameObject();
    alien->AddComponent(new Alien(*alien, 3));
    alien->box.SetCenter(512, 300);

    GameObject *penguin = new GameObject();
    Sprite *penguinsprite = new Sprite("../public/img/penguin.png", *penguin);
    penguin->box.SetCenter(704, 640);
    penguin->box.h = penguinsprite->GetHeight();
    penguin->box.w = penguinsprite->GetWidth();
    penguin->AddComponent(penguinsprite);
    penguin->AddComponent(new PenguinBody(*penguin));

    objectArray.emplace_back(background);
    objectArray.emplace_back(tileMap);
    objectArray.emplace_back(alien);
    objectArray.emplace_back(penguin);

    music = new Music("../public/audio/stageStageState.ogg");
    music->Play();
}

bool StageState::QuitRequested()
{
    return quitRequested;
}

StageState::~StageState()
{
    Resources::ClearImages();
    Resources::ClearMusics();
    Resources::ClearSounds();
    objectArray.clear();
}

void StageState::Update(float dt)
{
    quitRequested = false;
    Camera::Update(dt);

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
    for (int i = 0; i < objectArray.size(); i++)
    {
        Collider *a = (Collider *)objectArray[i]->GetComponent("Collider");
        if (a != nullptr)
        {
            for (int j = i + 1; j < objectArray.size(); j++)
            {
                Collider *b = (Collider *)objectArray[j]->GetComponent("Collider");
                if (b != nullptr)
                {
                    if (Collision::IsColliding(a->box, b->box, a->GetAssociated().angle, b->GetAssociated().angle))
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

void StageState::Render()
{
    TileMap *tm1;
    TileMap *tm;
    for (int i = 0; i < objectArray.size(); i++)
    {
        tm1 = (TileMap *)objectArray[i]->GetComponent("TileMap");
        if (tm1 != nullptr)
        {
            tm = tm1;
            tm->RenderLayer(0, Camera::pos.x, Camera::pos.y);
        }
        else
            objectArray[i]->Render();
    }
    if (tm != nullptr)
    {
        tm->RenderLayer(1, Camera::pos.x, Camera::pos.y);
    }
}

void StageState::Start()
{
    LoadAssets();
    for (int i = 0; i < objectArray.size(); i++)
    {
        objectArray[i]->Start();
    }
    started = true;
}

weak_ptr<GameObject> StageState::AddObject(GameObject *go)
{
    shared_ptr<GameObject> sharedGo(go);
    objectArray.emplace_back(sharedGo);
    if (!sharedGo->started)
    {
        sharedGo->Start();
    }
    return weak_ptr<GameObject>(sharedGo);
}

weak_ptr<GameObject> StageState::GetObjectPtr(GameObject *go)
{
    for (int i = 0; i < objectArray.size(); i++)
    {
        if (objectArray[i].get() == go)
        {

            return weak_ptr<GameObject>(objectArray[i]);
        }
    }
    return weak_ptr<GameObject>();
}
