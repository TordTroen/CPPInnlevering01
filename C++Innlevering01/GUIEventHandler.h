#pragma once
#include "Component.h"
class LevelEditorMenu;
class BoardManager;

class GUIEventHandler :
	public Component
{
public:
	GUIEventHandler();
	~GUIEventHandler();
	void OnMainMenuPlay();
	void OnMainMenuExit();
	void OnEndLevel();
	void OnGameOver();
	void OnWinLevel();
	void OnRestartLevel();
	void OnNextLevel();
	void OnEditorSave();
	void OnEditorClear();
	void Init(LevelEditorMenu* levelEditorMenu, GameManager* gameManager, BoardManager* boardManager);
private:
	LevelEditorMenu* levelEditorMenu;
	GameManager* gameManager;
	BoardManager* boardManager;
};

