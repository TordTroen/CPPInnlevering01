#pragma once
#include "Component.h"
#include "Rect.h"
#include "Collider.h"
#include "LevelBrick.h"
#include "Player.h"
class PowerUpBlock :
	public Component
{
public:
	PowerUpBlock(Vector2D start, float speed, PowerType pType);
	~PowerUpBlock();
	void Awake() override;
	void Update() override;

	void OnCollisionEnter(const Collider * const other) override;

private:
	Player* player;
	PowerType pType;
	Vector2D starting;
	LevelBrick* BlockObj;
	PowerType powerType;
	float speedBox;
};

