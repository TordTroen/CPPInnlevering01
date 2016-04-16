#pragma once
#include <vector>
#include <memory>
class Collider;

class CollisionManager
{
public:
	static void Update();
	static void AddCollider(Collider* const collider, bool isStaticCollider = true);
	static void DeleteCollider(Collider* collider);
private:
	static std::vector<Collider*> toRemove;
	static std::vector<Collider*> staticColliders;
	static std::vector<Collider*> dynamicColliders;
};
