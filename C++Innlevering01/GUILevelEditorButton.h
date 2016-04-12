#pragma once
#include "GUIButton.h"
#include "LevelBrick.h"
#include "LevelEditorMenu.h"

// Class for the buttons that represents the bricks in the level editor
class GUILevelEditorButton :
	public GUIButton
{
public:
	GUILevelEditorButton(Color normalColor, Color downColor, Color hoverColor, Rect rect, void(*OnClickFunction)(void), int buttonIndex);
	~GUILevelEditorButton();
	int GetBrickId() const { return brickId; }
private:
	void Awake() override;
	void OnClick() override;
	int buttonIndex;
	int brickId;
	//BrickType brickType; // TODO Wrap these in a brick struct or something
	int brickHealth;
	void UpdateBrickColor();
	LevelEditorMenu* editorMenu;
};

