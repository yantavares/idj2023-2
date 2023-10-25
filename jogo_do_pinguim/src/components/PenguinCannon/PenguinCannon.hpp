#ifndef PENGUINCANNON_HPP
#define PENGUINCANNON_HPP

#include "../Component/Component.hpp"
#include "../GameObject/GameObject.hpp"
#include "../Timer/Timer.hpp"

#include <string>
#include <memory>

class PenguinCannon : public Component
{
public:
    PenguinCannon(GameObject &associated, weak_ptr<GameObject> penguinBody);
    void Update(float dt) override;
    void Render() override;
    bool Is(string type) override;

    void Shoot();

private:
    weak_ptr<GameObject> pbody;
    float angle;

    Timer shotCooldown;
};

#endif
