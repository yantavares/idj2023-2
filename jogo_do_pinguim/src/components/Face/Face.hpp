#ifndef FACE_HPP
#define FACE_HPP

#include <iostream>
#include "Component.hpp"

using namespace std;

class Face : public Component
{
public:
    Face(GameObject &associated);
    ~Face();

    void Damage(int damage);
    void Update(float dt);
    void Render();
    bool Is(string type);

private:
    int hitpoints;
};

#endif