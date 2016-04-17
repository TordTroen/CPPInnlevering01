#include "GUIMenu.h"
#include "GameObjectManager.h"
#include "GameManager.h"
#include "Transform.h"

GUIMenu::GUIMenu(bool activeState)
{
	SetActive(activeState);
}

GUIMenu::~GUIMenu()
{
}

void GUIMenu::AddElement(GUIElement* const element)
{
	if (element->GetGameObject() == NULL)
	{
		GameObject* obj = gameManager->CreateObject();
		obj->AddComponent(element);
	}

	element->SyncDrawableWithTransform();

	elements.emplace_back(element);
	element->SetActive(IsActive());
}

void GUIMenu::AddElements(std::vector<GUIElement*> elements)
{
	for (auto it : elements)
	{
		AddElement(it);
	}
}

void GUIMenu::RemoveElements(int startIndex, int count)
{
	auto start = elements.begin() + startIndex;
	elements.erase(start, start + count);
}

void GUIMenu::OnSetActive()
{
	for (auto it : elements)
	{
		it->SetActive(IsActive());
	}
}
