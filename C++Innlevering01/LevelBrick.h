#pragma once
#include <memory>
#include "Component.h"
#include "Collider.h"
#include "Vector2D.h"
class ImageRenderer;
class Color;

enum BrickType
{
	BrickEmpty = 0,
	BrickNormal = 1, // 2, 3
	BrickGreen = 4,
	BrickBlue = 5,
	BrickPowerup = 6,
	BrickIndestructible = 7
};

class LevelBrick
	: public Component
{
public:
	LevelBrick(Vector2D pos, BrickType brickType, int health, bool indestructible);
	~LevelBrick();
	void OnCollisionEnter(const std::shared_ptr<Collider> other) override;
	void Awake() override;
	static const float BrickWidth;
	static const float BrickHeight;
private:
	Color GetColorBasedOnHealth();
	std::shared_ptr<ImageRenderer> _imageRenderer;
	void TakeDamage();
	Vector2D _brickPos;
	BrickType _brickType;
	int _scoreReward;
	int _health;
	bool _indestructible;
};

