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
	boardManager->SetCurrentLevel(levelIndex);
	boardManager->StartLevel();
}

void GUIEventHandler::OnMainMenuExit()
{
	gameManager->SetGameState(GameState::Exit);
}

void GUIEventHandler::OnEndLevel()
{
	boardManager->EndGame();
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
	boardManager->SetCurrentLevelToNextLevel();
	boardManager->StartLevel();
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

void GUIEventHandler::Init(LevelEditorMenu * levelEditorMenu, GameManager * gameManager, BoardManager* boardManager)
{
	this->levelEditorMenu = levelEditorMenu;
	this->gameManager = gameManager;
	this->boardManager = boardManager;
}
