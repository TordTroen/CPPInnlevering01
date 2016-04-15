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
	GameManager::GetInstance().SetGameState(GameState::InGame);
	int levelIndex = GUIManager::GetInstance().GetLevelSelectToggleGroup()->GetCurrentToggleIndex();
	BoardManager::GetInstance().SetCurrentLevel(levelIndex); // TODO Increment level index if we 
	BoardManager::GetInstance().OnStartLevel();
}

void GUIEventHandler::OnMainMenuExit()
{
	GameManager::GetInstance().SetGameState(GameState::Exit);
}

void GUIEventHandler::OnEndLevel()
{
	std::cout << "TODO: show end screen" << std::endl;
	GameManager::GetInstance().SetGameState(GameState::MainMenu);
	BoardManager::GetInstance().OnGameOver();
}

void GUIEventHandler::OnWinLevel()
{
	std::cout << "TODO: show win screen" << std::endl;
}

void GUIEventHandler::OnRestartLevel()
{
	OnMainMenuPlay();
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
