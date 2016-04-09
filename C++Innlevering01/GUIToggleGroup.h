#pragma once
#include "GUIElement.h"
#include <vector>
class GUIToggle;

class GUIToggleGroup :
	public GUIElement
{
public:
	GUIToggleGroup();
	~GUIToggleGroup();
	void AddToggle(GUIToggle* toggle);
	void Toggle(int toggleIndex);
	int GetCurrentToggle() const { return curToggled; }
private:
	int curToggled;
	std::vector<GUIToggle*> toggles;
};

