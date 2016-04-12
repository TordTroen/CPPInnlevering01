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
	static Color GetBrickColor(BrickType brickType, int health);
	void OnCollisionEnter(const Collider* const other) override;
	void Awake() override;
	static const float BrickWidth;
	static const float BrickHeight;
	void GiveScore(int amount) { scoreReward += amount; }
	int GetScore() const { return scoreReward; }
private:
	Color GetColorBasedOnHealth();
	ImageRenderer* imageRenderer;
	void TakeDamage();
	Vector2D brickPos;
	BrickType brickType;
	int scoreReward;
	int health;
	bool indestructible;
};

