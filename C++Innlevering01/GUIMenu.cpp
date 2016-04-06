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
	GameObject* obj = GameObjectManager::GetInstance().CreateObject();
	obj->AddComponent(element);
	element->SyncPositionWithTransform();
	_elements.emplace_back(element);
	element->SetActive(IsActive());
}

void GUIMenu::AddElementsLayout(int startYposition, int spacing, std::vector<GUIElement*> elements)
{
	int curY = startYposition;
	for (auto it : elements)
	{
		AddElement(it);
		/*Rect oldRect = it->GetTransform()->GetRect();
		Rect newRect = Rect(GameManager::GetInstance().GetCenterXPosition(oldRect.w), curY, oldRect.w, oldRect.h);
		it->GetTransform()->SetRect(newRect);
		curY += oldRect.h + spacing;*/
	}
}

void GUIMenu::OnSetActive()
{
	for (auto it : _elements)
	{
		it->SetActive(IsActive());
	}
}
