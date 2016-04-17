#pragma once
#include "GUIText.h"
#include "GUIToggleGroup.h"
#include "GUIEventHandler.h"
#include "GUIMenu.h"
class GUILayoutMenu;
class GameManager;

class GUIManager
{
public:
	~GUIManager();
	void Init(GameManager* gameManager);
	void SetupMenus();
	void UpdateScoreText(int score);
	void UpdateEndScoreText(int score);
	void UpdateHealthText(int health);
	GUIToggleGroup* GetLevelSelectToggleGroup() const { return levelSelectToggleGroup; }
	GUIEventHandler* GetGUIEventHandler() const { return eventHandler; }
	void LoadLevelList();
	void SetInstructionsActive(bool active);
	void SetGameOverMenuActive(bool active);
	void SetWinMenuActive(bool active);
	void SetHUDMenuActive(bool active);
private:
	GUIText* scoreText;
	GUIText* endScoreText;
	GUIText* healthText;
	GUIToggleGroup* levelSelectToggleGroup;
	GUIToggleGroup* levelEditorToggleGroup;
	GameObject* menuObj;
	GUIEventHandler* eventHandler;
	int customLevelStartElementIndex;
	int customLevelCount;
	GUIMenu* instructionsMenu;
	GUIMenu* hudMenu;
	GUILayoutMenu* levelSelectMenu;
	GUILayoutMenu* endMenu;
	GUILayoutMenu* levelIntermissionMenu;
	Color buttonColorNormal;
	Color buttonColorHover;
	Color buttonColorDown;
	Color textColor;
	GameManager* gameManager;

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
