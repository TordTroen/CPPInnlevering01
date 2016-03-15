#pragma once
#include "Vector2D.h"
#include "Component.h"

class Transform : public Component
{
public:
	Transform();
	Transform(Vector2D pos, Vector2D size);
	~Transform();
	void Translate(Vector2D const trans);
	void SetPosition(Vector2D const newPos);
	void SetSize(Vector2D const newSize);
	Vector2D _position;
	Vector2D _size;
};

