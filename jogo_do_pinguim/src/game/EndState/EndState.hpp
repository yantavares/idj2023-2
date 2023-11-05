#ifndef ENDSTATE_HPP
#define ENDSTATE_HPP

#include <iostream>
#include <string>
#include <memory>

#include "../State/State.hpp"
#include "../Music/Music.hpp"
#include "../InputManager/InputManager.hpp"
#include "../Camera/Camera.hpp"
#include "../../components/Sprite/Sprite.hpp"
#include "../../components/GameObject/GameObject.hpp"
#include "../../components/TileSet/TileSet.hpp"
#include "../../components/TileMap/TileMap.hpp"
#include "../../components/CameraFollower/CameraFollower.hpp"
#include "../../components/Alien/Alien.hpp"
#include "../../components/PenguinBody/PenguinBody.hpp"

class EndState : public State
{
public:
    EndState();
    ~EndState();
    void LoadAssets();
    void Update(float dt);
    void Render();
    void Start();
    void Pause();
    void Resume();

private:
    Music backgroundMusic;
};

#endif