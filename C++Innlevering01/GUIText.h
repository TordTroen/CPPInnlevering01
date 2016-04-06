#pragma once
#include "Drawable.h"
#include <string>
#include <memory>
#include "GUIElement.h"

class GUIText :
	public GUIElement
{
public:
	GUIText(std::string text, Color color, Rect rect);
	~GUIText();
	void SetText(std::string text);
	void SyncDrawableWithTransform() override;
protected:
	void Awake() override;
	void OnSetActive() override;
private:
	Drawable* textItem;
};

