#pragma once
#include "Component.h"
#include "Rect.h"

class PaddleMovement :
	public Component
{
public:
	PaddleMovement(Rect startRect, float speed);
	~PaddleMovement();
	void Awake() override;
	void Update() override;
	void Reset();
private:
	float paddleSpeed;
	Rect startRect;
};

