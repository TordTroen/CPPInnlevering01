#pragma once
#include "Drawable.h"
#include <string>
#include "GUIElement.h"

class GUIText :
	public GUIElement
{
public:
	GUIText(std::string text, Color color, Rect rect);
	~GUIText();
	void SetText(std::string text);
protected:
	void Awake() override;
	void OnSetActive() override;
private:
	Drawable* textItem;
};

