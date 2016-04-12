#include "GUILevelEditorButton.h"
#include "GameObject.h"

GUILevelEditorButton::GUILevelEditorButton(Color normalColor, Color downColor, Color hoverColor, Rect rect, void(*CallbackFunction)(void), int buttonIndex)
	: GUIButton(" ", Color(), normalColor, downColor, hoverColor, rect, 0, NULL, false), buttonIndex(buttonIndex), brickId(0)
{
	UpdateBrickColor();
}

GUILevelEditorButton::~GUILevelEditorButton()
{
}

void GUILevelEditorButton::Awake()
{
	editorMenu = GetGameObject()->GetComponent<LevelEditorMenu>();
}

void GUILevelEditorButton::OnClick()
{
	// set brick id based on the tool id
	brickId = editorMenu->GetCurrentTool();
	UpdateBrickColor();
}

void GUILevelEditorButton::UpdateBrickColor()
{
	Color color = LevelBrick::GetBrickColor(BrickType::BrickBlue, brickHealth); // TODO Set color based on BrickID
	//Color color = LevelBrick::GetBrickColor(brickType, brickHealth); // TODO Set color based on BrickID
	backgroundItem->SetColor(color);
}
