
#include "../State/State.hpp"
#include "../Collision/Collision.hpp"
#include "../../components/Collider/Collider.hpp"

State::State()
{
    started = false;
    quitRequested = false;
    popRequested = false;
    return;
}

State::~State()
{
    objectArray.clear();
}

bool State::QuitRequested()
{
    return quitRequested;
}

bool State::PopRequested()
{
    return popRequested;
}

weak_ptr<GameObject> State::AddObject(GameObject *go)
{

    shared_ptr<GameObject> newobj(go);

    objectArray.push_back(newobj);

    if (started)
    {
        newobj->Start();
    }

    weak_ptr<GameObject> newweak(newobj);
    return newweak;
}

weak_ptr<GameObject> State::GetObjectPtr(GameObject *go)
{
    long unsigned int index;
    for (index = 0; index < objectArray.size(); index++)
    {
        if (objectArray[index].get() == go)
        {
            weak_ptr<GameObject> newweak(objectArray[index]);
            return newweak;
        }
    }
    weak_ptr<GameObject> newweak;
    return newweak;
}

void State::UpdateArray(float dt)
{
    long unsigned int index;
    for (index = 0; index < objectArray.size(); index++)
    {
        objectArray[index]->Update(dt);
    }
    return;
}

void State::RenderArray()
{
    long unsigned int index;
    for (index = 0; index < objectArray.size(); index++)
    {
        objectArray[index]->Render();
    }
    return;
}

void State::StartArray()
{
    long unsigned int index;
    for (index = 0; index < objectArray.size(); index++)
    {
        objectArray[index]->Start();
    }
    return;
}