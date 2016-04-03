#include "GameObject.h"
#include "Transform.h"
#include <iostream>
using namespace std;

GameObject::GameObject()
{
	// All Gameobjects must have a transform
	_transform = shared_ptr<Transform>(new Transform());
	AddComponent(_transform);
	SetTag("Untagged");
}

GameObject::~GameObject()
{
	//for (auto i : _components)
	//{
	//	delete i;
	//}
}

void GameObject::Update()
{
	for (auto i : _components)
	{
		if (i->IsActive())
		{
			i->Update();
		}
	}
}

std::shared_ptr<Component> GameObject::AddComponent(std::shared_ptr<Component> comp)
{
	comp->Init(std::shared_ptr<GameObject>(this));
	_components.emplace_back(comp);
	return comp;
}

void GameObject::AddComponents(std::vector<std::shared_ptr<Component>> components)
{
	for (auto it : components)
	{
		AddComponent(it);
	}
}

std::shared_ptr<Transform> GameObject::GetTransform() const
{
	if (_transform == NULL)
	{
		cout << "ERROR: Couldn't find a transform on the gameobject! " << 
			"You can't access the transform before the GameObject has been initialized" << endl;
	}
	return _transform;
}

void GameObject::SetTag(std::string tag)
{
	if (tag.empty())
	{
		_tag = "Untagged";
	}
	_tag = tag;
}

void GameObject::SendCollisionEnter(std::shared_ptr<Collider> other)
{
	for (auto it : _components)
	{
		it->OnCollisionEnter(other);
	}
}

void GameObject::SendCollisionExit(std::shared_ptr<Collider> other)
{
	for (auto it : _components)
	{
		it->OnCollisionExit(other);
	}
}

void GameObject::SetActive(bool active)
{
	_isActive = active;
	for (auto it : _components)
	{
		it->SetActive(active);
	}
}
