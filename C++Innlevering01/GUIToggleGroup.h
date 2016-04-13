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
	int GetCurrentToggleIndex() const { return curToggled; }
	void SyncDrawableWithTransform() override { }
	void Reset();
private:
	int curToggled;
	std::vector<GUIToggle*> toggles;
};

