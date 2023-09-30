#ifndef CAMERAFOLLOWER_H
#define CAMERAFOLLOWER_H

#include "../Component/Component.hpp"

using namespace std;

class CameraFollower : public Component
{
public:
    CameraFollower(GameObject &go);
    ~CameraFollower() {}

    void Update(float dt);
    void Render(){};
    bool Is(string type);

private:
};

#endif
