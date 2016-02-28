#include "Component.h"
#include <iostream>
using namespace std;

Component::Component(string id)
	: _id(id), _isActive(true)
{
	cout << "Component " << _id << "  constructor" << endl;
}


Component::~Component()
{
}

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
