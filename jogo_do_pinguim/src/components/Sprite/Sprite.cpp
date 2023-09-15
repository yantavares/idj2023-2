#include "Sprite.hpp"
#include "../../game/Game/Game.hpp"

Sprite::Sprite(GameObject &associated) : Component(associated)
{
    texture = nullptr;
}

Sprite::Sprite()
{
    texture = nullptr;
}

Sprite::Sprite(string file, GameObject &associated) : Component(associated)
{
    texture = nullptr;
    Open(file);
}

Sprite::~Sprite()
{
    if (texture != nullptr)
    {
        SDL_DestroyTexture(texture);
    }
}

void Sprite::Open(string file)
{
    if (texture != nullptr)
    {
        SDL_DestroyTexture(texture);
    }
    texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());
    if (texture == nullptr)
    {
        cerr << "Failed to load texture: " << SDL_GetError() << endl;
        return;
    }
    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
}

void Sprite::SetClip(int x, int y, int w, int h)
{
    clipRect.x = x;
    clipRect.y = y;
    clipRect.w = w;
    clipRect.h = h;
}

void Sprite::Render(int x, int y)
{
    SDL_Rect dstRect = {x, y, clipRect.w, clipRect.h};
    SDL_Renderer *renderer = Game::GetInstance().GetRenderer();
    SDL_RenderCopy(renderer, texture, &clipRect, &dstRect);
    SetClip(x, y, width, height);
}

int Sprite::GetWidth()
{
    return width;
}

int Sprite::GetHeight()
{
    return height;
}

bool Sprite::IsOpen()
{
    return texture != nullptr;
}