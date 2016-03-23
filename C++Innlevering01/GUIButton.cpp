#include "GUIButton.h"
#include "Transform.h"
#include "InputManager.h"
#include <iostream>
int p = 0;
GUIButton::GUIButton(std::string text, Color color, Rect rect, SDLWrapper * sdl, bool fitrectToText)
{
	textItem = sdl->CreateText(text, color, rect, fitrectToText);
	_tempRect = textItem->rect;
}

GUIButton::~GUIButton()
{
}

void GUIButton::Update()
{
	if (_transform->GetRect().Contains(InputManager::GetInstance().GetMousePosition())
		&& InputManager::GetInstance().GetMouseDown(1))
	{
		OnClick();
	}
}

void GUIButton::Awake()
{
	_transform->SetPosition(Vector2D(_tempRect.x, _tempRect.y));
	_transform->SetSize(Vector2D(_tempRect.w, _tempRect.h));
}

void GUIButton::OnClick()
{
	std::cout << "Clicked "  << p++ << std::endl;
}
