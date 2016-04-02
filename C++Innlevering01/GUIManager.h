#pragma once
#include "GUIText.h"
#include "PlayerController.h"

class GUIManager
	: public Component
{
public:
	GUIManager();
	~GUIManager();
	void SetupMenus();
	void UpdateScoreText(int score);
private:
	//void OnPlay();
	void Awake() override;
	GUIText* _scoreText;
	PlayerController* _playerController;
};

