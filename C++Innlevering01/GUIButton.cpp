#include "GUIButton.h"
#include "Transform.h"
#include "InputManager.h"
#include <iostream>

GUIButton::GUIButton(std::string text, Color color, Color normalColor, Color downColor, Color hoverColor, Rect rect, int textPadding, void(*CallbackFunction)(void), bool fitRectToText)
	: isOver(false), clicked(false), clickFrames(0)
{
	// Store the colors for the different states
	this->normalColor = normalColor;
	this->downColor = downColor;
	this->hoverColor = hoverColor;

	// Make the background and text
	backgroundItem = SDLWrapper::GetInstance().CreateImage("WhiteTexture.png", rect, normalColor, false);
	textItem = SDLWrapper::GetInstance().CreateText(text, color, rect, fitRectToText);

	// Make the background fit the text, and apply the padding
	Rect bgRect = textItem->rect;
	if (textPadding != 0)
	{
		bgRect.x -= textPadding;
		bgRect.y -= textPadding;
		bgRect.w += textPadding * 2;
		bgRect.h += textPadding * 2;
	}
	backgroundItem->SetRect(bgRect);

	// Assign the callback function
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
	//std::cout << "Clicked = " << clicked << std::endl;
	if (downOver && isOver)
	{
		backgroundItem->SetColor(downColor);
		std::cout << " -> Setting BG Color to DOWN" << std::endl;
	}
	else if (isOver)
	{
		backgroundItem->SetColor(hoverColor);
		std::cout << " -> Setting BG Color to HOVER" << std::endl;
	}
	else if (!isOver || !clicked)
	{
		backgroundItem->SetColor(normalColor);
		std::cout << " -> Setting BG Color to NORMAL" << std::endl;
	}
}

void GUIButton::Update()
{
	if (_transform->GetRect().Contains(InputManager::GetInstance().GetMousePosition()))
	{
		if (InputManager::GetInstance().GetMouseDown(1))
		{
			clicked = true;
			downOver = true;
			SetBackgroundColor();
		}
		else if (InputManager::GetInstance().GetMouseUp(1))
		{
			if (downOver)
			{
				OnClick();
				clicked = false;
				downOver = false;
				SetBackgroundColor();
			}
		}
		if (!isOver)
		{
			OnEnter();
		}
	}
	else
	{
		if (InputManager::GetInstance().GetMouseDown(1) || InputManager::GetInstance().GetMouseUp(1))
		{
			std::cout << "down outside" << std::endl;
			downOver = false;
		}
		if (isOver)
		{
			OnExit();
		}
	}
}

void GUIButton::OnClick()
{
	std::cout << "OnClick" << std::endl;
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
