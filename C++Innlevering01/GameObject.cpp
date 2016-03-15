#include "GameObject.h"
#include "Transform.h"
#include <iostream>
using namespace std;

GameObject::GameObject()
{
	// All Gameobjects must have a transform
	_transform = new Transform();
	AddComponent(_transform);

	// Call awake and start on all components
	for (auto i : _components)
	{
		i->Awake();
	}
	for (auto i : _components)
	{
		i->Start();
	}
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
		i->Update();
	}
}

Component* GameObject::AddComponent(Component* comp)
{
	_components.emplace_back(comp);
	return comp;
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

