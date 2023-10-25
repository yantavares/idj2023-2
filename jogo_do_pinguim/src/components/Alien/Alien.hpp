#ifndef ALIEN_H
#define ALIEN_H

#include "../GameObject/GameObject.hpp"
#include "../Minion/Minion.hpp"
#include "../Sprite/Sprite.hpp"
#include "../Timer/Timer.hpp"

#include <queue>

class Alien : public Component
{
public:
	Alien(GameObject &associated, int nMinions);
	~Alien();

	void Start();
	void Update(float dt);
	void Render();
	bool Is(string type);

	void NotifyCollision(GameObject &other);

	static int alienCount;

private:
	class Action
	{
	public:
		enum ActionType
		{
			MOVE,
			SHOOT
		};

		Action(ActionType type, float x, float y);

		ActionType type;
		Vec2 pos;
	};
	enum AlienState
	{
		MOVING,
		RESTING
	};
	AlienState state;
	Vec2 speed;
	int hp;
	int nMinions;
	queue<Action> tasks;
	vector<weak_ptr<GameObject>> minions;

	Timer restTimer;
	Vec2 destination;

	bool dead;
};

#endif