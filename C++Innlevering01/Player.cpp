#include "Player.h"
#include <iostream>

//	Constructs a custom player
Player::Player(int highscore, int level, int lifeLeft, int bricksHit, int bricksMissed, std::string name)
{
	SetHighscore(highscore);
	SetLevel(level);
	SetLifeLeft(lifeLeft);
	SetBricksHit(bricksHit);
	SetBricksMissed(bricksMissed);
	SetName(name);
}

//	Set a player's individual values
void Player::SetHighscore(int highscore) {
	_highscore = highscore;
}

void Player::SetLevel(int level)
{
	_level = level;
}

void Player::SetLifeLeft(int lifeLeft)
{
	_lifeLeft = lifeLeft;
}

void Player::SetBricksHit(int bricksHit)
{
	_bricksHit = bricksHit;
}

void Player::SetBricksMissed(int bricksMissed)
{
	_bricksMissed = bricksMissed;
}

void Player::SetName(std::string name)
{
	_name = name;
}

int Player::GetHighscore() {
	return _highscore;
}

int Player::GetLevel()
{
	return _level;
}

int Player::GetLifeLeft()
{
	return _lifeLeft;
}

int Player::GetBricksHit()
{
	return _bricksHit;
}

int Player::GetBricksMissed()
{
	return _bricksMissed;
}

std::string Player::GetName()
{
	return _name;
}

//	Print a player's current score
void Player::PrintPlayer()
{
	if (_name == "") {
		std::cout << "Player without a name " << std::endl;
	}
	else {
		std::cout << "Player:  " << _name << std::endl;
	}
	std::cout << "Level: " << _level << std::endl;
	std::cout << "Life left: " << _level << std::endl;
	std::cout << "Bricks hit: " << _level << std::endl;
	std::cout << "Bricks missed: " << _level << std::endl;
	std::cout << "Highscore: " << _level << std::endl;
}
