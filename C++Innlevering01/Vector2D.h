#pragma once
class Vector2D
{
public:
	Vector2D();
	Vector2D(float x, float y);
	~Vector2D();
	Vector2D operator+(const Vector2D & v) const;
	Vector2D Vector2D::operator*(const float & s) const;
	bool operator==(const Vector2D & v) const;
	bool operator!=(const Vector2D & v) const;
	float X;
	float Y;
};

