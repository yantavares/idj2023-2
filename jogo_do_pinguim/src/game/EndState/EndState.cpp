#include "EndState.hpp"
#include "../Game/Game.hpp"
#include "../../components/Text/Text.hpp"
#include "../Camera/Camera.hpp"
#include "../GameData/GameData.hpp"

EndState::EndState()
{
    started = false;
    quitRequested = false;
    popRequested = false;
    if (GameData::playerVictory)
    {
        // background
        GameObject *bg = new GameObject();
        Sprite *newspr = new Sprite("../public/img/win.jpg", *bg);
        CameraFollower *newflwr = new CameraFollower(*bg);
        bg->AddComponent(newspr);
        bg->AddComponent(newflwr);
        AddObject(bg);
        GameObject *text = new GameObject();
        Text *newtxt = new Text(*text, "../public/font/Call me maybe.ttf", 55, Text::TextStyle::SOLID, "Press Space to Try Again, or ESC to Quit", {255, 255, 255, 255}, 1);
        text->AddComponent(newtxt);
        text->box.y = 500;
        text->box.x = 30;
        AddObject(text);
        backgroundMusic.Open("../public/audio/endStateWin.ogg");
        backgroundMusic.Play();
    }
    else
    {

        GameObject *bg = new GameObject();
        Sprite *newspr = new Sprite("../public/img/lose.jpg", *bg);
        CameraFollower *newflwr = new CameraFollower(*bg);
        bg->AddComponent(newspr);
        bg->AddComponent(newflwr);
        AddObject(bg);

        GameObject *text = new GameObject();
        Text *newtxt = new Text((*text), "../public/font/Call me maybe.ttf", 55, Text::TextStyle::SOLID, "Press Space to Try Again, or ESC to Quit", {255, 255, 255, 255}, 1);
        text->AddComponent(newtxt);

        text->box.y = 10;
        text->box.x = 30;
        AddObject(text);

        backgroundMusic.Open("../public/audio/endStateLose.ogg");
        backgroundMusic.Play();
    }
    return;
}

EndState::~EndState()
{
    objectArray.clear();
}

void EndState::LoadAssets()
{
}

void EndState::Update(float dt)
{
    if (InputManager::GetInstance().KeyPress(ESCAPE_KEY))
    {
        quitRequested = true;
    }
    if (InputManager::GetInstance().QuitRequested())
    {
        quitRequested = true;
    }
    if (InputManager::GetInstance().KeyPress(SDLK_SPACE))
    {
        popRequested = true;
    }
    Camera::pos.x = 0;
    Camera::pos.y = 0;
    UpdateArray(dt);
    return;
}

void EndState::Render()
{
    RenderArray();
    return;
}

void EndState::Start()
{
    LoadAssets();
    StartArray();
    started = true;
    return;
}

void EndState::Pause()
{
    return;
}

void EndState::Resume()
{
    return;
}