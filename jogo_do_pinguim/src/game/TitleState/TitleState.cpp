
#include "TitleState.hpp"
#include "../StageState/StageState.hpp"
#include "../Game/Game.hpp"
#include "../../components/Text/Text.hpp"

TitleState::TitleState()
{
    started = false;
    quitRequested = false;
    popRequested = false;
    // background
    GameObject *bg = new GameObject();
    Sprite *newspr = new Sprite("../public/img/title.jpg", (*bg));
    CameraFollower *newflwr = new CameraFollower(*bg);
    bg->AddComponent(newspr);
    bg->AddComponent(newflwr);
    AddObject(bg);
    // text
    GameObject *text = new GameObject();
    Text *newtxt = new Text((*text), "../public/font/Call me maybe.ttf", 100, Text::TextStyle::SOLID, "Press Space To Start", {255, 255, 255, 255}, 1);
    text->AddComponent(newtxt);
    // CameraFollower* newflwr2=new CameraFollower(*text);
    // text->AddComponent(newflwr2);
    text->box.y = Camera::pos.y + 400;
    text->box.x = Camera::pos.x + 40;
    AddObject(text);
    return;
}

TitleState::~TitleState()
{
    objectArray.clear();
}

void TitleState::LoadAssets()
{
}

void TitleState::Update(float dt)
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
        Game &game = Game::GetInstance();
        game.Push(new StageState());
    }
    Camera::pos.x = 0;
    Camera::pos.y = 0;
    UpdateArray(dt);
    return;
}

void TitleState::Render()
{
    RenderArray();
    return;
}

void TitleState::Start()
{
    LoadAssets();
    StartArray();
    started = true;
    return;
}

void TitleState::Pause()
{
    return;
}

void TitleState::Resume()
{
    return;
}