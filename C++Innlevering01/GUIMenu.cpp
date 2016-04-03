#include "GUIMenu.h"
#include "GameObjectManager.h"

GUIMenu::GUIMenu(bool activeState)
{
	SetActive(activeState);
}

GUIMenu::GUIMenu(std::vector<std::shared_ptr<GUIElement>> elements, bool activeState)
{
	SetActive(activeState);
	AddElements(elements);
}

GUIMenu::~GUIMenu()
{
}

void GUIMenu::AddElement(std::shared_ptr<GUIElement> element)
{
	GameObjectManager::GetInstance().CreateObject()->AddComponent(element);
	_elements.emplace_back(element);
	element->SetActive(IsActive());
}

void GUIMenu::AddElements(std::vector<std::shared_ptr<GUIElement>> elements)
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
