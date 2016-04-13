#pragma once
#include <string>
#include <memory>
#include "SDLWrapper.h"
#include "Rect.h"
#include "Color.h"
#include "GUIElement.h"
#include "GUIMenu.h"
#include "GUIEventHandler.h"

class GUIButton
	: public GUIElement
{
public:
	GUIButton(std::string text, Color textColor, Color normalColor, Color downColor, Color hoverColor, Rect rect, int textPadding, void(GUIEventHandler::*CallbackFunction)(void), bool fitRectToText = true);
	GUIButton(std::string text, Color textColor, Color normalColor, Color downColor, Color hoverColor, Rect rect, int textPadding, Color overrideColor, bool fitRectToText = true);
	GUIButton(std::string text, Color textColor, Color normalColor, Color downColor, Color hoverColor, Rect rect, int textPadding, GUIMenu* const deactivateMenu, GUIMenu* const activateMenu, bool fitRectToText = true);
	GUIButton(std::string text, Color textColor, Color normalColor, Color downColor, Color hoverColor, Rect rect, int textPadding, GUIMenu* const deactivateMenu, GUIMenu* const activateMenu, void(GUIEventHandler::*CallbackFunction)(void), bool fitRectToText = true);
	~GUIButton();
	void SyncDrawableWithTransform() override;
	void SetOverrideColorActive(bool isOverriding);
	void SetColors(Color normal, Color down, Color hover);
protected:
	void Update() override;
	void OnSetActive() override;

	// TODO: Use GUIText and GUIRect elements instead of Drawables, let the GUItext&rect handle the drawables!
	Drawable* backgroundItem;
	Drawable* textItem;
private:
	void Awake() override;
	bool isOverridingColor;
	bool hasOverrideColor;
	Color overrideColor;
	void Init(std::string text, Color textColor, Color normalColor, Color downColor, Color hoverColor, Rect rect, int textPadding, GUIMenu* const deactivateMenu, GUIMenu* const activateMenu, void(GUIEventHandler::*CallbackFunction)(void), bool fitRectToText, bool hasOverrideColor);
	void SetBackgroundColor();
	virtual void OnClick();
	virtual void OnEnter();
	void OnExit();
	void(GUIEventHandler::*Callback)(void);
	GUIEventHandler* guiEventHandler;
	void ToggleMenus();
	GUIMenu* activateMenu;
	GUIMenu* deactivateMenu;
	Color normalColor;
	Color downColor;
	Color hoverColor;
	bool isOver;
	bool downOver;
	int textPadding;
};

