#include "Vector2D.h"

Vector2D::Vector2D()
	: X(0), Y(0)
{
}

Vector2D::Vector2D(int x, int y)
	: X(x), Y(y)
{
}


Vector2D::~Vector2D()
{
}

Vector2D Vector2D::operator+(const Vector2D & v) const
{
	return Vector2D(X + v.X, Y + v.Y);
}

bool Vector2D::operator==(const Vector2D & v) const
{
	return (X == v.X && Y == v.Y);
}

bool Vector2D::operator!=(const Vector2D & v) const
{
	return (X != v.X && Y != v.Y);
}
