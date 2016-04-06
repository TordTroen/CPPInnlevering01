#pragma once
#include <vector>
#include <memory>
class Collider;

class CollisionManager
{
public:
	static void Update();
	static void AddCollider(Collider* const collider, bool isStaticCollider = true);
private:
	static std::vector<Collider*> staticColliders;
	static std::vector<Collider*> dynamicColliders;
};

