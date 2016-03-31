#pragma once
class Rect;

class Vector2D
{
public:
	Vector2D();
	Vector2D(float x, float y);
	~Vector2D();
	float GetLength() const;
	Vector2D Normalized() const;
	Vector2D operator+(const Vector2D & v) const;
	Vector2D operator-(const Vector2D & v) const;
	Vector2D operator*(const float & s) const;
	bool operator==(const Vector2D & v) const;
	bool operator!=(const Vector2D & v) const;
	float X;
	float Y;
};

