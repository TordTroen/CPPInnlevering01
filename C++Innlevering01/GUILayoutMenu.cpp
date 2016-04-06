#include "GUILayoutMenu.h"
#include "GameObjectManager.h"
#include "GameManager.h"
#include "Transform.h"
#include "Rect.h"

GUILayoutMenu::GUILayoutMenu(int startYpos, int spacing, bool activeState)
	: GUIMenu(activeState), curYpos(startYpos), spacing(spacing)
{
}

GUILayoutMenu::~GUILayoutMenu()
{
}

void GUILayoutMenu::AddElement(GUIElement * const element)
{
	// Create a gameobject and add the element to it
	GameObject* obj = GameObjectManager::GetInstance().CreateObject();
	obj->AddComponent(element);

	// Make sure the transform 
	element->SyncDrawableWithTransform();

	// Put this element at the next position
	Rect oldRect = element->GetTransform()->GetRect();
	Rect newRect = Rect(GameManager::GetInstance().GetCenterXPosition(oldRect.w), curYpos, oldRect.w, oldRect.h); // TODO add ability to align left/right/middle/horizontally/vertically
	element->GetTransform()->SetRect(newRect);
	curYpos += oldRect.h + spacing;

	// Add the element to the list
	elements.emplace_back(element);

	// Set the element active state based on the menus active state
	element->SetActive(IsActive());
}

void GUILayoutMenu::AddElements(std::vector<GUIElement*> elements)
{
	for (auto it : elements)
	{
		AddElement(it);
		
	}
}

void GUILayoutMenu::SetStartingYPos(int startYPos)
{
	curYpos = startYPos;
	if (!elements.empty())
	{
		std::cout << "Warning: The GUIMenu already has elemnts, are you sure you want to set the startYposition?" << std::endl;
	}
}
