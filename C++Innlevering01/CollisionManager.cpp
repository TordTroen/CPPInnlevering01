#include "CollisionManager.h"
#include "Collider.h"
#include "Rect.h"
#include <iostream>
using namespace std;

// Holds the static position of the walls that can be collided with
vector<Collider*> CollisionManager::_staticColliders;

// Holds the dynamic position of the moving objects that will collide
vector<Collider*> CollisionManager::_dynamicColliders;

// Is updated every frame to see if there is a new collision.
void CollisionManager::Update()
{
	for (auto ita : _staticColliders)	// For every static wall
	{
		if (!ita->IsActive()) continue; // Only collide if the collider is active!

		for (auto itb : _dynamicColliders) // For every moving ball and brick..
		{
			if (!itb->IsActive()) continue; // Only collide if the collider is active!

			if (ita->Intersects(itb) && !itb->IsColliding())
			{
				ita->OnCollisionEnterEvent(itb);
				itb->OnCollisionEnterEvent(ita);
			}
			else if (itb->IsColliding())    // If there is a new collision
			{
				ita->OnCollisionExitEvent(itb);
				itb->OnCollisionExitEvent(ita);
			}
		}
	}
}

void CollisionManager::AddCollider(Collider* const collider, bool isStaticCollider)
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
