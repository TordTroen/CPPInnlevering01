#pragma once
#include "GUIMenu.h"
#include "Vector2D.h"

enum class Alignment
{
	VerticalCenter,
	HorizontalCenter,
	Left,
	Right,
	Top,
	Bottom
};

class GUILayoutMenu
	: public GUIMenu
{
public:
	GUILayoutMenu(Alignment alignment, int startMargin, int spacing, bool activeState = true);
	~GUILayoutMenu();
	void AddElement(GUIElement* const element) override;
	void AddElements(std::vector<GUIElement*> elements) override;
	void SetSpacing(int spacing) { this->spacing = spacing; }
	float GetSize() const;
	void SetOverrideSize(Vector2D overrideSize) { this->overrideSize = overrideSize; }
	bool IsVertical() const;
private:
	Vector2D overrideSize;
	int margin;
	int spacing;
	Vector2D curPos;
	Alignment alignment;
};

