#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "../../components/GameObject/GameObject.hpp"
#include "../../geometry/Vec2/Vec2.hpp"

class Camera
{
public:
    static void Follow(GameObject *newFocus);
    static void Unfollow();
    static void Update(float dt);

    static Vec2 pos;
    static Vec2 speed;

private:
    static GameObject *focus;
};

#endif
