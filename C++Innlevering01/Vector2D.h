#pragma once
class Vector2D
{
public:
	Vector2D();
	Vector2D(int x, int y);
	~Vector2D();
	Vector2D operator+(const Vector2D & v) const;
	bool operator==(const Vector2D & v) const;
	bool operator!=(const Vector2D & v) const;
	int X;
	int Y;
};

