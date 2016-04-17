#include "Transform.h"
#include <iostream>
#include "GameManager.h"
using namespace std;

Transform::Transform()
	: Transform(Vector2D(0, 0), Vector2D(100, 100))
{
}

Transform::Transform(Vector2D pos, Vector2D size)
	: parent(NULL)
{
	position = pos;
	size = size;
}

Transform::~Transform()
{
}

void Transform::Translate(Vector2D const trans, bool clampToScreen)
{
	Vector2D v = trans;
	if (clampToScreen)
	{
		int w = gameManager->GetWindowWidth();
		int h = gameManager->GetWindowHeight();

		// Define the corners of the translation 
		int lx = position.X + v.X;
		int rx = position.X + v.X + size.X;
		int ty = position.Y + v.Y;
		int by = position.Y + v.Y + size.Y;

		// If the translation is outside the screen, take away the difference from the velocity
		if (rx > w)
		{
			v.X -= rx - w;
		}
		else if (lx < 0)
		{
			v.X -= lx;
		}
		if (by > h)
		{
			v.Y -= by - h;
		}
		else if (ty < 0)
		{
			v.Y -= ty;
		}
	}
	
	//position = position + v;
	SetPosition(position + v);
}

void Transform::SetPosition(Vector2D newPos)
{
	if (parent == NULL)
	{
		position = newPos;
	}
	else
	{
		position = newPos + parent->GetPosition();
	}
}

void Transform::SetSize(Vector2D newSize)
{
	size = newSize;
}

void Transform::SetRect(Rect rect)
{
	SetPosition(Vector2D(rect.x, rect.y));
	SetSize(Vector2D(rect.w, rect.h));
}

Vector2D Transform::GetCenter() const
{
	return Vector2D(position.X + size.X / 2, position.Y + size.Y / 2);
}

Rect Transform::GetRect() const
{
	return Rect(position.X, position.Y, size.X, size.Y);
}

void Transform::SetParent(Transform * newParent, bool keepPosition)
{
	parent = newParent;
	if (!keepPosition)
	{
		SetPosition(position);
	}
}
