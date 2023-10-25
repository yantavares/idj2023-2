#include "Sprite.hpp"
#include "../../game/Game/Game.hpp"
#include "../Resources/Resources.hpp"
#include "../../game/Camera/Camera.hpp"

Sprite::Sprite(GameObject &associated) : Component(associated)
{
    texture = nullptr;
    scale = Vec2(1, 1);
}

Sprite::Sprite(string file, GameObject &associated, int frameCount, float frameTime) : Component(associated)
{
    this->frameCount = frameCount;
    this->frameTime = frameTime;
    this->currentFrame = 0;
    this->timeElapsed = 0;
    texture = nullptr;
    Open(file);
    SetClip(0, 0, width, height);
    scale = Vec2(1, 1);
}

Sprite::~Sprite()
{
    /*     if (texture != nullptr)
        {
            SDL_DestroyTexture(texture);
        } */
}

void Sprite::Open(string file)
{
    /*     if (texture != nullptr)
        {
            SDL_DestroyTexture(texture);
        }
        texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());
        if (texture == nullptr)
        {
            cerr << "Failed to load texture: " << SDL_GetError() << endl;
            return;
        }
        SDL_QueryTexture(texture, nullptr, nullptr, &width, &height); */

    texture = Resources::GetImage(file);
    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
    this->file = file;
}

void Sprite::SetClip(int x, int y, int w, int h)
{
    clipRect.x = x;
    clipRect.y = y;
    clipRect.w = w;
    clipRect.h = h;
}

void Sprite::Render()
{
    SDL_Rect dstRect;
    dstRect.x = associated.box.x - Camera::pos.x;
    dstRect.y = associated.box.y - Camera::pos.y;
    dstRect.h = height * scale.y;
    dstRect.w = width * scale.x;
    SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstRect, associated.angle, nullptr, SDL_FLIP_NONE);
}

void Sprite::Render(float x, float y, float w, float h)
{
    SDL_Rect dstRect;
    dstRect.x = x;
    dstRect.y = y;
    dstRect.h = h;
    dstRect.w = w;
    SDL_RenderCopy(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstRect);
}

int Sprite::GetWidth()
{
    return width / frameCount * scale.x;
}

int Sprite::GetHeight()
{
    return height * scale.y;
}

bool Sprite::IsOpen()
{
    return texture != nullptr;
}

bool Sprite::Is(string type)
{
    return type == "Sprite" ? true : false;
}

void Sprite::SetScale(float scaleX, float scaleY)
{
    scale = Vec2(scaleX, scaleY);
    Vec2 center = associated.box.GetCenteredVec2();
    associated.box.x *= scale.x;
    associated.box.y *= scale.y;
    associated.box.SetCenter(center);
}

void Sprite::Update(float dt)
{
    timeElapsed += dt;
    if (timeElapsed > frameTime)
    {
        timeElapsed = 0;

        currentFrame++;

        if (currentFrame > frameCount - 1)
        {
            currentFrame = 0;
        }
        SetFrame(currentFrame);
    }
}

void Sprite::SetFrame(int frame)
{
    int x = frame * GetWidth();
    int y = 0;
    int w = GetWidth();
    int h = GetHeight();
    SetClip(x, y, w, h);
}

void Sprite::SetFrameCount(int frameCount)
{
    this->frameCount = frameCount;
}

void Sprite::SetFrameTime(float frameTime)
{
    this->frameTime = frameTime;
}