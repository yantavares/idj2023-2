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

    void Start();

    weak_ptr<GameObject> AddObject(GameObject *go);
    weak_ptr<GameObject> GetObjectPtr(GameObject *go);

private:
    Music *music;
    bool quitRequested;

    void Input();

    bool started;
    vector<shared_ptr<GameObject>> objectArray;
};

#endif