#include "GUILayoutMenu.h"
#include "GameManager.h"
#include "GameObject.h"
#include "Transform.h"
#include "Rect.h"

GUILayoutMenu::GUILayoutMenu(Alignment alignment, int startMargin, int spacing, bool activeState)
	: GUIMenu(activeState), margin(startMargin), spacing(spacing), alignment(alignment)
{
	SetOverrideSize(Vector2D(-1, -1));
	curPos = Vector2D(0, 0);
	if (IsVertical())
	{
		curPos.Y = margin;
	}
	else
	{
		curPos.X = margin;
	}
}

GUILayoutMenu::~GUILayoutMenu()
{
}

void GUILayoutMenu::AddElement(GUIElement * const element)
{
	// Create a gameobject and add the element to it if it ins't already attached to a gameobject
	if (element->GetGameObject() == NULL)
	{
		GameObject* obj = gameManager->CreateObject();
		obj->AddComponent(element);
	}

	// Make sure the transform and the drawable have the same positions/sizes
	element->SyncDrawableWithTransform();

	// Put this element at the next position
	Rect oldRect = element->GetTransform()->GetRect();
	Rect newRect = Rect(curPos.X, curPos.Y, oldRect.w, oldRect.h);

	// Figure out where we anchor the element
	switch (alignment)
	{
	case Alignment::VerticalCenter:
		curPos.X = gameManager->GetCenterXPosition(newRect.w);
		break;
	case Alignment::HorizontalCenter:
		curPos.Y = gameManager->GetCenterYPosition(newRect.h);
		break;
	case Alignment::Left:
		curPos.X = margin;
		break;
	case Alignment::Right:
		curPos.X = gameManager->GetWindowWidth() - newRect.w - margin;
		break;
	case Alignment::Top:
		curPos.Y = margin;
		break;
	case Alignment::Bottom:
		curPos.Y = gameManager->GetWindowHeight() - newRect.h - margin;
		break;
	default:
		break;
	}
	
	// If we have set a width/height size to override the elements size, apply it
	if (overrideSize.X >= 0)
	{
		newRect.w = overrideSize.X;
	}
	if (overrideSize.Y >= 0)
	{
		newRect.h = overrideSize.Y;
	}
	newRect.x = curPos.X;
	newRect.y = curPos.Y;

	// Apply the current rect to the element
	element->GetTransform()->SetRect(newRect);

	// Calculate the next currentPos
	if (IsVertical())
	{
		curPos.Y += oldRect.h + spacing * 2;
	}
	else
	{
		curPos.X += oldRect.w + spacing * 2;
	}

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

float GUILayoutMenu::GetSize() const
{
	return 0.0f;
}

bool GUILayoutMenu::IsVertical() const
{
	return alignment == Alignment::Left || alignment == Alignment::VerticalCenter || alignment == Alignment::Right;
}

void GUILayoutMenu::RemoveElements(int startIndex, int count)
{
	// Go through the elements and decrease the curPos value so the next element is placed correcly
	auto start = elements.begin() + startIndex;
	auto end = start + count;
	for (auto it = start; it != end; ++it)
	{
		if (IsVertical())
		{
			curPos.Y -= (*it)->GetTransform()->GetRect().h + spacing * 2;
		}
		else
		{
			curPos.X -= (*it)->GetTransform()->GetRect().w + spacing * 2;
		}
	}

	// Remove the elements
	GUIMenu::RemoveElements(startIndex, count);
}
