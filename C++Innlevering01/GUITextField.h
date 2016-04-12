#pragma once
#include "GUIText.h"
#include "SDL.h"
#include "GUIButton.h"

class GUITextField
	: public GUIButton
{
public:
	GUITextField(std::string startText, Rect rect);
	~GUITextField();
	void Update() override;
	std::string GetInputText() const { return inputText; }
private:
	void StartInput();
	void StopInput();
	void OnClick() override;
	bool takeInput;
	std::string inputText;
	SDL_Event e;
};

