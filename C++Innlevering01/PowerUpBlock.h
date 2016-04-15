#pragma once
#include "Component.h"
#include "Rect.h"
class PowerUpBlock :
	public Component
{
public:
	PowerUpBlock(Vector2D start, float speed);
	~PowerUpBlock();
	void Update() override;

private:
	Vector2D starting;
	float speedBox;
};

