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
	void LoadLevel(std::shared_ptr<Level> level);
private:
	std::shared_ptr<Level> curLevel;
};
