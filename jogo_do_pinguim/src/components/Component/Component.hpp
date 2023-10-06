#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include <iostream>
#include "../GameObject/GameObject.hpp"

using namespace std;

class GameObject;

class Component
{
protected:
    GameObject &associated;

public:
    Component(GameObject &associated);
    virtual ~Component();
    virtual void Update(float dt) = 0;
    virtual void Render() = 0;
    virtual bool Is(string type) = 0;

    GameObject &GetAssociated() { return associated; }

    virtual void Start();
};

#endif