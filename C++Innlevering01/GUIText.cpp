#include "GUIText.h"
#include "SDLWrapper.h"
#include "Transform.h"

GUIText::GUIText(std::string text, Color color, Rect rect)
{
	textItem = SDLWrapper::GetInstance().CreateText(text, color, rect);
}

GUIText::~GUIText()
{
}

void GUIText::SetText(std::string text)
{
	Color color = textItem->GetColor();
	if (textItem != NULL)
	{
		// TODO Destroy old textitem
		//SDLWrapper::GetInstance().allDrawables.erase()
		//delete textItem;
		textItem->SetActive(false);
	}
	textItem = SDLWrapper::GetInstance().CreateText(text, color, textItem->GetRect());
	textItem->SetActive(IsActive());
}

void GUIText::SyncDrawableWithTransform()
{
	GetTransform()->SetRect(textItem->GetRect());
	textItem->SetComponent(this);
}

void GUIText::Awake()
{
	// Make sure the button is positioned at the correct position
	GetTransform()->SetRect(textItem->GetRect());
}

void GUIText::OnSetActive()
{
	textItem->SetActive(IsActive());
}

