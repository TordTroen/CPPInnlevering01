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
	GUIButton(std::string text, Color textColor, Color normalColor, Color downColor, Color hoverColor, Rect rect, int textPadding, Color overrideColor, bool fitRectToText = true);
	GUIButton(std::string text, Color textColor, Color normalColor, Color downColor, Color hoverColor, Rect rect, int textPadding, GUIMenu* const deactivateMenu, GUIMenu* const activateMenu, bool fitRectToText = true);
	GUIButton(std::string text, Color textColor, Color normalColor, Color downColor, Color hoverColor, Rect rect, int textPadding, GUIMenu* const deactivateMenu, GUIMenu* const activateMenu, void(*CallbackFunction)(void), bool fitRectToText = true);
	~GUIButton();
	void SyncDrawableWithTransform() override;
	void SetOverrideColorActive(bool isOverriding);
protected:
	void Update() override;
	void Awake() override;
	void OnSetActive() override;
private:
	bool isOverridingColor;
	bool hasOverrideColor;
	Color overrideColor;
	void Init(std::string text, Color textColor, Color normalColor, Color downColor, Color hoverColor, Rect rect, int textPadding, GUIMenu* const deactivateMenu, GUIMenu* const activateMenu, void(*CallbackFunction)(void), bool fitRectToText, bool hasOverrideColor);
	void SetBackgroundColor();
	Drawable* textItem;
	Drawable* backgroundItem;
	virtual void OnClick();
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
	int textPadding;
};

