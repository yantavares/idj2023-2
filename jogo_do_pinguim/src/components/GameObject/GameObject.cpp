#include "GameObject.hpp"

GameObject::GameObject()
{
    started = false;
    isDead = false;
    angle = 0;
}

GameObject::~GameObject()
{
    for (int i = components.size() - 1; i >= 0; i--)
    {
        components.erase(components.begin() + i);
    }
}

void GameObject::Update(float dt)
{
    for (unsigned int i = 0; i < components.size(); i++)
    {
        components[i]->Update(dt);
    }
}

void GameObject::Render()
{
    for (unsigned int i = 0; i < components.size(); i++)
    {
        components[i]->Render();
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

void GameObject::Start()
{
    for (auto &comp : components)
    {
        comp->Start();
    }
}

void GameObject::AddComponent(Component *comp)
{
    components.emplace_back(comp);
}

void GameObject::NotifyCollision(GameObject &other)
{
    for (auto &component : components)
    {
        component->NotifyCollision(other);
    }
}

void GameObject::RemoveComponent(string type)
{
    bool found = false;
    for (unsigned int i = 0; i < components.size() && !found; i++)
    {
        if (components[i]->Is(type))
        {
            components.erase(components.begin() + i);
            found = true;
        }
    }
}