#pragma once
#include <memory>
#include "Component.h"
#include "Collider.h"
#include "Vector2D.h"
#include "Player.h"
class ImageRenderer;
class Color;

enum class BrickType
{
	BrickEmpty = 0,
	BrickNormal = 1,
	Brick2Hits = 2,
	Brick3Hits = 3,
	BrickGreen = 4,
	BrickBlue = 5,
	BrickPowerup = 6,
	BrickIndestructible = 7
};

enum class PowerType
{
	PowerPaddle,
	PowerLife
};

class LevelBrick
	: public Component
{
public:
	LevelBrick(Vector2D pos, BrickType brickType, int powerup, int health, bool indestructible);
	~LevelBrick();
	static Color GetBrickColor(BrickType brickType);
	void OnCollisionEnter(const Collider* const other) override;
	void Awake() override;
	static const float BrickWidth;
	static const float BrickHeight;
	int GetHealth() const;
	void PowerUp(int amount) { powerUpReward += amount; }
	int GetPowerUp() const { return powerUpReward; }
private:
	//Color GetColorBasedOnHealth();
	ImageRenderer* imageRenderer;
	Player* player;
	GameObject* powerPaddleObj;
	GameObject* powerLifeObj;
	int scoreReward;
	const float PowerUpWidth = 40;
	const float PowerUpHeight = 40;
	void PowerUp();
	void TakeDamage();
	void PowerPaddleBlock();
	void PowerLifeBlock();
	Vector2D brickPos;
	BrickType brickType;
	float powerUpSpeed = 2;
	int powerUpReward;
	int health;
	bool indestructible;
};

