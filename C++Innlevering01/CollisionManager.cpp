#include "CollisionManager.h"
#include "Collider.h"
#include "Rect.h"
#include <iostream>
using namespace std;

vector<Collider*> CollisionManager::_staticColliders;
vector<Collider*> CollisionManager::_dynamicColliders;

void CollisionManager::Update()
{
	for (auto ita : _staticColliders)
	{
		if (!ita->IsActive()) continue; // Only collide if the collider is active!

		for (auto itb : _dynamicColliders)
		{
			if (!itb->IsActive()) continue; // Only collide if the collider is active!

			if (ita->Intersects(itb) && !itb->IsColliding())
			{
				ita->OnCollisionEnterEvent(itb);
				itb->OnCollisionEnterEvent(ita);
			}
			else if (itb->IsColliding())
			{
				ita->OnCollisionExitEvent(itb);
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
