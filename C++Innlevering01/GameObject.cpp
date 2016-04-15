#include "GameObject.h"
#include "Transform.h"
#include <iostream>
using namespace std;

GameObject::GameObject()
{
	// All Gameobjects must have a transform
	_transform = new Transform();
	AddComponent(_transform);
	SetTag("Untagged");
}

GameObject::~GameObject()
{
	//std::cout << "Deleting GameObject: " << _tag.c_str() << std::endl;
	//for (auto i : _components)
	//{
	//	delete i;
	//}
}

void GameObject::Update()
{
	for (auto const& it : _components)
	{
		if (it != NULL && it->IsActive())
		{
			it->Update();
		}
	}
}

Component* GameObject::AddComponent(Component* const comp)
{
	comp->Init(this);
	_components.emplace_back(comp);
	return comp;
}

void GameObject::AddComponents(std::vector<Component*> components)
{
	for (auto it : components)
	{
		AddComponent(it);
	}
}

Transform* GameObject::GetTransform() const
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

void GameObject::SendCollisionEnter(const Collider* const other)
{
	for (auto const& it : _components)
	{
		it->OnCollisionEnter(other);
	}
}

void GameObject::SendCollisionExit(const Collider* const other)
{
	for (auto const& it : _components)
	{
		it->OnCollisionExit(other);
	}
}

void GameObject::SetActive(bool active)
{
	_isActive = active;
	for (auto const& it : _components)
	{
		it->SetActive(active);
	}
}

void GameObject::Destroy()
{
	// TODO Implement
	SetActive(false);
}
