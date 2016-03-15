#include "Component.h"
#include <iostream>
using namespace std;

Component::Component()
	: _isActive(true)
{
	cout << "Component " /*<< _id*/ << "  constructor" << endl;
}


Component::~Component()
{
}

bool Component::IsActive() const { return _isActive; }
void Component::SetActive(bool active) { _isActive = active; }

void Component::Awake()
{
	//cout << "Component " << _id << " Awake()" << endl;
}

void Component::Start()
{
	//cout << "Component " << _id << " Start()" << endl;
}

void Component::Update()
{
	//cout << "BaseComponent " << _id << " Update()" << endl;
}
