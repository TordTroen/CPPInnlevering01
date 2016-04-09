#include "GUIToggle.h"
#include "GUIToggleGroup.h"

GUIToggle::GUIToggle(std::string text, Color textColor, Color normalColor, Color downColor, Color hoverColor, Color toggeledColor, Rect rect, int textPadding, GUIToggleGroup* toggleGroup)
	: GUIButton(text, textColor, normalColor, downColor, hoverColor, rect, textPadding, toggeledColor, false)
{
	this->toggleGroup = toggleGroup;
	toggleGroup->AddToggle(this);
}

GUIToggle::~GUIToggle()
{
}

void GUIToggle::SetToggleActive(bool toggeled)
{
	isToggeled = toggeled;
	SetOverrideColorActive(isToggeled);
}

void GUIToggle::OnClick()
{
	toggleGroup->Toggle(index);
}
