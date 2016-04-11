#include "GUIButton.h"
#include "Transform.h"
#include "InputManager.h"
#include <iostream>

GUIButton::GUIButton(std::string text, Color textColor, Color normalColor, Color downColor, Color hoverColor, Rect rect, int textPadding, void(*CallbackFunction)(void), bool fitRectToText)
{
	Init(text, textColor, normalColor, downColor, hoverColor, rect, textPadding, NULL, NULL, CallbackFunction, fitRectToText, false);
}

GUIButton::GUIButton(std::string text, Color textColor, Color normalColor, Color downColor, Color hoverColor, Rect rect, int textPadding, Color overrideColor, bool fitRectToText)
{
	Init(text, textColor, normalColor, downColor, hoverColor, rect, textPadding, NULL, NULL, NULL, fitRectToText, true);
	this->overrideColor = overrideColor;
}

GUIButton::GUIButton(std::string text, Color textColor, Color normalColor, Color downColor, Color hoverColor, Rect rect, int textPadding, GUIMenu* const deactivateMenu, GUIMenu* const activateMenu, bool fitRectToText)
{
	Init(text, textColor, normalColor, downColor, hoverColor, rect, textPadding, deactivateMenu, activateMenu, NULL, fitRectToText, false);
}

GUIButton::GUIButton(std::string text, Color textColor, Color normalColor, Color downColor, Color hoverColor, Rect rect, int textPadding, GUIMenu* const deactivateMenu, GUIMenu* const activateMenu, void(*CallbackFunction)(void), bool fitRectToText)
{
	Init(text, textColor, normalColor, downColor, hoverColor, rect, textPadding, deactivateMenu, activateMenu, CallbackFunction, fitRectToText, false);
}

GUIButton::~GUIButton()
{
}

void GUIButton::SyncDrawableWithTransform()
{
	if (backgroundItem != NULL)
	{
		GetTransform()->SetRect(backgroundItem->GetRect().Expanded(textPadding));
	}
	else if (textItem != NULL)
	{
		GetTransform()->SetRect(textItem->GetRect());
	}

	// Cant do this before setting transform rect, because if drawable has component, it return the transforms rect
	textItem->SetComponent(this, -textPadding);
	backgroundItem->SetComponent(this, 0);
}

void GUIButton::SetOverrideColorActive(bool isOverriding)
{
	isOverridingColor = isOverriding;
	SetBackgroundColor();
}

void GUIButton::OnSetActive()
{
	backgroundItem->SetActive(IsActive());
	textItem->SetActive(IsActive());
}

void GUIButton::Init(std::string text, Color textColor, Color normalColor, Color downColor, Color hoverColor, Rect rect, int textPadding, GUIMenu* const deactivateMenu, GUIMenu* const activateMenu, void(*CallbackFunction)(void), bool fitRectToText, bool hasOverrideColor)
{
	this->activateMenu = activateMenu;
	this->deactivateMenu = deactivateMenu;
	Callback = CallbackFunction;
	isOver = false;
	this->hasOverrideColor = hasOverrideColor;

	// Store the colors for the different states
	this->normalColor = normalColor;
	this->downColor = downColor;
	this->hoverColor = hoverColor;
	this->textPadding = textPadding;

	// Make the background and text
	backgroundItem = SDLWrapper::GetInstance().CreateRect(normalColor, rect);
	textItem = SDLWrapper::GetInstance().CreateText(text, textColor, rect, fitRectToText);

	// Make the background fit the text, and apply the padding
	Rect bgRect = textItem->GetRect();
	if (textPadding != 0)
	{
		bgRect.Grow(textPadding);
	}
	backgroundItem->SetRect(bgRect);
}

void GUIButton::SetBackgroundColor()
{
	if (isOverridingColor)
	{
		backgroundItem->SetColor(overrideColor);
	}
	else if (downOver && isOver)
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
	if (GetTransform()->GetRect().Contains(InputManager::GetInstance().GetMousePosition()))
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
	if (Callback != NULL)
	{
		Callback();
	}
	ToggleMenus();
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
}

void GUIButton::ToggleMenus()
{
	if (activateMenu != NULL)
	{
		activateMenu->SetActive(true);
	}
	if (deactivateMenu != NULL)
	{
		deactivateMenu->SetActive(false);
	}
}
