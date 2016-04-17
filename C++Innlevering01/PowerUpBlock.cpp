#include "PowerUpBlock.h"
#include "LevelBrick.h"
#include "Vector2D.h"
#include "InputManager.h"
#include "GameManager.h"
#include "GameObject.h"
#include "Transform.h"
#include "Player.h"
#include "Time.h"
#include "Tags.h"


PowerUpBlock::PowerUpBlock(Vector2D start, float speed, PowerType pType)
	: starting(start), speedBox(speed), powerType(pType)
{
}


PowerUpBlock::~PowerUpBlock()
{
}

void PowerUpBlock::Awake()
{
	player = gameManager->FindGameObjectByTag(Tags::Paddle)->GetComponent<Player>();
}

void PowerUpBlock::Update()
{
	Vector2D velocity = Vector2D(0, 0.5);
	GetTransform()->Translate(velocity * speedBox * Time::DeltaTime(), true);
}

void PowerUpBlock::OnCollisionEnter(const Collider* const other)
{
	if (other->GetGameObject()->CompareTag(Tags::Paddle))
	{
		if (powerType == PowerType::PowerPaddle)
		{
			player->LongPaddle(true);
		}
		else if (powerType == PowerType::PowerLife) 
		{
			player->SetLifeLeft(player->GetLifeLeft() + 1);
		}
		GetGameObject()->SetActive(false);
	}
	else if (other->GetGameObject()->CompareTag(Tags::WallBottom))
	{
		GetGameObject()->SetActive(false);
		//TODO: Destroy object
	}
}