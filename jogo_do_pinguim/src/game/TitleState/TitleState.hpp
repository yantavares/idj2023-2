#ifndef TITLESTATE_HPP
#define TITLESTATE_HPP

#include <iostream>
#include <string>
#include <memory>

#include "../State/State.hpp"
#include "../../components/Sprite/Sprite.hpp"
#include "../Music/Music.hpp"
#include "../../components/GameObject/GameObject.hpp"
#include "../../components/TileSet/TileSet.hpp"
#include "../../components/TileMap/TileMap.hpp"
#include "../InputManager/InputManager.hpp"
#include "../Camera/Camera.hpp"
#include "../../components/CameraFollower/CameraFollower.hpp"
#include "../../components/Alien/Alien.hpp"
#include "../../components/PenguinBody/PenguinBody.hpp"

class TitleState : public State
{
public:
    TitleState();
    ~TitleState();
    void LoadAssets();
    void Update(float dt);
    void Render();
    void Start();
    void Pause();
    void Resume();

private:
};

#endif