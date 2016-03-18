#include "Transform.h"
#include <iostream>
#include "GameManager.h"
using namespace std;

Transform::Transform()
{
	std::cout << "Tranform constructor" << std::endl;
	_position = Vector2D(0, 0);
	_size = Vector2D(100, 100);
}

Transform::Transform(Vector2D pos, Vector2D size)
{
	std::cout << "Tranform constructor" << std::endl;
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
		/*if (_position.X + _size.X + v.X > windowWidth)
		{
			v.X = 0;
		}
		else if (_position.X + v.X < 0)
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
		}*/
		// Don't do the translation if the translation would result in it being outside the screen
		if (_position.X + _size.X + v.X > windowWidth || _position.X + v.X < 0 
			|| _position.Y + _size.Y + v.Y > windowHeight || _position.Y + v.Y < 0)
		{
			return;
		}
	}
	
	_position = _position + v;
}

void Transform::SetPosition(Vector2D const newPos)
{
	_position = newPos;
}

void Transform::SetSize(Vector2D const newSize)
{
	_size = newSize;
}
