#include "GUIMenu.h"
#include "GameObjectManager.h"

GUIMenu::GUIMenu(std::vector<GUIElement*> elements)
{
	for (auto it : elements)
	{
		// Create gameobject and add the GUIElement to it
		GameObjectManager::GetInstance().CreateObject()->AddComponent(it);
	}
	AddElements(elements);
}

GUIMenu::~GUIMenu()
{
}

void GUIMenu::AddElement(GUIElement* element)
{
	_elements.emplace_back(element);
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
