#pragma once
#include "GUIText.h"
#include "PlayerController.h"
#include "GUIToggleGroup.h"

class GUIManager
	: public Component
{
public:
	//GUIManager();
	~GUIManager();
	void SetupMenus();
	void UpdateScoreText(int score);
	GUIToggleGroup* GetLevelSelectToggleGroup() const { return levelSelectToggleGroup; }
private:
	void Test();
	void Awake() override;
	GUIText* scoreText;
	PlayerController* playerController;
	GUIToggleGroup* levelSelectToggleGroup;
	GUIToggleGroup* levelEditorToggleGroup;
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

