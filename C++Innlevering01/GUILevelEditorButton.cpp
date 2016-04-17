#include "GUILevelEditorButton.h"
#include "GameObject.h"
#include "GameManager.h"
#include "Tags.h"
#include "InputManager.h"

GUILevelEditorButton::GUILevelEditorButton(Color normalColor, Color downColor, Color hoverColor, Rect rect, int buttonIndex)
	: GUIButton(" ", Color(), normalColor, downColor, hoverColor, rect, 0, NULL, false), buttonIndex(buttonIndex), brickId(0), editorMenu(NULL)
{
	UpdateBrickColor();
}

GUILevelEditorButton::~GUILevelEditorButton()
{
}

void GUILevelEditorButton::PaintBrick()
{
	// TODO Do in Awake()
	if (editorMenu == NULL)
	{
		//editorMenu = GetGameObject()->GetComponent<LevelEditorMenu>();
		editorMenu = gameManager->FindGameObjectByTag(Tags::MenuObject)->GetComponent<LevelEditorMenu>();
	}

	// Set brick id based on the tool id
	brickId = editorMenu->GetCurrentTool();
	UpdateBrickColor();
}

void GUILevelEditorButton::OnClick()
{
	PaintBrick();
}

void GUILevelEditorButton::OnEnter()
{
	if (InputManager::GetInstance().GetMouse(1))
	{
		PaintBrick();
	}
}

void GUILevelEditorButton::UpdateBrickColor()
{
	BrickType bt = static_cast<BrickType>(brickId);
	Color color = LevelBrick::GetBrickColor(bt); // TODO Set color based on BrickID
	SetColors(color, color, color);
}
