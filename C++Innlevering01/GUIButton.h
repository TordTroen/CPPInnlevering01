#pragma once
#include <string>
#include "Component.h"
#include "SDLWrapper.h"
#include "Rect.h"
#include "Color.h"
class GUIButton
	: public Component
{
public:
	GUIButton(std::string text, Color textColor, Color normalColor, Color downColor, Color hoverColor, Rect rect, int textPadding, void (*CallbackFunction)(void), bool fitrectToText = true);
	// TODO Add padding between text and bg
	// TODO Add hover and click color
	~GUIButton();
protected:
	void Update() override;
	void Awake() override;
private:
	void SetBackgroundColor();
	Drawable* textItem;
	Drawable* backgroundItem;
	void OnClick();
	void OnEnter();
	void OnExit();
	void(*Callback)(void);
	Color normalColor;
	Color downColor;
	Color hoverColor;
	bool isOver;
	bool clicked;
	int clickFrames;
};
