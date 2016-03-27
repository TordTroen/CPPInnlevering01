#include "CollisionManager.h"
#include "Collider.h"
using namespace std;

vector<Collider*> CollisionManager::_colliders;
Collider* CollisionManager::_player;

CollisionManager::CollisionManager()
{
}

CollisionManager::~CollisionManager()
{
}

void CollisionManager::Update()
{
	for (auto it : _colliders)
	{
		if (it->Intersects(_player))
		{
			if (!_player->isColliding)
				_player->OnCollisionEnter(it);
		}
		else
		{
			if (_player->isColliding)
				_player->OnCollisionExit(it);
		}
	}
	//for (auto colA : _colliders)
	//{
	//	for (auto colB : _colliders)
	//	{
	//		if (colA->Intersects(colB))
	//		{
	//			colA->OnCollision(colB);
	//			colB->OnCollision(colA);
	//		}
	//	}
	//}
}

void CollisionManager::AddCollider(Collider* collider)
{
	_colliders.emplace_back(collider);
}

void CollisionManager::AddPlayer(Collider * playerCol)
{
	_player = playerCol;
}
