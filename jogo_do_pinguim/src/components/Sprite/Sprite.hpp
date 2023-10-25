#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "../Component/Component.hpp"
#include "../Timer/Timer.hpp"

using namespace std;

class Sprite : public Component
{
public:
    Sprite(GameObject &associated);
    Sprite(string file, GameObject &associated, int frameCount = 1, float frameTime = 1, float secondsToSelfDestruct = 0);

    ~Sprite();
    void Open(string file);
    void SetClip(int x, int y, int w, int h);
    void Render();
    void Render(float x, float y, float w, float h);
    int GetWidth();
    int GetHeight();
    bool IsOpen();
    void Update(float dt);
    void SetFrame(int frame);
    void SetFrameCount(int frameCount);
    void SetFrameTime(float frameTime);
    bool Is(string type);
    void SetScale(float scaleX, float scaleY);

private:
    SDL_Texture *texture;
    int width;
    int height;
    SDL_Rect clipRect;
    Vec2 scale;

    string file;

    int frameCount;
    float frameTime;
    int currentFrame;
    float timeElapsed;

    Timer selfDestructCount;
    float secondsToSelfDestruct;
};

#endif