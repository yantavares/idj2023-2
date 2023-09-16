#include "GameObject.hpp"

GameObject::GameObject()
{
    this->isDead = false;
}

GameObject::~GameObject()
{
    for (int i = components.size() - 1; i >= 0; i--)
    {
        components.erase(components.begin() + i);
    }
    components.clear();
}

void GameObject::Update(float dt)
{
    for (auto it = components.begin(); it != components.end(); ++it)
    {
        (*it)->Update(dt);
    }
}

void GameObject::Render()
{
    for (auto it = components.begin(); it != components.end(); ++it)
    {
        (*it)->Render();
    }
}

bool GameObject::IsDead()
{
    return isDead;
}

void GameObject::RequestDelete()
{
    isDead = true;
}

void GameObject::AddComponent(Component *cpt)
{
    components.emplace_back(cpt);
}

void GameObject::RemoveComponent(Component *cpt)
{

    for (int i = 0; i < components.size(); i++)
    {
        if (components[i].get() == cpt)
        {
            components.erase(components.begin() + i);
            break;
        }
    }
}

Component *GameObject::GetComponent(string type)
{
    for (unsigned int i = 0; i < components.size(); i++)
    {
        if (components[i]->Is(type))
        {
            return components[i].get();
        }
    }
    return nullptr;
}

void GameObject::RemoveComponentType(string type)
{
    for (unsigned int i = 0; i < components.size(); i++)
    {
        if (components[i]->Is(type))
        {
            cout << "Found" << endl;
            components.erase(components.begin() + i);
            break;
        }
    }
}