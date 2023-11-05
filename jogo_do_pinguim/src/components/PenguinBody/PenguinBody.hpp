#ifndef PENGUINBODY_HPP
#define PENGUINBODY_HPP

#include "../../geometry/Vec2/Vec2.hpp"
#include "../Component/Component.hpp"
#include "../GameObject/GameObject.hpp"

#include <string>
#include <memory>

#define CONST_ACCELERATION 0.01
#define ANGULAR_SPEED 0.001
#define MAX_SPEED 0.25

class PenguinBody : public Component
{
public:
    PenguinBody(GameObject &associated);
    virtual ~PenguinBody();

    void Start();
    void Update(float dt);
    void Render();
    bool Is(string type);

    void NotifyCollision(GameObject &other);

    static PenguinBody *player;

private:
    weak_ptr<GameObject> pcannon;
    Vec2 speed;
    float linearSpeed;
    float angle;
    int hp;

    bool dead;
};

#endif
