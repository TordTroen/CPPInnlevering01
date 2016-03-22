#pragma once
#include "Rect.h"
class GUIObject
{
public:
	GUIObject();
	~GUIObject();
	void Render();
	//virtual void OnClick();
	// AddEvent(void function())???
	// then OnClick has parameter for button names or something?
	Rect rect;
};

