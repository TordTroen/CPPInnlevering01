#include "GUIButton.h"
#include "Transform.h"
#include "InputManager.h"
#include <iostream>

GUIButton::GUIButton(std::string text, Color textColor, Color normalColor, Color downColor, Color hoverColor, Rect rect, int textPadding, void(*CallbackFunction)(void), bool fitRectToText)
{
	//activateMenu = NULL;
	//deactivateMenu = NULL;

	Init(text, textColor, normalColor, downColor, hoverColor, rect, textPadding, NULL, NULL, CallbackFunction, fitRectToText);
	
	// Assign the callback function
	//Callback = CallbackFunction;
}

GUIButton::GUIButton(std::string text, Color textColor, Color normalColor, Color downColor, Color hoverColor, Rect rect, int textPadding, GUIMenu* deactivateMenu, GUIMenu* activateMenu, bool fitRectToText)
{
	Init(text, textColor, normalColor, downColor, hoverColor, rect, textPadding, deactivateMenu, activateMenu, NULL, fitRectToText);

	//this->activateMenu = activateMenu;
	//this->deactivateMenu = deactivateMenu;
	//Callback = NULL;
}

GUIButton::GUIButton(std::string text, Color textColor, Color normalColor, Color downColor, Color hoverColor, Rect rect, int textPadding, GUIMenu * deactivateMenu, GUIMenu * activateMenu, void(*CallbackFunction)(void), bool fitRectToText)
{
	Init(text, textColor, normalColor, downColor, hoverColor, rect, textPadding, deactivateMenu, activateMenu, CallbackFunction, fitRectToText);

	//this->activateMenu = activateMenu;
	//this->deactivateMenu = deactivateMenu;
	//Callback = Callback;
}

GUIButton::~GUIButton()
{
}

void GUIButton::Awake()
{
	// Make sure the button is positioned at the correct position
	//GetTransform()->SetPosition(Vector2D(backgroundItem->rect.x, backgroundItem->rect.y));
	//GetTransform()->SetSize(Vector2D(backgroundItem->rect.w, backgroundItem->rect.h));
	GetTransform()->SetRect(backgroundItem->rect);
}

void GUIButton::OnSetActive()
{
	backgroundItem->SetActive(IsActive());
	textItem->SetActive(IsActive());
}

void GUIButton::Init(std::string text, Color textColor, Color normalColor, Color downColor, Color hoverColor, Rect rect, int textPadding, GUIMenu* deactivateMenu, GUIMenu* activateMenu, void(*CallbackFunction)(void), bool fitRectToText)
{
	this->activateMenu = activateMenu;
	this->deactivateMenu = deactivateMenu;
	Callback = CallbackFunction;
	isOver = false;

	// Store the colors for the different states
	this->normalColor = normalColor;
	this->downColor = downColor;
	this->hoverColor = hoverColor;

	// Make the background and text
	backgroundItem = SDLWrapper::GetInstance().CreateRect(normalColor, rect);
	textItem = SDLWrapper::GetInstance().CreateText(text, textColor, rect, fitRectToText);

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
}

void GUIButton::SetBackgroundColor()
{
	if (downOver && isOver)
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
