#ifndef ALIEN_H
#define ALIEN_H

#include "../GameObject/GameObject.hpp"
#include "../Minion/Minion.hpp"
#include "../Sprite/Sprite.hpp"

#include <queue>

class Alien : public Component
{
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
	Vec2 speed;
	int hp;
	int nMinions;
	queue<Action> tasks;
	vector<weak_ptr<GameObject>> minions;

public:
	Alien(GameObject &associated, int nMinions);
	~Alien();

	void Start();
	void Update(float dt);
	void Render();
	bool Is(string type);
};

#endif