#include "GUIEventHandler.h"
#include "GameManager.h"
#include "GUIManager.h"
#include "BoardManager.h"
#include "LevelEditorMenu.h"

GUIEventHandler::GUIEventHandler()
{
}

GUIEventHandler::~GUIEventHandler()
{
}

void GUIEventHandler::OnMainMenuPlay()
{
	int levelIndex = GUIManager::GetInstance().GetLevelSelectToggleGroup()->GetCurrentToggleIndex();
	BoardManager::GetInstance().SetCurrentLevel(levelIndex);
	BoardManager::GetInstance().StartLevel();
}

void GUIEventHandler::OnMainMenuExit()
{
	GameManager::GetInstance().SetGameState(GameState::Exit);
}

void GUIEventHandler::OnEndLevel()
{
	BoardManager::GetInstance().EndGame();
	GUIManager::GetInstance().SetInstructionsActive(false);
}

void GUIEventHandler::OnGameOver()
{
	OnEndLevel();
	GUIManager::GetInstance().SetGameOverMenuActive(true);
}


void GUIEventHandler::OnWinLevel()
{
	OnEndLevel();
	GUIManager::GetInstance().SetWinMenuActive(true);
}

void GUIEventHandler::OnRestartLevel()
{
	OnEndLevel();
	OnMainMenuPlay();
}

void GUIEventHandler::OnNextLevel()
{
	BoardManager::GetInstance().SetCurrentLevelToNextLevel();
	BoardManager::GetInstance().StartLevel();
}

void GUIEventHandler::OnEditorSave()
{
	levelEditorMenu->Save();
	GUIManager::GetInstance().LoadLevelList();
}

void GUIEventHandler::OnEditorClear()
{
	levelEditorMenu->Clear();
}
