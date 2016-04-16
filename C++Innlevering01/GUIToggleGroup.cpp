#include "GUIToggleGroup.h"
#include "GUIToggle.h"

GUIToggleGroup::GUIToggleGroup()
{
}


GUIToggleGroup::~GUIToggleGroup()
{
}

void GUIToggleGroup::AddToggle(GUIToggle* toggle)
{
	toggle->SetToggleGroupIndex(toggles.size());
	toggles.emplace_back(toggle);

	// Toggle the first element
	if (toggles.size() == 1)
	{
		Toggle(0);
	}
}

void GUIToggleGroup::Toggle(int toggleIndex)
{
	// Make sure only the toggle we just toggeled is toggeled
	for (int i = 0; i < toggles.size(); i ++)
	{
		toggles[i]->SetToggleActive(toggleIndex == i);
	}

	curToggled = toggleIndex;
}

void GUIToggleGroup::Reset()
{
	toggles.clear();
}
