#ifndef PENGUINBODY_HPP
#define PENGUINBODY_HPP

#include "../../geometry/Vec2/Vec2.hpp"
#include "../Component/Component.hpp"
#include "../GameObject/GameObject.hpp"

#include <string>
#include <memory>

#define CONST_ACCELERATION 0.01;
#define ANGULAR_SPEED 0.001;
#define MAX_SPEED 0.25

class PenguinBody : public Component
{
public:
    PenguinBody(GameObject &associated);
    virtual ~PenguinBody();

    void Start() override;
    void Update(float dt) override;
    void Render() override;
    bool Is(std::string type) override;

    static PenguinBody *player;

private:
    std::weak_ptr<GameObject> pcannon;
    Vec2 speed;
    float linearSpeed;
    float angle;
    int hp;
};

#endif
