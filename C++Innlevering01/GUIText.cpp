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

void GUIText::Awake()
{
	// Make sure the button is positioned at the correct position
	_transform->SetPosition(Vector2D(textItem->rect.x, textItem->rect.y));
	_transform->SetSize(Vector2D(textItem->rect.w, textItem->rect.h));
}

