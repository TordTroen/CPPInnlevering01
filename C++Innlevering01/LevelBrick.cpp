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
	: _brickPos(pos), _brickType(brickType), powerUpReward(powerup), _health(health), _indestructible(indestructible)
{
}

LevelBrick::~LevelBrick()
{
}

void LevelBrick::OnCollisionEnter(const Collider* const other)
{
	if (!_indestructible && other->GetGameObject()->CompareTag(Tags::Ball))
	{
		TakeDamage();
	}
}

void LevelBrick::Awake()
{
	GetTransform()->SetPosition(_brickPos);
	GetTransform()->SetSize(Vector2D(BrickWidth, BrickHeight));
	
	Color color = GetColorBasedOnHealth();
	
	_imageRenderer = dynamic_cast<ImageRenderer*>(GetGameObject()->AddComponent(new ImageRenderer("WhiteTexture.png", color)));
	GetGameObject()->AddComponent(new BoxCollider());
}

Color LevelBrick::GetColorBasedOnHealth()
{
	switch (_health)
	{
	case 1:
		if (_brickType == BrickType::BrickNormal)
		{
			return Color(255, 255, 40);
		}
		else if (_brickType == BrickType::BrickGreen)
		{
			return Color(40, 255, 40);
		}
		else if (_brickType == BrickType::BrickBlue)
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
	_health--;
	if (_health <= 0)
	{
		GetGameObject()->SetActive(false);
		// TODO Award player
		player.SetHighscore(1);
		GUIManager::GetInstance().UpdateScoreText(player.GetHighscore());
		PowerUp();
	}
	_imageRenderer->GetImageDrawable()->SetColor(GetColorBasedOnHealth());
}