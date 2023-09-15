#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <iostream>
#include <vector>
#include <memory>
#include "../../geometry/Rect/Rect.hpp"
#include "../Component/Component.hpp"

using namespace std;

class GameObject
{
public:
    GameObject();
    ~GameObject();

    void Update(float dt);
    void Render();
    bool IsDead();
    void RequestDelete();
    void AddComponent(Component *cpt);
    void RemoveComponent(Component *cpt);
    Component *GetComponent(string type);

    Rect box;

private:
    vector<unique_ptr<Component>> components;
    bool isDead;
};

#endif