#pragma once
#include <vector>
#include <string>
#include "GUIMenu.h"
#include "Component.h"
#include "GUIToggleGroup.h"
#include "GUILayoutMenu.h"
#include "GUITextField.h"
class GUILevelEditorButton;

class LevelEditorMenu
	: public Component
{
public:
	LevelEditorMenu(GUIMenu* levelEditorMenu, GUIMenu* previousMenu, GUILayoutMenu* levelSaveMenu);
	~LevelEditorMenu();
	void Save();
	void Clear();
	int GetCurrentTool() const;
private:
	void Awake() override;
	void Init();
	const int columns = 14;
	const int rows = 10;
	std::string levelName;
	std::vector<GUILevelEditorButton*> buttons;
	GUIMenu* levelEditorMenu;
	GUIMenu* previousMenu;
	GUILayoutMenu* levelSaveMenu;
	GUIToggleGroup* levelEditorToggleGroup;
	GUIToggleGroup* levelSaveToggleGroup;
	GUITextField* textField;
};

