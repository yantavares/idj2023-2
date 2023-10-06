#ifndef MINION_H
#define MINION_H

#include "../Component/Component.hpp"

class Minion : public Component
{
private:
	GameObject &alien;
	float arc;

public:
	Minion(GameObject &associated, GameObject &alien, float arcOffsetDeg = 0);
	void Update(float dt);
	void Render();
	bool Is(string type);
	void Shoot(Vec2 target);
};

#endif