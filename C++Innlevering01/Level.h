#pragma once
#include <string>
#include <vector>

class Level
{
public:
	Level(std::string levelText, float startYPosition = 100);
	~Level();
	void LoadBricks();
	void SetBackground();
	std::string GetLevelText() const { return _levelText; }
	std::vector<int> GetLevelVectices() const { return _levelVertices; }
private:
	int levelId;
	float _startYPosition;
	std::string _levelText;
	std::vector<int> _levelVertices;
};

