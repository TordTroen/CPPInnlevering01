#pragma once
#include "Level.h"
#include <memory>
#include "PaddleMovement.h"
#include "BallMovement.h"

class BoardManager
{
public:
	~BoardManager();

	/* Initializes the board. Import the leveldata and sets up the walls surrounding the screen. */
	void InitializeBoard();
	void ResetBoard();
	void ClearBoard();

	Level * GetCurrentLevel() const;

	/* Sets the curLevel based on the index given. */
	void SetCurrentLevel(int levelId);

	void SetCurrentLevelToNextLevel();

	// Called when pressing start after selectin level, when restarting, when pressing nextlevel
	void StartLevel();

	void EndGame();

	std::vector<std::string> GetLevelNames() const;

	void ImportAllLevels();

	int GetStandardLevelCount() const { return standardLevelCount; }

	void SaveLevel(int index, std::string levelText);
private:
	/* Loads the level stored in curLevel. */
	void LoadCurrentLevel();

	/* Import level data from a file. */
	void ImportLevelData(std::string filename);

	/* Adds a level to the allLevels vector. */
	void AddLevel(Level* level);

	std::vector<Level*> allLevels;
	int standardLevelCount;
	Player* player;
	Level* curLevel;
	int curLevelId;
	PaddleMovement* paddleMovement;
	BallMovement* ballMovement;

// Singleton stuff
public:
static BoardManager& GetInstance()
{
	static BoardManager instance;
	return instance;
}
private:
	BoardManager() {};
	BoardManager(BoardManager const&);
void operator=(BoardManager const&);
};
