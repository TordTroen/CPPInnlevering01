#pragma once

#include "GUIButton.h"
#include "Transform.h"
#include "InputManager.h"
#include "Tags.h"
#include <iostream>
#include "Player.h"
#include <iostream>
#include "Component.h"
#include <string>

class Player : public Component
{
public:
	~Player() {}

	//	Constructs a player with no name and three lives
	Player() : Player { 0, 0, 3, 0, 0, "" } {} 

	//	Constructs a player with a name
	Player(std::string name) : Player { 0, 0, 3, 0, 0, name } {}

	//	Constructs a custom player
	Player(int highscore, int level, int lifeLeft, int bricksHit, int bricksMissed, std::string name);

	void Reset();

	//	Set a player's individual values
	void SetHighscore(int highscore);
	void SetLevel(int level);
	void SetLifeLeft(int lifeLeft);
	void SetBricksHit(int bricksHit);
	void SetBricksMissed(int bricksMissed);
	void SetName(std::string name);

	void SetBricksForCurrentLevel(int bricks);

	//	Get a player's individual values
	int GetHighscore() const;
	int GetLevel() const;
	int GetLifeLeft() const;
	int GetBricksHit() const;
	int GetBricksMissed() const;
	int GetBricksForCurrentLevel() const;
	std::string GetName() const;

	void PrintPlayer()  const;

	void Awake() override;
	void Update() override;
	void LongPaddle(bool lPaddle);

private:

	//	The player's values
	int bricks;
	int highscore;
	int level;
	int lifeLeft;
	int bricksHit;
	int bricksMissed;
	bool isAlive;
	std::string name;

	float delay;
	bool pad;

	GameObject* paddle;
	GUIEventHandler* guiEventHandler;
};