#pragma once
#include <string>
#include <vector>
#include "Player.h"
#include "GameObject.h"

class Level
{
public:
	Level(std::string levelText);
	~Level();
	void LoadBricks();
	void DeleteBricks();
	std::string GetLevelText() const { return levelText; }
	std::string GetLevelName() const { return levelName; }
	std::string GetLevelString() const { return levelName + "|" + levelText; }
	void SetLevelText(std::string levelText);
private:
	Player* player;
	int levelId;
	std::string levelName;
	std::string levelText;
	std::vector<GameObject*> brickObjects;
};

