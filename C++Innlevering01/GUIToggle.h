#pragma once
#include "GUIButton.h"
#include <string>
class GUIToggleGroup;

class GUIToggle :
	public GUIButton
{
public:
	GUIToggle(std::string text, Color textColor, Color normalColor, Color downColor, Color hoverColor, Color toggeledColor, Rect rect, int textPadding, GUIToggleGroup* toggleGroup, bool fitRectToText = true);
	virtual ~GUIToggle();
	void SetToggleGroupIndex(int index) { this->index = index; }
	void SetToggleActive(bool toggeled);
	bool IsToggeled() const { return isToggeled; }
private:
	void OnClick() override;
	int index;
	bool isToggeled;
	GUIToggleGroup* toggleGroup;
};

