#pragma once
#include <vector>

class Collider;

class CollisionManager
{
public:
	static void Update();
	static void AddCollider(Collider* collider, bool isStaticCollider = true);
private:
	static std::vector<Collider*> _staticColliders;
	static std::vector<Collider*> _dynamicColliders;
};

