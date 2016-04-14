#include "Player.h"
#include "Time.h"
#include "PError.h"
using namespace std;


//	Constructs a custom player
Player::Player(int highscore, int level, int lifeLeft, int bricksHit, int bricksMissed, std::string name)
{
	SetHighscore(highscore);
	SetLevel(level);
	SetLifeLeft(lifeLeft);
	SetBricksHit(bricksHit);
	SetBricksMissed(bricksMissed);
	SetName(name);
	pad = false;
}

//	Set a player's individual values
void Player::SetHighscore(int highscore) {
	m_highscore += highscore;
}

void Player::SetLevel(int level)
{
	m_level = level;
}

void Player::SetLifeLeft(int lifeLeft)
{
	m_lifeLeft = lifeLeft;
	
	if (m_guiEventHandler == NULL) {
		m_guiEventHandler = GameObjectManager::GetInstance().FindGameObjectByTag(Tags::MenuObject)->GetComponent<GUIEventHandler>();
	}

	if (m_lifeLeft <= 0)
	{
		PError("m_lifeLeft <= 0");
		m_guiEventHandler->OnEndLevel();
	}
}

void Player::SetBricksHit(int bricksHit)
{
	m_bricksHit = bricksHit;
}

void Player::SetBricksMissed(int bricksMissed)
{
	m_bricksMissed = bricksMissed;
}

void Player::SetName(std::string name)
{
	m_name = name;
}

int Player::GetHighscore() const
{
	return m_highscore;
}

int Player::GetLevel() const
{
	return m_level;
}

int Player::GetLifeLeft() const
{
	return m_lifeLeft;
}

int Player::GetBricksHit() const
{
	return m_bricksHit;
}

int Player::GetBricksMissed() const
{
	return m_bricksMissed;
}

std::string Player::GetName() const
{
	return m_name;
}

//	Print a player's current score
void Player::PrintPlayer() const
{
	if (m_name == "") {
		std::cout << "Player without a name " << std::endl;
	}
	else {
		std::cout << "Player:  " << m_name << std::endl;
	}
	std::cout << "Level: " << m_level << std::endl;
	std::cout << "Life left: " << m_lifeLeft << std::endl;
	std::cout << "Bricks hit: " << m_bricksHit << std::endl;
	std::cout << "Bricks missed: " << m_bricksMissed << std::endl;
	std::cout << "Highscore: " << m_highscore << std::endl;
}

void Player::LongPaddle(bool lPaddle) {
	if (pad) {
		return;
	}
	//Change the size of the paddle
	paddle->GetTransform()->SetSize(Vector2D(300, 15));
	paddle->GetTransform()->Translate(Vector2D(paddle->GetTransform()->GetSize().X / 2, 0));
	pad = lPaddle;
}

void Player::Awake() {
	m_guiEventHandler = GameObjectManager::GetInstance().FindGameObjectByTag(Tags::MenuObject)->GetComponent<GUIEventHandler>();
	paddle = GameObjectManager::GetInstance().FindGameObjectByTag(Tags::Paddle);
}

void Player::Update() {
	//Delay for small-big paddle
	if (pad) {
		delay += Time::DeltaTime();
		if (delay > 500) {
			delay = 0;
			pad = false;
			paddle->GetTransform()->SetSize(Vector2D(150, 15));
			paddle->GetTransform()->Translate(Vector2D(paddle->GetTransform()->GetSize().X / 2, 0));
		}
	}
}