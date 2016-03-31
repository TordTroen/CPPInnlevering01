#include "GUIMenu.h"
#include "GameObjectManager.h"

GUIMenu::GUIMenu(bool activeState)
{
	SetActive(activeState);
}

GUIMenu::GUIMenu(std::vector<GUIElement*> elements, bool activeState)
{
	SetActive(activeState);
	AddElements(elements);
}

GUIMenu::~GUIMenu()
{
}

void GUIMenu::AddElement(GUIElement* element)
{
	GameObjectManager::GetInstance().CreateObject()->AddComponent(element);
	_elements.emplace_back(element);
	element->SetActive(IsActive());
}

void GUIMenu::AddElements(std::vector<GUIElement*> elements)
{
	for (auto it : elements)
	{
		AddElement(it);
	}
}

void GUIMenu::OnSetActive()
{
	for (auto it : _elements)
	{
		it->SetActive(IsActive());
	}
}
