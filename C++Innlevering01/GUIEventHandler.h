#pragma once
#include "Component.h"
class LevelEditorMenu;

class GUIEventHandler :
	public Component
{
public:
	GUIEventHandler();
	~GUIEventHandler();
	void OnMainMenuPlay();
	void OnMainMenuExit();
	void OnEndLevel();
	void OnWinLevel();
	void OnRestartLevel();
	void OnEditorSave();
	void OnEditorClear();
	void SetLevelEditorMenuReference(LevelEditorMenu* levelEditorMenu) { this->levelEditorMenu = levelEditorMenu; }
private:
	LevelEditorMenu* levelEditorMenu;
};

