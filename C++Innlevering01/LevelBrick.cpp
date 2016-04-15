#include "LevelBrick.h"
#include "GameObject.h"
#include "ImageRenderer.h"
#include "Tags.h"
#include "Time.h"
#include "Transform.h"
#include "BoxCollider.h"
#include "ImageRenderer.h"
#include "GUIManager.h"
#include "Player.h"
#include "GameObjectManager.h"
#include "GameManager.h"
#include "PowerUpBlock.h"
#include <chrono>
#include <thread>

const float LevelBrick::BrickWidth = 50;
const float LevelBrick::BrickHeight = 30;

LevelBrick::LevelBrick(Vector2D pos, BrickType brickType, int powerup, int health, bool indestructible)
	: brickPos(pos), brickType(brickType), powerUpReward(powerup), health(health), indestructible(indestructible)
{
	if (brickType == BrickType::Brick2Hits || brickType == BrickType::Brick3Hits)
	{
		this->health = static_cast<int>(this->brickType);
	}
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
}

void LevelBrick::OnCollisionEnter(const Collider* const other)
{
	if (!indestructible && other->GetGameObject()->CompareTag(Tags::Ball))
	{
		TakeDamage();
		player->ReduceBrickCount();
	}
}

void LevelBrick::Awake()
{
	PowerLifeObj = GameObjectManager::GetInstance().CreateObject(Tags::PowerUp);
	PowerPaddleObj = GameObjectManager::GetInstance().CreateObject(Tags::PowerUp);
	player = GameObjectManager::GetInstance().FindGameObjectByTag(Tags::Paddle)->GetComponent<Player>();
	GetTransform()->SetPosition(brickPos);
	GetTransform()->SetSize(Vector2D(BrickWidth, BrickHeight));
	PowerPaddleBlock();
	PowerPaddleObj->SetActive(false);
	PowerLifeBlock();
	PowerLifeObj->SetActive(false);
	Color color = GetBrickColor(brickType);
	
	imageRenderer = dynamic_cast<ImageRenderer*>(GetGameObject()->AddComponent(new ImageRenderer("WhiteTexture.png", color)));
	GetGameObject()->AddComponent(new BoxCollider());
}

void LevelBrick::PowerPaddleBlock()
{
	PowerPaddleObj->AddComponent(new ImageRenderer("PowerUpLongPaddle.png"));
	PowerPaddleObj->AddComponent(new BoxCollider(false));
	PowerPaddleObj->GetTransform()->SetPosition(GetTransform()->GetPosition());
	PowerPaddleObj->GetTransform()->SetSize(Vector2D(PowerUpWidth, PowerUpHeight));
}

void LevelBrick::PowerLifeBlock()
{
	PowerLifeObj->AddComponent(new ImageRenderer("PowerUpExtraLife.png"));
	PowerLifeObj->AddComponent(new BoxCollider(false));
	PowerLifeObj->GetTransform()->SetPosition(GetTransform()->GetPosition());
	PowerLifeObj->GetTransform()->SetSize(Vector2D(PowerUpWidth, PowerUpHeight));
}

void LevelBrick::PowerUp() {
	int chance = (int)(rand() % 10) + 1;
	std::cout << chance << std::endl;

	if (chance == 1) {
		int chance2 = (int)(rand() % 2) + 1;
		if (chance2 == 1) {
			PowerPaddleObj->AddComponent(new PowerUpBlock(Vector2D(0, 1), powerUpSpeed, PowerType::PowerPaddle));
			PowerPaddleObj->SetActive(true);
		}
		else if (chance2 == 2){
			PowerLifeObj->AddComponent(new PowerUpBlock(Vector2D(0, 1), powerUpSpeed, PowerType::PowerLife));
			PowerLifeObj->SetActive(true);
		}
	}
}

void LevelBrick::TakeDamage()
{
	health--;
	if (brickType == BrickType::Brick2Hits || brickType == BrickType::Brick3Hits)
	{
		player->ReduceBrickCount();
		brickType = static_cast<BrickType>(health);
	}
	
	if (health <= 0)
	{
		GetGameObject()->SetActive(false);
		player->SetHighscore(Points);
		GUIManager::GetInstance().UpdateScoreText(player->GetHighscore());
		PowerUp();
		return;
	}
	imageRenderer->GetImageDrawable()->SetColor(GetBrickColor(brickType));
}
