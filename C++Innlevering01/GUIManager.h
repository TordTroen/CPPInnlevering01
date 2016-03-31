#pragma once
#include "GUIText.h"

class GUIManager
{
public:
	GUIManager();
	~GUIManager();
	void SetupMenus();
	void UpdateScoreText(int score);
private:
	GUIText* _scoreText;
};

