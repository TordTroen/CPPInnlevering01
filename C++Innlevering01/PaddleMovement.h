#pragma once
#include "Component.h"
class PaddleMovement :
	public Component
{
public:
	PaddleMovement();
	~PaddleMovement();
	void Update() override;
};

