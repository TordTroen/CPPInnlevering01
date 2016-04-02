#pragma once
#include "Component.h"
#include "Collider.h"
#include "Vector2D.h"

enum BrickType
{
	Empty,
	Yellow,
	Orange,
	Red,
	Powerup,
	Indestructible
};

class LevelBrick
	: public Component
{
public:
	LevelBrick(Vector2D pos, BrickType brickType, int health, bool indestructible);
	~LevelBrick();
	void OnCollisionEnter(const Collider* other) override;
	void Awake() override;
	static const float BrickWidth;
	static const float BrickHeight;
private:
	void TakeDamage();
	Vector2D _brickPos;
	BrickType _brickType;
	int _scoreReward;
	int _health;
	bool _indestructible;
};

