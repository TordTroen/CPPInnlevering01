#include "CollisionManager.h"
#include "Collider.h"
using namespace std;

vector<Collider*> CollisionManager::_staticColliders;
vector<Collider*> CollisionManager::_dynamicColliders;

void CollisionManager::Update()
{
	for (auto ita : _staticColliders)
	{
		for (auto itb : _dynamicColliders)
		{
			if (ita->Intersects(itb) && !itb->IsColliding())
			{
				itb->OnCollisionEnterEvent(ita);
			}
			else if (itb->IsColliding())
			{
				itb->OnCollisionExitEvent(ita);
			}
		}
	}
}

void CollisionManager::AddCollider(Collider* collider, bool isStaticCollider)
{
	if (isStaticCollider)
	{
		_staticColliders.emplace_back(collider);
	}
	else
	{
		_dynamicColliders.emplace_back(collider);
	}
}
