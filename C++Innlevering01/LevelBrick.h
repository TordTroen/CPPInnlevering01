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
	static const float PowerUpWidth;
	static const float PowerUpHeight;
	void PowerUp(int amount) { powerUpReward += amount; }
	int GetPowerUp() const { return powerUpReward; }
private:
	//Color GetColorBasedOnHealth();
	ImageRenderer* imageRenderer;
	Player* player;
	GameObject* PowerObj;
	int Points = 1;
	void ExtraLife();
	void PowerUp();
	void TakeDamage();
	void PowerBlock();
	Vector2D brickPos;
	BrickType brickType;
	float powerUpSpeed = 2;
	int powerUpReward;
	int health;
	bool indestructible;
};

