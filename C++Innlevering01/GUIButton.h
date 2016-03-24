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
	GUIButton(std::string text, Color textColor, Color bgColor, Rect rect, SDLWrapper* sdl, void (*CallbackFunction)(void), bool fitrectToText = true);
	// TODO Add padding between text and bg
	// TODO Add hover and click color
	~GUIButton();
protected:
	void Update() override;
	void Awake() override;
private:
	Drawable* textItem;
	Drawable* backgroundItem;
	void OnClick() const;
	void(*Callback)(void);
};

