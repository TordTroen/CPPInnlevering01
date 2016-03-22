#pragma once
#include "Vector2D.h"
class Rect
{
public:
	Rect();
	Rect(float x, float y, float w, float h);
	float x;
	float y;
	float w;
	float h;
	bool Contains(Vector2D point);
};

