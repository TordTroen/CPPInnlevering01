#pragma once
#include <string>
#include <vector>
#include "GameObject.h"

class Level
{
public:
	Level(std::string levelText);
	~Level();
	void LoadBricks();
	void DeleteBricks();
	void SetBackground();
	std::string GetLevelText() const { return levelText; }
	std::vector<int> GetLevelVectices() const { return levelVertices; }
	std::string GetLevelName() const { return levelName; }
	int GetBrickCount() const;
private:
	std::string levelName;
	int levelId;
	std::string levelText;
	std::vector<int> levelVertices;
	std::vector<GameObject*> brickObjects;
};

