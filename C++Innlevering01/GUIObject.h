#pragma once
#include "Rect.h"
class GUIObject
{
public:
	GUIObject();
	~GUIObject();
	void Render();
	virtual void OnClick();
	Rect rect;
};

