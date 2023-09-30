#include "Sprite.hpp"
#include "../../game/Game/Game.hpp"
#include "../Resources/Resources.hpp"
#include "../../game/Camera/Camera.hpp"

Sprite::Sprite(GameObject &associated) : Component(associated)
{
    texture = nullptr;
}

Sprite::Sprite(string file, GameObject &associated) : Component(associated)
{
    texture = nullptr;
    Open(file);
    SetClip(0, 0, width, height);
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
    dstRect.h = height;
    dstRect.w = width;
    SDL_RenderCopy(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstRect);
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
    return clipRect.w;
}

int Sprite::GetHeight()
{
    return clipRect.h;
}

bool Sprite::IsOpen()
{
    return texture != nullptr;
}

void Sprite::Update(float dt)
{
}

bool Sprite::Is(string type)
{
    return type == "Sprite" ? true : false;
}