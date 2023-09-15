#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include <iostream>
#include "../GameObject/GameObject.hpp"

using namespace std;

class Component
{
protected:
    GameObject &associated;

public:
    Component();
    Component(GameObject &associated);
    virtual ~Component();

    virtual void Update(float dt);
    virtual void Render();
    virtual bool Is(string type);
};

#endif