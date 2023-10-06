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

State::State()
{
    music = nullptr;
    quitRequested = false;
    started = false;

    LoadAssets();
}

void State::LoadAssets()
{
    GameObject *background = new GameObject();
    Sprite *bg = new Sprite("../public/img/ocean.jpg", *background);
    background->box = {0, 0, bg->GetWidth(), bg->GetHeight()};
    background->AddComponent(bg);

    CameraFollower *cameraFollower = new CameraFollower(*background);
    background->AddComponent(cameraFollower);

    GameObject *alien = new GameObject();
    alien->AddComponent(new Alien(*alien, 3));

    objectArray.emplace_back(alien);

    TileSet *tileSet = new TileSet(*background, 64, 64, "../public/img/tileset.png");
    TileMap *tileMap = new TileMap(*background, "../public/map/tileMap.txt", tileSet);

    background->AddComponent(tileMap);

    objectArray.emplace_back(background);

    music = new Music("../public/audio/stageState.ogg");
    music->Play();
}

bool State::QuitRequested()
{
    return quitRequested;
}

State::~State()
{
    objectArray.clear();
}

void State::Update(float dt)
{
    SDL_Delay((int)dt);

    InputManager &input = InputManager::GetInstance();

    if (input.KeyPress(ESCAPE_KEY) || input.QuitRequested())
    {
        quitRequested = true;
    }

    for (unsigned int i = 0; i < objectArray.size(); i++)
    {

        if (objectArray[i]->IsDead())
        {

            objectArray.erase(objectArray.begin() + i);
            i--;
        }
        else
        {
            objectArray[i]->Update(dt);
        }
    }
    // Uptades Camera
    Camera::Update(dt * 1000);
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

std::weak_ptr<GameObject> State::AddObject(GameObject *go)
{
    std::shared_ptr<GameObject> sharedGo(go);
    objectArray.push_back(sharedGo);
    if (started)
    {
        go->Start();
    }
    return std::weak_ptr<GameObject>(sharedGo);
}

std::weak_ptr<GameObject> State::GetObjectPtr(GameObject *go)
{
    for (auto &obj : objectArray)
    {
        if (obj.get() == go)
        {
            return std::weak_ptr<GameObject>(obj);
        }
    }
    return std::weak_ptr<GameObject>(); // Retorna um weak_ptr vazio se não encontrar.
}
