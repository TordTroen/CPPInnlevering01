#include "Component.h"
#include <iostream>
#include "GameObject.h"
#include "GameManager.h"
#include "Collider.h"
using namespace std;

Component::Component()
	: isActive(true), transform(NULL), gameObject(NULL)
{
}


Component::~Component()
{
}

void Component::Init(GameObject* const gameObject, GameManager* gameManager)
{
	if (gameObject == NULL)
	{
		std::cout << "GameObject of this component is NULL! You can't create a component without a GameObject!" << std::endl;
	}
	this->gameObject = gameObject;
	this->transform = gameObject->GetTransform();
	this->gameManager = gameManager;
	Awake();
}

bool Component::IsActive() const
{
	return isActive;
}

void Component::SetActive(bool active)
{
	isActive = active;
	OnSetActive();
}

void Component::Awake()
{
	//cout << "Component Awake()" << endl;
}

//void Component::Start()
//{
//	//cout << "Component " << _id << " Start()" << endl;
//}

void Component::OnSetActive()
{
}

void Component::Update()
{
	//cout << "BaseComponent " << _id << " Update()" << endl;
}

void Component::OnCollisionEnter(const Collider* const other)
{
}

void Component::OnCollisionExit(const Collider* const other)
{
}
