#include "GUILevelEditorButton.h"



GUILevelEditorButton::GUILevelEditorButton(Color normalColor, Color downColor, Color hoverColor, Rect rect, void(*CallbackFunction)(void), int buttonIndex)
	: GUIButton(" ", Color(), normalColor, downColor, hoverColor, rect, 0, NULL, false), buttonIndex(buttonIndex), brickId(0)
{
}


GUILevelEditorButton::~GUILevelEditorButton()
{
}
