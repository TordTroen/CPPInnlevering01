#pragma once
#include "Component.h"

/* Class that all GUIElements derive from, so we can store all elements in the same container. */
class GUIElement :
	public Component
{
public:
	GUIElement();
	~GUIElement();
	// TODO Find a better way to do this. This is necessary when creating GUIelements without directly adding them to a GameObject (because the Drawables will then have a Rect different from the Transform). 
	//		This feels like a wrong approach/logic error in the current system
	/* Used when creating elements directly in GUIMenu's AddElement functions. */
	virtual void SyncPositionWithTransform() = 0;
};

