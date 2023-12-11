#ifndef STATE_HPP
#define STATE_HPP

#include <memory>
#include <vector>

class GameObject;

class State {
protected:
    bool popRequested;
    bool quitRequested;
    bool started;
    std::vector<std::shared_ptr<GameObject>> objectArray;

public:
    State();
    virtual ~State();

    virtual void LoadAssets() = 0;
    virtual void Update(float dt) = 0;
    virtual void Render() = 0;
    virtual void Start() = 0;
    virtual void Pause() = 0;
    virtual void Resume() = 0;

    virtual std::weak_ptr<GameObject> AddObject(GameObject* object);
    virtual std::weak_ptr<GameObject> GetObjectPtr(GameObject* object);

    bool PopRequested() const;
    bool QuitRequested() const;

    virtual void StartArray();
    virtual void UpdateArray(float dt);
    virtual void RenderArray();
};

#endif // STATE_H
