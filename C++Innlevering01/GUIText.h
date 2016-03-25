#pragma once
#include "Component.h"
#include "Drawable.h"
#include <string>

class GUIText :
	public Component
{
public:
	GUIText(std::string text, Color color, Rect rect);
	~GUIText();
protected:
	void Awake() override;
	void OnSetActive() override;
private:
	Drawable* textItem;
};

