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
	void Test();
	void Awake() override;
	std::shared_ptr<GUIText> _scoreText;
	std::shared_ptr<PlayerController> _playerController;
};

