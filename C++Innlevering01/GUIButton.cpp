#include "GUIButton.h"
#include "Transform.h"
#include "InputManager.h"
#include <iostream>

GUIButton::GUIButton(std::string text, Color color, Color normalColor, Color downColor, Color hoverColor, Rect rect, int textPadding, void(*CallbackFunction)(void), bool fitrectToText)
	: isOver(false), clicked(false), clickFrames(0)
{
	this->normalColor = normalColor;
	this->downColor = downColor;
	this->hoverColor = hoverColor;
	backgroundItem = SDLWrapper::GetInstance().CreateImage("WhiteTexture.png", rect, normalColor, false);
	textItem = SDLWrapper::GetInstance().CreateText(text, color, rect, fitrectToText);

	Rect bgRect = textItem->rect;
	if (textPadding != 0)
	{
		bgRect.x -= textPadding;
		bgRect.y -= textPadding;
		bgRect.w += textPadding * 2;
		bgRect.h += textPadding * 2;
	}
	backgroundItem->SetRect(bgRect);

	Callback = CallbackFunction;
}

GUIButton::~GUIButton()
{
}

void GUIButton::Awake()
{
	// Make sure the button is positioned at the correct position
	_transform->SetPosition(Vector2D(textItem->rect.x, textItem->rect.y));
	_transform->SetSize(Vector2D(textItem->rect.w, textItem->rect.h));
}

void GUIButton::SetBackgroundColor()
{
	if (clicked)
	{
		backgroundItem->SetColor(downColor);
	}
	else if (isOver)
	{
		backgroundItem->SetColor(hoverColor);
	}
	else if (!isOver)
	{
		backgroundItem->SetColor(normalColor);
	}
}

void GUIButton::Update()
{
	if (_transform->GetRect().Contains(InputManager::GetInstance().GetMousePosition()))
	{
		if (InputManager::GetInstance().GetMouseDown(1))
		{
			OnClick();
		}
		if (!isOver)
		{
			OnEnter();
		}
	}
	else
	{
		if (isOver)
		{
			OnExit();
		}
	}
	if (clicked)
	{
		clickFrames++;
		if (clickFrames > 7) // TODO Use time here instead
		{
			clicked = false;
			clickFrames = 0;
			SetBackgroundColor();
		}
	}
}

void GUIButton::OnClick()
{
	std::cout << "OnClick" << std::endl;
	clicked = true;
	SetBackgroundColor();
	if (Callback != NULL)
	{
		Callback();
	}
}

void GUIButton::OnEnter()
{
	isOver = true;
	SetBackgroundColor();
	std::cout << "OnEnter" << std::endl;
}

void GUIButton::OnExit()
{
	isOver = false;
	SetBackgroundColor();
	std::cout << "OnExit" << std::endl;
}
