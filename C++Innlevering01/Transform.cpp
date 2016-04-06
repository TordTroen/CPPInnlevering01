#include "Transform.h"
#include <iostream>
#include "GameManager.h"
using namespace std;

Transform::Transform()
{
	position = Vector2D(0, 0);
	size = Vector2D(100, 100);
}

Transform::Transform(Vector2D pos, Vector2D size)
{
	position = pos;
	size = size;
}

Transform::~Transform()
{
}

void Transform::Translate(Vector2D const trans, bool limitToScreen)
{
	Vector2D v = trans;
	if (limitToScreen)
	{
		int windowWidth = GameManager::GetInstance().GetWindowWidth();
		int windowHeight = GameManager::GetInstance().GetWindowHeight();
		int xTrans = position.X + v.X;
		//if (_position.X + _size.X + v.X > windowWidth)
		if (xTrans + size.X > windowWidth)
		{
			v.X = 0;
		}
		else if (xTrans < 0)
		{
			v.X = 0;
		}
		if (position.Y + size.Y + v.Y > windowHeight)
		{
			v.Y = 0;
		}
		else if (position.Y + v.Y < 0)
		{
			v.Y = 0;
		}
		// Don't do the translation if the translation would result in it being outside the screen
		/*if (_position.X + _size.X + v.X > windowWidth || _position.X + v.X < 0 
			|| _position.Y + _size.Y + v.Y > windowHeight || _position.Y + v.Y < 0)
		{
			return;
		}*/
	}
	
	position = position + v;
}

void Transform::SetPosition(Vector2D newPos)
{
	position = newPos;
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
