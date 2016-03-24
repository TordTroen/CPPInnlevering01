#include "GUIButton.h"
#include "Transform.h"
#include "InputManager.h"
#include <iostream>

GUIButton::GUIButton(std::string text, Color color, Color bgColor, Rect rect, SDLWrapper * sdl, void (*CallbackFunction)(void), bool fitrectToText)
{
	backgroundItem = sdl->CreateImage("WhiteTexture.png", rect, bgColor, false);
	textItem = sdl->CreateText(text, color, rect, fitrectToText);
	Callback = CallbackFunction;
}

GUIButton::~GUIButton()
{
}

void GUIButton::Awake()
{
	// Make sure the button is positioned at the correct position
	backgroundItem->SetRect(textItem->rect);
	_transform->SetPosition(Vector2D(textItem->rect.x, textItem->rect.y));
	_transform->SetSize(Vector2D(textItem->rect.w, textItem->rect.h));
}

void GUIButton::Update()
{
	if (_transform->GetRect().Contains(InputManager::GetInstance().GetMousePosition())
		&& InputManager::GetInstance().GetMouseDown(1))
	{
		OnClick();
	}
}

void GUIButton::OnClick() const
{
	std::cout << "Clicked" << std::endl;
	if (Callback != NULL)
	{
		Callback();
	}
}
