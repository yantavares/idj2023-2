#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <iostream>
#include <vector>
#include <memory>
#include "../../geometry/Rect/Rect.hpp"
#include "../Component/Component.hpp"

using namespace std;

class Component;

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
    void RemoveComponentType(string type);
    Component *GetComponent(string type);

    void Start();
    bool started;

    Rect box;

private:
    // Needs to be shared to work!
    vector<shared_ptr<Component>> components;
    bool isDead;
};

#endif