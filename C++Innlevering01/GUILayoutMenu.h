#pragma once
#include "GUIMenu.h"

class GUILayoutMenu
	: public GUIMenu
{
public:
	GUILayoutMenu(int startYpos, int spacing, bool activeState = true);
	~GUILayoutMenu();
	void AddElement(GUIElement* const element) override;
	void AddElements(std::vector<GUIElement*> elements) override;
	void SetStartingYPos(int startYPos);
	void SetSpacing(int spacing) { this->spacing = spacing; }
private:
	int curYpos;
	int spacing;
};

