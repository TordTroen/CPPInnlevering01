#include "LevelBrick.h"
#include "GameObject.h"
#include "ImageRenderer.h"
#include "Tags.h"
#include "Transform.h"
#include "BoxCollider.h"

const float LevelBrick::BrickWidth = 50;
const float LevelBrick::BrickHeight = 30;

LevelBrick::LevelBrick(Vector2D pos, BrickType brickType, int health, bool indestructible)
	: _brickPos(pos), _brickType(brickType), _health(health), _indestructible(indestructible)
{
}

LevelBrick::~LevelBrick()
{
}

void LevelBrick::OnCollisionEnter(const Collider * other)
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
	
	Color color = Color(200, 100, 100); // TODO Change color based on brick type?
	GetGameObject()->AddComponent(new ImageRenderer("WhiteTexture.png", color));
	GetGameObject()->AddComponent(new BoxCollider());
}

void LevelBrick::TakeDamage()
{
	_health--;
	if (_health <= 0)
	{
		GetGameObject()->SetActive(false);
		// TODO Award player
	}
}
