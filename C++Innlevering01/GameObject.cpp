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
	//cout << "Gameobj constructor" << endl;
	// Call awake and start on all components
	//for (auto i : _components)
	//{
	//	i->Awake();
	//}
	//for (auto i : _components)
	//{
	//	i->Start();
	//}
}

GameObject::~GameObject()
{
	for (auto i : _components)
	{
		delete i;
	}
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

Component* GameObject::AddComponent(Component* comp)
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

void GameObject::SendCollisionEnter(Collider * other)
{
	for (auto it : _components)
	{
		it->OnCollisionEnter(other);
	}
}

