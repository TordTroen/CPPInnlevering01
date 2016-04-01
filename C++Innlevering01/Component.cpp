#include "Component.h"
#include "GameObject.h"
#include <iostream>
#include "Collider.h"
using namespace std;

Component::Component()
	: _isActive(true), _transform(NULL), _gameObject(NULL)
{
	//cout << "Component " /*<< _id*/ << "  constructor" << endl;
}


Component::~Component()
{
}

void Component::Init(GameObject * gameObject)
{
	_gameObject = gameObject;
	_transform = _gameObject->GetTransform();
	Awake();
	Start();
}

bool Component::IsActive() const
{
	return _isActive;
}

void Component::SetActive(bool active)
{
	_isActive = active;
	OnSetActive();
}

void Component::Awake()
{
	//cout << "Component Awake()" << endl;
}

void Component::Start()
{
	//cout << "Component " << _id << " Start()" << endl;
}

void Component::OnSetActive()
{
}

void Component::Update()
{
	//cout << "BaseComponent " << _id << " Update()" << endl;
}

void Component::OnCollisionEnter(const Collider* other)
{
}

void Component::OnCollisionExit(const Collider* other)
{
}
