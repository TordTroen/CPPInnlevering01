#include "GUIToggleGroup.h"
#include "GUIToggle.h"

GUIToggleGroup::GUIToggleGroup()
{
}


GUIToggleGroup::~GUIToggleGroup()
{
}

void GUIToggleGroup::AddToggle(GUIToggle * toggle)
{
	toggle->SetToggleGroupIndex(toggles.size());
	toggles.emplace_back(toggle);
}

void GUIToggleGroup::Toggle(int toggleIndex)
{
	for (auto it : toggles)
	{
		// TODO Toggle that shit here
	}
}
