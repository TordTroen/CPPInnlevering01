#pragma once
#include "GUIText.h"
#include "PlayerController.h"
#include "GUIToggleGroup.h"
#include "GUIEventHandler.h"
#include "GUIMenu.h"
class GUILayoutMenu;

class GUIManager
{
public:
	~GUIManager();
	void Init();
	void SetupMenus();
	void UpdateScoreText(int score);
	void UpdateHealthText(int health);
	GUIToggleGroup* GetLevelSelectToggleGroup() const { return levelSelectToggleGroup; }
	void LoadLevelList();
	void SetInstructionsActive(bool active);
private:
	GUIText* scoreText;
	GUIText* healthText;
	GUIToggleGroup* levelSelectToggleGroup;
	GUIToggleGroup* levelEditorToggleGroup;
	GameObject* menuObj;
	GUIEventHandler* eventHandler;
	int customLevelStartElementIndex;
	int customLevelCount;
	GUIMenu* instructionsMenu;
	GUILayoutMenu* levelSelectMenu;
	Color buttonColorNormal;
	Color buttonColorHover;
	Color buttonColorDown;

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
