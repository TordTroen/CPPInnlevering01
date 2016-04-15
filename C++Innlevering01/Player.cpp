#include "Player.h"
#include "BoardManager.h"
#include "Time.h"
#include "PError.h"
#include "GUIManager.h"
using namespace std;


/*  Class: Player.cpp
	- Holds data about every result the user can control by playing, e.g. the number
	of bricks hit, missed, name, it's highscore etc.. */


//	Constructs a custom player
Player::Player(int highscore, int level, int lifeLeft, int bricksHit, int bricksMissed, std::string name)
{
	SetLevel(level);
	m_highscore = highscore;
	m_lifeLeft = lifeLeft;
	SetBricksHit(bricksHit);
	SetBricksMissed(bricksMissed);
	SetName(name);
	pad = false;
	m_isAlive = true;
}

void Player::Reset()
{
	SetHighscore(0);
	SetLifeLeft(3);
	SetBricksHit(0);
	SetBricksMissed(0);
	SetName("Player");
	m_isAlive = true;
}

//	Set a player's individual values
void Player::SetHighscore(int highscore) {
	m_highscore = highscore;
	GUIManager::GetInstance().UpdateScoreText(m_highscore);
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
	GUIManager::GetInstance().UpdateHealthText(GetLifeLeft());

	if (m_lifeLeft <= 0)
	{
		if (m_isAlive)
		{
			m_guiEventHandler->OnGameOver();
			m_isAlive = false;
		}
	}
	else
	{
		GUIManager::GetInstance().SetInstructionsActive(true);
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

void Player::SetBricksForCurrentLevel(int bricks)
{
	m_bricks = bricks;
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
	if (m_bricksHit == m_bricks) {
		m_guiEventHandler->OnWinLevel();
	}
	return m_bricksHit;
}

int Player::GetBricksMissed() const
{
	return m_bricksMissed;
}

int Player::GetBricksForCurrentLevel() const
{
	return m_bricks;
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
	std::cout << ": " << m_bricksHit << std::endl;
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
