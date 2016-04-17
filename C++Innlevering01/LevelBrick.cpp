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
	scoreReward = this->health;
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
	}
}

void LevelBrick::Awake()
{
	powerLifeObj = gameManager->CreateObject(Tags::PowerUp);
	powerPaddleObj = gameManager->CreateObject(Tags::PowerUp);
	player = gameManager->FindGameObjectByTag(Tags::Paddle)->GetComponent<Player>();
	GetTransform()->SetPosition(brickPos);
	GetTransform()->SetSize(Vector2D(BrickWidth, BrickHeight));
	PowerPaddleBlock();
	powerPaddleObj->SetActive(false);
	PowerLifeBlock();
	powerLifeObj->SetActive(false);
	Color color = GetBrickColor(brickType);
	
	imageRenderer = new ImageRenderer("WhiteTexture.png", color);
	GetGameObject()->AddComponent(imageRenderer);
	GetGameObject()->AddComponent(new BoxCollider());
}

void LevelBrick::PowerPaddleBlock()
{
	powerPaddleObj->AddComponent(new ImageRenderer("PowerUpLongPaddle.png"));
	powerPaddleObj->AddComponent(new BoxCollider(false));
	powerPaddleObj->GetTransform()->SetPosition(GetTransform()->GetPosition());
	powerPaddleObj->GetTransform()->SetSize(Vector2D(PowerUpWidth, PowerUpHeight));
}

void LevelBrick::PowerLifeBlock()
{
	powerLifeObj->AddComponent(new ImageRenderer("PowerUpExtraLife.png"));
	powerLifeObj->AddComponent(new BoxCollider(false));
	powerLifeObj->GetTransform()->SetPosition(GetTransform()->GetPosition());
	powerLifeObj->GetTransform()->SetSize(Vector2D(PowerUpWidth, PowerUpHeight));
}

void LevelBrick::PowerUp() {
	int chance = (int)(rand() % 10) + 1;
	if (chance == 1) {
		int chance2 = (int)(rand() % 2) + 1;
		if (chance2 == 1) {
			powerPaddleObj->AddComponent(new PowerUpBlock(Vector2D(0, 1), powerUpSpeed, PowerType::PowerPaddle));
			powerPaddleObj->SetActive(true);
		}
		else if (chance2 == 2){
			powerLifeObj->AddComponent(new PowerUpBlock(Vector2D(0, 1), powerUpSpeed, PowerType::PowerLife));
			powerLifeObj->SetActive(true);
		}
	}
}

void LevelBrick::TakeDamage()
{
	health--;
	if (brickType == BrickType::Brick2Hits || brickType == BrickType::Brick3Hits)
	{
		brickType = static_cast<BrickType>(health);
	}
	
	if (health <= 0)
	{
		GetGameObject()->SetActive(false);
		player->SetHighscore(player->GetHighscore() + scoreReward);
		GUIManager::GetInstance().UpdateScoreText(player->GetHighscore());
		PowerUp();
		return;
	}
	imageRenderer->GetImageDrawable()->SetColor(GetBrickColor(brickType));
}

int LevelBrick::GetHealth() const {
	return health;
}
