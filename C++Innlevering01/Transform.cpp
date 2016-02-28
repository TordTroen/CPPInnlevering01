#include "Transform.h"
#include <iostream>
using namespace std;

Transform::Transform()
	: Component("Transform")
{
	std::cout << "Tranform constructor" << std::endl;
	_position = Vector2D(0, 0);
	_size = Vector2D(100, 100);
}

Transform::Transform(Vector2D pos, Vector2D size)
	: Component("Transform")
{
	std::cout << "Tranform constructor" << std::endl;
	_position = pos;
	_size = size;
}

Transform::~Transform()
{
}

void Transform::Translate(Vector2D const trans)
{
	_position = _position + trans;
}

void Transform::SetPosition(Vector2D const newPos)
{
	_position = newPos;
}

void Transform::SetSize(Vector2D const newSize)
{
	_size = newSize;
}
