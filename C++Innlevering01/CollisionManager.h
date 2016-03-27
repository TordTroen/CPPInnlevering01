#pragma once
#include <vector>
//#include "Collider.h"

class Collider;

class CollisionManager
{
public:
	CollisionManager();
	~CollisionManager();
	static void Update();
	static void AddCollider(Collider* collider);
	static void AddPlayer(Collider* playerCol);
private:
	static std::vector<Collider*> _colliders;
	static Collider* _player;
};

