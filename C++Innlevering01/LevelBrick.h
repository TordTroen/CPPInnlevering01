#pragma once
#include <memory>
#include "Component.h"
#include "Collider.h"
#include "Vector2D.h"
class ImageRenderer;
class Color;

enum class BrickType
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
	LevelBrick(Vector2D pos, BrickType brickType, int score, int health, bool indestructible);
	~LevelBrick();
	void OnCollisionEnter(const Collider* const other) override;
	void Awake() override;
	static const float BrickWidth;
	static const float BrickHeight;
	void GiveScore(int amount) { _scoreReward += amount; }
	int GetScore() const { return _scoreReward; }
private:
	Color GetColorBasedOnHealth();
	ImageRenderer* _imageRenderer;
	void TakeDamage();
	Vector2D _brickPos;
	BrickType _brickType;
	int _scoreReward;
	int _health;
	bool _indestructible;
};

