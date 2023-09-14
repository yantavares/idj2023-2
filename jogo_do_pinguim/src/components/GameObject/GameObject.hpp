#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <iostream>
#include <vector>
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
    vector<Component *> components;
    bool isDead;
};

#endif