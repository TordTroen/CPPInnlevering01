#include "LevelBrick.h"
#include "GameObject.h"
#include "ImageRenderer.h"
#include "Tags.h"
#include "Transform.h"
#include "BoxCollider.h"
#include "ImageRenderer.h"

const float LevelBrick::BrickWidth = 50;
const float LevelBrick::BrickHeight = 30;

LevelBrick::LevelBrick(Vector2D pos, BrickType brickType, int score, int health, bool indestructible)
	: _brickPos(pos), _brickType(brickType), _scoreReward(score), _health(health), _indestructible(indestructible)
{
}

LevelBrick::~LevelBrick()
{
}

void LevelBrick::OnCollisionEnter(const std::shared_ptr<Collider> other)
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
	
	_imageRenderer = dynamic_pointer_cast<ImageRenderer>(GetGameObject()->AddComponent(std::shared_ptr<ImageRenderer>(new ImageRenderer("WhiteTexture.png", color))));
	GetGameObject()->AddComponent(std::shared_ptr<BoxCollider>(new BoxCollider()));
}

Color LevelBrick::GetColorBasedOnHealth()
{
	switch (_health)
	{
	case 1:
		if (_brickType == BrickNormal)
		{
			return Color(255, 255, 40);
		}
		else if (_brickType == BrickGreen)
		{
			return Color(40, 255, 40);
		}
		else if (_brickType == BrickBlue)
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

void LevelBrick::TakeDamage()
{
	_health--;
	if (_health <= 0)
	{
		GetGameObject()->SetActive(false);
		_scoreReward++;
		cout << _scoreReward++ << endl;
		// TODO Award player
	}
	_imageRenderer->GetImageDrawable()->SetColor(GetColorBasedOnHealth());
}