#ifndef BULLET_H
#define BULLET_H

#include "../Component/Component.hpp"
#include "../Sprite/Sprite.hpp"

class Bullet : public Component
{
private:
	Vec2 speed;
	float distanceLeft;
	int damage;

public:
	Bullet(GameObject &associated, float angle, float speed, int damage, float maxDistance, string sprite, bool targetsPlayer, int framcount = 1, float frameTime = 1);
	void Update(float dt);
	void Render();
	bool Is(string type);
	int GetDamage();

	bool targetsPlayer;
};

#endif