#include "BoardManager.h"

BoardManager::BoardManager()
	: curLevel(NULL)
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
	// reset paddle, ball, score, etc
}

void BoardManager::LoadLevel(Level* level)
{
	// TODO Destroy old level
	if (curLevel != NULL)
	{

	}

	// Load new level
	curLevel = level;
	level->LoadBricks();
}
