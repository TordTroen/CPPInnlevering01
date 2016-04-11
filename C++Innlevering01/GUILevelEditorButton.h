#pragma once
#include "GUIButton.h"

// Class for the buttons that represents the bricks in the level editor
class GUILevelEditorButton :
	public GUIButton
{
public:
	GUILevelEditorButton(Color normalColor, Color downColor, Color hoverColor, Rect rect, void(*OnClickFunction)(void), int buttonIndex);
	~GUILevelEditorButton();
	int GetBrickId() const { return brickId; }
private:
	int buttonIndex;
	int brickId;
};

