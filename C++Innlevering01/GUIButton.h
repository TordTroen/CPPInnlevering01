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
	GUIButton(std::string text, Color textColor, Color normalColor, Color downColor, Color hoverColor, Rect rect, int textPadding, std::shared_ptr<GUIMenu> deactivateMenu, std::shared_ptr<GUIMenu> activateMenu, bool fitRectToText = true);
	GUIButton(std::string text, Color textColor, Color normalColor, Color downColor, Color hoverColor, Rect rect, int textPadding, std::shared_ptr<GUIMenu> deactivateMenu, std::shared_ptr<GUIMenu> activateMenu, void(*CallbackFunction)(void), bool fitRectToText = true);
	~GUIButton();
protected:
	void Update() override;
	void Awake() override;
	void OnSetActive() override;
private:
	void Init(std::string text, Color textColor, Color normalColor, Color downColor, Color hoverColor, Rect rect, int textPadding, std::shared_ptr<GUIMenu> deactivateMenu, std::shared_ptr<GUIMenu> activateMenu, void(*CallbackFunction)(void), bool fitRectToText);
	void SetBackgroundColor();
	std::shared_ptr<Drawable> textItem;
	std::shared_ptr<Drawable> backgroundItem;
	void OnClick();
	void OnEnter();
	void OnExit();
	void(*Callback)(void);
	void ToggleMenus();
	std::shared_ptr<GUIMenu> activateMenu;
	std::shared_ptr<GUIMenu> deactivateMenu;
	Color normalColor;
	Color downColor;
	Color hoverColor;
	bool isOver;
	bool downOver;
};

