#include "CollisionManager.h"
#include "Collider.h"
#include "Rect.h"
#include <algorithm>
using namespace std;

// Holds the static position of the walls that can be collided with
vector<Collider*> CollisionManager::staticColliders;

// Holds the dynamic position of the moving objects that will collide
vector<Collider*> CollisionManager::dynamicColliders;

vector<Collider*> CollisionManager::toRemove;

// Is updated every frame to see if there is a new collision.
void CollisionManager::Update()
{
	if (toRemove.size() > 0)
	{
		for (int i = 0; i < toRemove.size(); i++)
		{
			if (toRemove[i]->IsStaticCollider())
			{
				staticColliders.erase(
					std::remove_if( // Selectively remove elements in the second vector...
						staticColliders.begin(),
						staticColliders.end(),
						[&](Collider* const& p)
				{   // This predicate checks whether the element is contained
					// in the second vector of pointers to be removed...
					return toRemove[i] == p;
				}), staticColliders.end());
			}
			else
			{
				dynamicColliders.erase(
					std::remove_if( // Selectively remove elements in the second vector...
						dynamicColliders.begin(),
						dynamicColliders.end(),
						[&](Collider* const& p)
				{   // This predicate checks whether the element is contained
					// in the second vector of pointers to be removed...
					return toRemove[i] == p;
				}), dynamicColliders.end());
			}
		}
		toRemove.clear();
	}

	for (auto ita : staticColliders) // For every static wall
	{
		if (!ita->IsActive() || ita == NULL) continue; // Only collide if the collider is active and not null!

		for (auto itb : dynamicColliders) // For every moving ball and brick..
		{
			if (!itb->IsActive() || itb == NULL) continue; // Only collide if the collider is active and not null!

			if (ita->Intersects(itb) && !itb->IsColliding())
			{
				ita->OnCollisionEnterEvent(itb);
				itb->OnCollisionEnterEvent(ita);
			}
			else if (itb->IsColliding()) // If there is a new collision
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
		staticColliders.emplace_back(collider);
	}

	else {
		dynamicColliders.emplace_back(collider);
	}
}

void CollisionManager::DeleteCollider(Collider* collider)
{
	if (collider == NULL) return;
	toRemove.emplace_back(collider);
}
