#pragma once
#include "GUIMenu.h"
#include "GUILevelEditorButton.h"
#include "GUIToggleGroup.h"

class LevelEditorMenu
{
public:
	LevelEditorMenu(GUIMenu* levelEditorMenu, GUIMenu* previousMenu, GameObject* menuObj);
	~LevelEditorMenu();
	void Init();
	void Save();
private:
	const int columns = 14;
	const int rows = 10;
	std::string levelName;
	std::vector<GUILevelEditorButton*> buttons;
	GUIMenu* levelEditorMenu;
	GUIMenu* previousMenu;
	GUIToggleGroup* levelEditorToggleGroup;
	GameObject* menuObj;
};

