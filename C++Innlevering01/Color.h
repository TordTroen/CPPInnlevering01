#pragma once
class Color
{
public:
	Color();
	Color(int r, int g, int b);
	Color(int r, int g, int b, int a);
	~Color();
	int GetR() const { return _r; }
	int GetG() const { return _g; }
	int GetB() const { return _b; }
	int GetA() const { return _a; }
private:
	void Set(int r, int g, int b);
	void Set(int r, int g, int b, int a);
	int _r;
	int _g;
	int _b;
	int _a;
};

