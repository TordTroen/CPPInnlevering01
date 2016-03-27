#pragma once
#include "Vector2D.h"
#include "Component.h"
#include "Rect.h"

class Transform : public Component
{
public:
	Transform();
	Transform(Vector2D pos, Vector2D size);
	~Transform();
	void Translate(Vector2D const trans, bool limitToScreen = false);
	void SetPosition(Vector2D const newPos);
	void SetSize(Vector2D const newSize);
	void SetRect(Rect rect);
	Vector2D _position;
	Vector2D _size;
	Rect GetRect() const;
};

