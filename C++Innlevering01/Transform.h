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
	void Translate(Vector2D const trans, bool clampToScreen = false);
	void SetPosition(Vector2D const newPos);
	void SetSize(Vector2D const newSize);
	void SetRect(Rect rect);
	Vector2D GetCenter() const;
	Rect GetRect() const;
	Vector2D GetPosition() const { return position; }
	Vector2D GetSize() const { return size; }
private:
	Vector2D position;
	Vector2D size;
};

