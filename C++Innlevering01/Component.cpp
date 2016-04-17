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

// TODO These can be abstract
void Component::Awake()
{
}

void Component::OnSetActive()
{
}

void Component::Update()
{
}

void Component::OnCollisionEnter(const Collider* const other)
{
}

void Component::OnCollisionExit(const Collider* const other)
{
}
