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
	//for (auto it : toggles)
	for (int i = 0; i < toggles.size(); i ++)
	{
		// TODO Toggle that shit here
		toggles[i]->SetToggleActive(toggleIndex == i);
	}
}
