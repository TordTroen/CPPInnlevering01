#pragma once
#include "GUIText.h"
#include "PlayerController.h"
#include "GUIToggleGroup.h"
#include "GUIEventHandler.h"
class GUILayoutMenu;

class GUIManager
	: public Component
{
public:
	//GUIManager();
	~GUIManager();
	void Init();
	void SetupMenus();
	void UpdateScoreText(int score);
	GUIToggleGroup* GetLevelSelectToggleGroup() const { return levelSelectToggleGroup; }
	void LoadLevelList();
private:
	void Awake() override;
	GUIText* scoreText;
	PlayerController* playerController;
	GUIToggleGroup* levelSelectToggleGroup;
	GUIToggleGroup* levelEditorToggleGroup;
	GameObject* menuObj;
	GUIEventHandler* eventHandler;
	int customLevelStartElementIndex;
	int customLevelCount;
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
