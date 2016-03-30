#include "Transform.h"
#include <iostream>
#include "GameManager.h"
using namespace std;

Transform::Transform()
{
	_position = Vector2D(0, 0);
	_size = Vector2D(100, 100);
}

Transform::Transform(Vector2D pos, Vector2D size)
{
	_position = pos;
	_size = size;
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
		int xTrans = _position.X + v.X;
		//if (_position.X + _size.X + v.X > windowWidth)
		if (xTrans + _size.X > windowWidth)
		{
			v.X = 0;
		}
		else if (xTrans < 0)
		{
			v.X = 0;
		}
		if (_position.Y + _size.Y + v.Y > windowHeight)
		{
			v.Y = 0;
		}
		else if (_position.Y + v.Y < 0)
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
	
	_position = _position + v;
}

void Transform::SetPosition(Vector2D newPos)
{
	_position = newPos;
}

void Transform::SetSize(Vector2D newSize)
{
	_size = newSize;
}

void Transform::SetRect(Rect rect)
{
	SetPosition(Vector2D(rect.x, rect.y));
	SetSize(Vector2D(rect.w, rect.h));
}

Rect Transform::GetRect() const
{
	return Rect(_position.X, _position.Y, _size.X, _size.Y);
}
