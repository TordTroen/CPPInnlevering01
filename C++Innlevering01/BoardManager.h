#pragma once
#include "Level.h"

class BoardManager
{
public:
	BoardManager();
	~BoardManager();
	void InitializeBoard();
	void ResetBoard();
	void LoadLevel(Level* level);
private:
	Level* curLevel;
};
