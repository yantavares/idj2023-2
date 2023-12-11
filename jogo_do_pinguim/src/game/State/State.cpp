#include "State.hpp"
#include "../../components/GameObject/GameObject.hpp"

State::State() : popRequested(false), quitRequested(false), started(false) {}

State::~State() {
    objectArray.clear();
}

std::weak_ptr<GameObject> State::AddObject(GameObject* object) {
    std::shared_ptr<GameObject> sharedObj(object);
    objectArray.push_back(sharedObj);
    return std::weak_ptr<GameObject>(sharedObj);
}

std::weak_ptr<GameObject> State::GetObjectPtr(GameObject* object) {
    for (size_t i = 0; i < objectArray.size(); ++i) {
        if (objectArray[i].get() == object) {
            return std::weak_ptr<GameObject>(objectArray[i]);
        }
    }
    return std::weak_ptr<GameObject>();
}

bool State::PopRequested() const {
    return popRequested;
}

bool State::QuitRequested() const {
    return quitRequested;
}

void State::StartArray() {
    for (size_t i = 0; i < objectArray.size(); ++i) {
        objectArray[i]->Start();
    }
}

void State::UpdateArray(float dt) {
    for (size_t i = 0; i < objectArray.size(); ++i) {
        objectArray[i]->Update(dt);
    }
}

void State::RenderArray() {
    for (size_t i = 0; i < objectArray.size(); ++i) {
        objectArray[i]->Render();
    }
}
