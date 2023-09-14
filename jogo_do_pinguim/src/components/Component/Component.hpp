#include <iostream>

using namespace std;

class GameObject;

class Component
{
protected:
    GameObject &associated;

public:
    Component(GameObject &associated);
    virtual ~Component();
};
