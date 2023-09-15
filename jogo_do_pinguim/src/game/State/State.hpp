#ifndef STATE_HPP
#define STATE_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <vector>
#include <memory>

#include "../../components/Sprite/Sprite.hpp"
#include "../Music/Music.hpp"

using namespace std;

class State
{
public:
    State();
    ~State();
    bool QuitRequested();
    void LoadAssets();
    void Update(float dt);
    void Render();

private:
    Music *music;
    bool quitRequested;
    vector<unique_ptr<GameObject>> objectArray;

    void Input();
    void AddObject(int mouseX, int mouseY);
};

#endif