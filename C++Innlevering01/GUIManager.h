#pragma once
#include "GUIText.h"
#include "PlayerController.h"

class GUIManager
	: public Component
{
public:
	//GUIManager();
	~GUIManager();
	void SetupMenus();
	void UpdateScoreText(int score);
private:
	void Test();
	void Awake() override;
	GUIText* _scoreText;
	PlayerController* _playerController;

	// Singleton stuff
public:
	static GUIManager& GetInstance()
	{
		static GUIManager instance;
		return instance;
	}
private:
	GUIManager() {};
	GUIManager(GUIManager const&);
	void operator=(GUIManager const&);
};

