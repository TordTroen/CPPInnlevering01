#pragma once
#include <vector>
#include <memory>
class Collider;

class CollisionManager
{
public:
	static void Update();
	static void AddCollider(std::shared_ptr<Collider> collider, bool isStaticCollider = true);
private:
	static std::vector<std::shared_ptr<Collider>> _staticColliders;
	static std::vector<std::shared_ptr<Collider>> _dynamicColliders;
};

