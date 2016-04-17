#include "Player.h"
#include "BoardManager.h"
#include "Time.h"
#include "PError.h"
#include "GUIManager.h"
#include "GameManager.h"
using namespace std;


/*  Class: Player.cpp
	- Holds data about every result the user can control by playing, e.g. the number
	of bricks hit, missed, name, it's highscore etc.. */


//	Constructs a custom player
Player::Player(int highscore, int level, int lifeLeft, int bricksHit, int bricksMissed, std::string name)
{
	SetLevel(level);
	this->highscore = highscore;
	this->lifeLeft = lifeLeft;
	SetBricksHit(bricksHit);
	SetBricksMissed(bricksMissed);
	SetName(name);
	pad = false;
	isAlive = true;
}

void Player::Reset()
{
	SetHighscore(0);
	SetLifeLeft(3);
	SetBricksHit(0);
	SetBricksMissed(0);
	SetName("Player");
	isAlive = true;
}

//	Set a player's individual values
void Player::SetHighscore(int highscore) {
	this->highscore = highscore;
	GUIManager::GetInstance().UpdateScoreText(this->highscore);
}

void Player::SetLevel(int level)
{
	this->level = level;
}

void Player::SetLifeLeft(int lifeLeft)
{
	bool loosingLife = (lifeLeft < this->lifeLeft);

	this->lifeLeft = lifeLeft;

	if (this->guiEventHandler == NULL) {
		this->guiEventHandler = gameManager->FindGameObjectByTag(Tags::MenuObject)->GetComponent<GUIEventHandler>();
	}
	GUIManager::GetInstance().UpdateHealthText(GetLifeLeft());

	if (this->lifeLeft <= 0)
	{
		if (this->isAlive)
		{
			this->guiEventHandler->OnGameOver();
			this->isAlive = false;
		}
	}
	else if (loosingLife)
	{
		GUIManager::GetInstance().SetInstructionsActive(true);
	}
}

void Player::SetBricksHit(int bricksHit)
{
	this->bricksHit = bricksHit;
}

void Player::SetBricksMissed(int bricksMissed)
{
	this->bricksMissed = bricksMissed;
}

void Player::SetName(std::string name)
{
	this->name = name;
}

void Player::SetBricksForCurrentLevel(int bricks)
{
	this->bricks = bricks;
}

int Player::GetHighscore() const
{
	return highscore;
}

int Player::GetLevel() const
{
	return level;
}

int Player::GetLifeLeft() const
{
	return lifeLeft;
}

int Player::GetBricksHit() const
{
	if (bricksHit == bricks) {
		guiEventHandler->OnWinLevel();
	}
	return bricksHit;
}

int Player::GetBricksMissed() const
{
	return bricksMissed;
}

int Player::GetBricksForCurrentLevel() const
{
	return bricks;
}


std::string Player::GetName() const
{
	return name;
}

//	Print a player's current score
void Player::PrintPlayer() const
{
	if (name == "") {
		std::cout << "Player without a name " << std::endl;
	}

	else {
		std::cout << "Player:  " << name << std::endl;
	}
	std::cout << "Level: " << level << std::endl;
	std::cout << "Life left: " << lifeLeft << std::endl;
	std::cout << ": " << bricksHit << std::endl;
	std::cout << "Bricks missed: " << bricksMissed << std::endl;
	std::cout << "Highscore: " << highscore << std::endl;
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
	guiEventHandler = gameManager->FindGameObjectByTag(Tags::MenuObject)->GetComponent<GUIEventHandler>();
	paddle = gameManager->FindGameObjectByTag(Tags::Paddle);
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
