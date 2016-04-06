#pragma once
#include "Level.h"
#include <memory>
class BoardManager
{
public:
	BoardManager();
	~BoardManager();
	void InitializeBoard();
	void ResetBoard();
	void SetCurrentLevel(int levelId);
	void AddLevel(Level* level) { allLevels.emplace_back(level); }

	// Called when pressing start after selectin level, when restarting, when pressing nextlevel
	void OnStartLevel();

	void OnGameOver();
private:
	void LoadCurrentLevel();
	std::vector<Level*> allLevels;
	Level* curLevel;
};
