#pragma once
#include "Component.h"

/* Class that all GUIElements derive from, so we can store all elements in the same container. */
class GUIElement :
	public Component
{
public:
	GUIElement();
	~GUIElement();
};

