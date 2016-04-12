#include "LevelBrick.h"
#include "GameObject.h"
#include "ImageRenderer.h"
#include "Tags.h"
#include "Transform.h"
#include "BoxCollider.h"
#include "ImageRenderer.h"
#include "GUIManager.h"
#include "Player.h"

const float LevelBrick::BrickWidth = 50;
const float LevelBrick::BrickHeight = 30;
Player player;

LevelBrick::LevelBrick(Vector2D pos, BrickType brickType, int score, int health, bool indestructible)
	: brickPos(pos), brickType(brickType), scoreReward(score), health(health), indestructible(indestructible)
{
}

LevelBrick::~LevelBrick()
{
}

Color LevelBrick::GetBrickColor(BrickType brickType, int health)
{
	if (brickType == BrickType::BrickIndestructible)
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
	}
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
	
	Color color = GetColorBasedOnHealth();
	
	imageRenderer = dynamic_cast<ImageRenderer*>(GetGameObject()->AddComponent(new ImageRenderer("WhiteTexture.png", color)));
	GetGameObject()->AddComponent(new BoxCollider());
}

Color LevelBrick::GetColorBasedOnHealth()
{
	return LevelBrick::GetBrickColor(brickType, health);
	/*if (indestructible)
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

void LevelBrick::TakeDamage()
{
	health--;
	if (health <= 0)
	{
		GetGameObject()->SetActive(false);
		// TODO Award player
		player.SetHighscore(1);
		GUIManager::GetInstance().UpdateScoreText(player.GetHighscore());
	}
	imageRenderer->GetImageDrawable()->SetColor(GetColorBasedOnHealth());
}