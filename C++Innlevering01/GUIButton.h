#pragma once
#include <string>
#include <memory>
#include "SDLWrapper.h"
#include "Rect.h"
#include "Color.h"
#include "GUIElement.h"
#include "GUIMenu.h"

class GUIButton
	: public GUIElement
{
public:
	GUIButton(std::string text, Color textColor, Color normalColor, Color downColor, Color hoverColor, Rect rect, int textPadding, void(*CallbackFunction)(void), bool fitRectToText = true);
	GUIButton(std::string text, Color textColor, Color normalColor, Color downColor, Color hoverColor, Rect rect, int textPadding, GUIMenu* const deactivateMenu, GUIMenu* const activateMenu, bool fitRectToText = true);
	GUIButton(std::string text, Color textColor, Color normalColor, Color downColor, Color hoverColor, Rect rect, int textPadding, GUIMenu* const deactivateMenu, GUIMenu* const activateMenu, void(*CallbackFunction)(void), bool fitRectToText = true);
	~GUIButton();
	void SyncPositionWithTransform();
protected:
	void Update() override;
	void Awake() override;
	void OnSetActive() override;
private:
	void Init(std::string text, Color textColor, Color normalColor, Color downColor, Color hoverColor, Rect rect, int textPadding, GUIMenu* const deactivateMenu, GUIMenu* const activateMenu, void(*CallbackFunction)(void), bool fitRectToText);
	void SetBackgroundColor();
	Drawable* textItem;
	Drawable* backgroundItem;
	void OnClick();
	void OnEnter();
	void OnExit();
	void(*Callback)(void);
	void ToggleMenus();
	GUIMenu* activateMenu;
	GUIMenu* deactivateMenu;
	Color normalColor;
	Color downColor;
	Color hoverColor;
	bool isOver;
	bool downOver;
	int _textPadding;
};

