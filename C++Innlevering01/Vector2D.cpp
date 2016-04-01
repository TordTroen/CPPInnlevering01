#include "Vector2D.h"
#include <math.h>
#include <iostream>

Vector2D::Vector2D()
	: X(0), Y(0)
{
}

Vector2D::Vector2D(float x, float y)
	: X(x), Y(y)
{
}


Vector2D::~Vector2D()
{
}

float Vector2D::GetLength() const
{
	return sqrt(X*X + Y*Y);
}

Vector2D Vector2D::Normalized() const
{
	float l = GetLength();
	//std::cout << "Vector: [" << (X / l) << ", " << (Y / l) << "]" << std::endl;
	return Vector2D(X / l, Y / l);
}

Vector2D Vector2D::operator+(const Vector2D & v) const
{
	return Vector2D(X + v.X, Y + v.Y);
}

Vector2D Vector2D::operator-(const Vector2D & v) const
{
	return Vector2D(X - v.X, Y - v.Y);
}

Vector2D Vector2D::operator*(const float & s) const
{
	return Vector2D(X * s, Y * s);
}

float Vector2D::operator*(const Vector2D & v) const
{
	return (X * v.X + Y * v.Y);
}

bool Vector2D::operator==(const Vector2D & v) const
{
	return (X == v.X && Y == v.Y);
}

bool Vector2D::operator!=(const Vector2D & v) const
{
	return (X != v.X && Y != v.Y);
}
