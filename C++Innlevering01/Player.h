#pragma once

#include <string>
class Player
{
public:
	~Player() {}

	//	Constructs a player with no name and three lives
	Player() : Player { 0, 0, 3, 0, 0, "" } {} 

	//	Constructs a player with a name
	Player(std::string name) : Player { 0, 0, 3, 0, 0, name } {}

	//	Constructs a custom player
	Player(int highscore, int level, int lifeLeft, int bricksHit, int bricksMissed, std::string name);

	//	Set a player's individual values
	void Player::SetHighscore(int highscore);
	void Player::SetLevel(int level);
	void Player::SetLifeLeft(int lifeLeft);
	void Player::SetBricksHit(int bricksHit);
	void Player::SetBricksMissed(int bricksMissed);
	void Player::SetName(std::string name);

	//	Get a player's individual values
	int Player::GetHighscore() const;
	int Player::GetLevel() const;
	int Player::GetLifeLeft() const;
	int Player::GetBricksHit() const;
	int Player::GetBricksMissed() const;
	std::string Player::GetName() const;

	void Player::PrintPlayer();

private:

	//	The player's values
	int _highscore;
	int _level;
	int _lifeLeft;
	int _bricksHit;
	int _bricksMissed;
	std::string _name;
};