#ifndef StageState_HPP
#define StageState_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <vector>
#include <memory>

#include "../../components/Sprite/Sprite.hpp"
#include "../State/State.hpp"
#include "../Music/Music.hpp"

using namespace std;

class StageState : public State
{
public:
    StageState();
    ~StageState();
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