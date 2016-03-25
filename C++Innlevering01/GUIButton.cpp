#include "GUIButton.h"
#include "Transform.h"
#include "InputManager.h"
#include <iostream>

GUIButton::GUIButton(std::string text, Color color, Color normalColor, Color downColor, Color hoverColor, Rect rect, int textPadding, void(*CallbackFunction)(void), bool fitRectToText)
	: isOver(false)
{
	// Store the colors for the different states
	this->normalColor = normalColor;
	this->downColor = downColor;
	this->hoverColor = hoverColor;

	// Make the background and text
	backgroundItem = SDLWrapper::GetInstance().CreateRect(normalColor, rect);
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
	_transform->SetPosition(Vector2D(backgroundItem->rect.x, backgroundItem->rect.y));
	_transform->SetSize(Vector2D(backgroundItem->rect.w, backgroundItem->rect.h));
}

void GUIButton::OnSetActive()
{
	backgroundItem->SetActive(IsActive());
	textItem->SetActive(IsActive());
}

void GUIButton::SetBackgroundColor()
{
	//std::cout << "Clicked = " << clicked << std::endl;
	if (downOver && isOver)
	{
		backgroundItem->SetColor(downColor);
		//std::cout << " -> Setting BG Color to DOWN" << std::endl;
	}
	else if (isOver)
	{
		backgroundItem->SetColor(hoverColor);
		//std::cout << " -> Setting BG Color to HOVER" << std::endl;
	}
	else if (!isOver)
	{
		backgroundItem->SetColor(normalColor);
		//std::cout << " -> Setting BG Color to NORMAL" << std::endl;
	}
}

void GUIButton::Update()
{
	if (_transform->GetRect().Contains(InputManager::GetInstance().GetMousePosition()))
	{
		if (InputManager::GetInstance().GetMouseDown(1))
		{
			downOver = true;
			SetBackgroundColor();
		}
		else if (InputManager::GetInstance().GetMouseUp(1))
		{
			if (downOver)
			{
				OnClick();
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
			//std::cout << "down outside" << std::endl;
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
	//std::cout << "OnClick" << std::endl;
	if (Callback != NULL)
	{
		Callback();
	}
	SetActive(false);
}

void GUIButton::OnEnter()
{
	isOver = true;
	SetBackgroundColor();
	//std::cout << "OnEnter" << std::endl;
}

void GUIButton::OnExit()
{
	isOver = false;
	SetBackgroundColor();
	//std::cout << "OnExit" << std::endl;
}
