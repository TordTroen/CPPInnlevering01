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
	GUIButton(std::string text, Color color, Rect rect, SDLWrapper* sdl, bool fitrectToText = true);
	~GUIButton();
	void Update() override;
	void Awake();
	void OnClick();
private:
	Rect _tempRect;
	Drawable* textItem;
};

