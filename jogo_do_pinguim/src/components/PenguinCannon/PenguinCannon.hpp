#ifndef PENGUINCANNON_HPP
#define PENGUINCANNON_HPP

#include "../Component/Component.hpp"
#include "../GameObject/GameObject.hpp"

#include <string>
#include <memory>

class PenguinCannon : public Component
{
public:
    PenguinCannon(GameObject &associated, std::weak_ptr<GameObject> penguinBody);
    void Update(float dt) override;
    void Render() override;
    bool Is(std::string type) override;

    void Shoot();

private:
    std::weak_ptr<GameObject> pbody;
    float angle;
};

#endif
