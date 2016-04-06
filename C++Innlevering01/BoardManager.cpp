#include "BoardManager.h"
#include <memory>
#include "PError.h"

BoardManager::BoardManager()
{
}


BoardManager::~BoardManager()
{
}

void BoardManager::InitializeBoard()
{
	// setup walls and stuff
}

void BoardManager::ResetBoard()
{
	// TODO Reset paddle
	// TODO Reset ball
	// TODO Reset level
}

void BoardManager::SetCurrentLevel(int levelId)
{
	// TODO Destroy old level
	if (curLevel != NULL)
	{

	}

	// Set new level
	curLevel = allLevels[levelId];
	LoadCurrentLevel();
}

void BoardManager::OnStartLevel()
{
	ResetBoard();
	// TODO Activate player/ball
	LoadCurrentLevel(); // TODO load next level OR selected level from level select
}

void BoardManager::OnGameOver()
{
	// Open gameovermenu
	// set gamestate
}

void BoardManager::LoadCurrentLevel()
{
	if (curLevel != NULL)
	{
		curLevel->LoadBricks();
	}
	else
	{
		PError("Couldn't load a level, because no curLevel is assigned.");
	}
}
