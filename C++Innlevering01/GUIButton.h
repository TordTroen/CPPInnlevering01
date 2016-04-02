#pragma once
#include <string>
#include "SDLWrapper.h"
#include "Rect.h"
#include "Color.h"
#include "GUIElement.h"
#include "GUIMenu.h"

class GUIManager;

class GUIButton
	: public GUIElement
{
public:
	GUIButton(std::string text, Color textColor, Color normalColor, Color downColor, Color hoverColor, Rect rect, int textPadding, void(*CallbackFunction)(void), bool fitRectToText = true);
	GUIButton(std::string text, Color textColor, Color normalColor, Color downColor, Color hoverColor, Rect rect, int textPadding, GUIManager* gui, void(*CBF)(void), bool fitRectToText = true);
	GUIButton(std::string text, Color textColor, Color normalColor, Color downColor, Color hoverColor, Rect rect, int textPadding, GUIMenu* deactivateMenu, GUIMenu* activateMenu, bool fitRectToText = true);
	GUIButton(std::string text, Color textColor, Color normalColor, Color downColor, Color hoverColor, Rect rect, int textPadding, GUIMenu* deactivateMenu, GUIMenu* activateMenu, void(*CallbackFunction)(void), bool fitRectToText = true);
	~GUIButton();
protected:
	void Update() override;
	void Awake() override;
	void OnSetActive() override;
private:
	GUIManager* _gui;
	void Init(std::string text, Color textColor, Color normalColor, Color downColor, Color hoverColor, Rect rect, int textPadding, GUIMenu* deactivateMenu, GUIMenu* activateMenu, void(*CallbackFunction)(void), bool fitRectToText);
	void SetBackgroundColor();
	Drawable* textItem;
	Drawable* backgroundItem;
	void OnClick();
	void OnEnter();
	void OnExit();
	void(*Callback)(void);
	void(*cbf)(void);
	void ToggleMenus();
	GUIMenu* activateMenu;
	GUIMenu* deactivateMenu;
	Color normalColor;
	Color downColor;
	Color hoverColor;
	bool isOver;
	bool downOver;
};

