#include "LevelBrick.h"
#include "GameObject.h"
#include "ImageRenderer.h"
#include "Tags.h"
#include "Transform.h"
#include "BoxCollider.h"
#include "ImageRenderer.h"
#include "GUIManager.h"
#include "Player.h"
#include "GameObjectManager.h"

const float LevelBrick::BrickWidth = 50;
const float LevelBrick::BrickHeight = 30;
const float LevelBrick::PowerUpWidth = 20;
const float LevelBrick::PowerUpHeight = 20;
Player player;

LevelBrick::LevelBrick(Vector2D pos, BrickType brickType, int powerup, int health, bool indestructible)
	: brickPos(pos), brickType(brickType), powerUpReward(powerup), health(health), indestructible(indestructible)
{
}

LevelBrick::~LevelBrick()
{
}

Color LevelBrick::GetBrickColor(BrickType brickType)
{
	switch (brickType)
	{
	case BrickType::BrickEmpty:
		return Color(240, 240, 240);
	case BrickType::BrickNormal:
		return Color(255, 255, 40);
	case BrickType::Brick2Hits:
		return Color(255, 150, 150);
	case BrickType::Brick3Hits:
		return Color(255, 100, 100);
	case BrickType::BrickGreen:
		return Color(40, 255, 40);
	case BrickType::BrickBlue:
		return Color(40, 40, 255);
	case BrickType::BrickPowerup:
		return Color(255, 0, 255);
	case BrickType::BrickIndestructible:
		return Color(10, 10, 10);
	default:
		return Color(127, 127, 127);
	}
	/*if (brickType == BrickType::BrickIndestructible)
	{
		return Color(10, 10, 10);
	}
	switch (health)
	{
	case 1:
		if (brickType == BrickType::BrickNormal)
		{
			return Color(255, 255, 40);
		}
		else if (brickType == BrickType::BrickGreen)
		{
			return Color(40, 255, 40);
		}
		else if (brickType == BrickType::BrickBlue)
		{
			return Color(40, 40, 255);
		}
	case 2:
		return Color(255, 150, 150);
	case 3:
		return Color(255, 100, 100);
	default:
		return Color(255, 255, 255);
	}*/
}

void LevelBrick::OnCollisionEnter(const Collider* const other)
{
	if (!indestructible && other->GetGameObject()->CompareTag(Tags::Ball))
	{
		TakeDamage();
	}
}

void LevelBrick::Awake()
{
	GetTransform()->SetPosition(brickPos);
	GetTransform()->SetSize(Vector2D(BrickWidth, BrickHeight));
	
	Color color = GetBrickColor(brickType);
	
	imageRenderer = dynamic_cast<ImageRenderer*>(GetGameObject()->AddComponent(new ImageRenderer("WhiteTexture.png", color)));
	GetGameObject()->AddComponent(new BoxCollider());
}

//Color LevelBrick::GetColorBasedOnHealth()
//{
//	return GetBrickColor(_brickType);
//	//switch (_health)
//	//{
//	//case 1:
//	//	if (_brickType == BrickType::BrickNormal)
//	//	{
//	//		return Color(255, 255, 40);
//	//	}
//	//	else if (_brickType == BrickType::BrickGreen)
//	//	{
//	//		return Color(40, 255, 40);
//	//	}
//	//	else if (_brickType == BrickType::BrickBlue)
//	//	{
//	//		return Color(40, 40, 255);
//	//	}
//	//case 2:
//	//	return Color(255, 150, 150);
//	//case 3:
//	//	return Color(255, 100, 100);
//	//default:
//	//	return Color(255, 255, 255);
//	//}
//}

void LevelBrick::PowerUp() {
	int chance = (int)(rand() % 4) + 1;
	std::cout << chance << std::endl;

	if (chance == 1) {
		std::cout << "You got a powerup!" << std::endl;
		//Spawne en powerup blokk
	}
}

void LevelBrick::TakeDamage()
{
	health--;
	brickType = static_cast<BrickType>(health);
	if (health <= 0)
	{
		GetGameObject()->SetActive(false);
		// TODO Award player
		player.SetHighscore(1);
		GUIManager::GetInstance().UpdateScoreText(player.GetHighscore());
		PowerUp();
		return;
	}
	imageRenderer->GetImageDrawable()->SetColor(GetBrickColor(brickType));
}