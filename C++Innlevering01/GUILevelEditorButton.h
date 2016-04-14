#pragma once
#include "GUIButton.h"
#include "LevelBrick.h"
#include "LevelEditorMenu.h"

// Class for the buttons that represents the bricks in the level editor
class GUILevelEditorButton :
	public GUIButton
{
public:
	GUILevelEditorButton(Color normalColor, Color downColor, Color hoverColor, Rect rect, int buttonIndex);
	~GUILevelEditorButton();
	int GetBrickId() const { return brickId; }
	int GetButtonIndex() const { return buttonIndex; }
private:
	void PaintBrick();
	void Awake() override;
	void OnClick() override;
	void OnEnter() override;
	int buttonIndex;
	int brickId;
	void UpdateBrickColor();
	LevelEditorMenu* editorMenu;
};
