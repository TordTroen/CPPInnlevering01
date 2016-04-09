#include "GUIManager.h"
#include <sstream>
#include <memory>
#include "GUIMenu.h"
#include "GUILayoutMenu.h"
#include "GameObjectManager.h"
#include "GUIText.h"
#include "GUIButton.h"
#include "GameManager.h"
#include "BoardManager.h"
#include "Tags.h"
#include "GUIToggleGroup.h"
#include "GUIToggle.h"

void OnExit()
{
	GameManager::GetInstance().SetGameState(GameState::Exit);
}

void OnPlay()
{
	GameManager::GetInstance().SetGameState(GameState::InGame);
	BoardManager::GetInstance().OnStartLevel();
}

void OnEndGame()
{
	GameManager::GetInstance().SetGameState(GameState::MainMenu);
	BoardManager::GetInstance().OnGameOver();
}

void OnRestart()
{
	OnPlay();
}

GUIManager::~GUIManager()
{
}

void GUIManager::SetupMenus()
{
	GameObject* menuObj = GameObjectManager::GetInstance().CreateObject();
	//GameObject* hudMenuObj = GameObjectManager::GetInstance().CreateObject();
	//GameObject* endMenuObj = GameObjectManager::GetInstance().CreateObject();
	// TODO Find a better way to do these ugly lines
	int startY = 100, spacing = 26;
	GUILayoutMenu* mainMenu = dynamic_cast<GUILayoutMenu*>(menuObj->AddComponent(new GUILayoutMenu(startY, spacing)));
	GUILayoutMenu* levelSelectMenu = dynamic_cast<GUILayoutMenu*>(menuObj->AddComponent(new GUILayoutMenu(startY, spacing, false)));
	GUILayoutMenu* levelEditorMenu = dynamic_cast<GUILayoutMenu*>(menuObj->AddComponent(new GUILayoutMenu(startY, spacing, false)));
	GUIMenu* hudMenu = dynamic_cast<GUIMenu*>(menuObj->AddComponent(new GUIMenu(false)));
	GUILayoutMenu* endMenu = dynamic_cast<GUILayoutMenu*>(menuObj->AddComponent(new GUILayoutMenu(startY, spacing, false)));
	GUILayoutMenu* levelIntermissionMenu = dynamic_cast<GUILayoutMenu*>(menuObj->AddComponent(new GUILayoutMenu(startY, spacing, false)));

	mainMenu->AddElements({
		new GUIText("Breakout", Color(200, 255, 255), Rect(10, 10, 0, 0)),
		new GUIButton("Play", Color(200, 255, 255), Color(0, 0, 0), Color(25, 25, 25), Color(50, 50, 50), Rect(10, 100, 0, 0), 8, mainMenu, levelSelectMenu),
		new GUIButton("Level editor", Color(200, 255, 255), Color(0, 0, 0), Color(25, 25, 25), Color(50, 50, 50), Rect(10, 100, 0, 0), 8, mainMenu, levelEditorMenu),
		new GUIButton("Exit", Color(200, 255, 255), Color(0, 0, 0), Color(25, 25, 25), Color(50, 50, 50), Rect(10, 150, 0, 0), 8, OnExit)
	});
	GUIToggleGroup* tGroup = dynamic_cast<GUIToggleGroup*>(menuObj->AddComponent(new GUIToggleGroup()));
	//mainMenu->AddElement(new GUIToggle("Item1", Color(200, 255, 255), Color(0, 0, 0), Color(25, 25, 25), Color(50, 50, 50), Color(10, 200, 10), Rect(10, 100, 0, 0), 8, tGroup));
	//mainMenu->AddElement(new GUIToggle("Item2", Color(200, 255, 255), Color(0, 0, 0), Color(25, 25, 25), Color(50, 50, 50), Color(10, 200, 10), Rect(10, 100, 0, 0), 8, tGroup));
	//mainMenu->AddElement(new GUIToggle("Item3", Color(200, 255, 255), Color(0, 0, 0), Color(25, 25, 25), Color(50, 50, 50), Color(10, 200, 10), Rect(10, 100, 0, 0), 8, tGroup));
	for (auto it : BoardManager::GetInstance().GetLevelNames())
	{
		mainMenu->AddElement(new GUIToggle(it, Color(200, 255, 255), Color(0, 0, 0), Color(25, 25, 25), Color(50, 50, 50), Color(10, 200, 10), Rect(10, 100, 0, 0), 8, tGroup));
	}

	levelSelectMenu->AddElements({
		new GUIText("Select a level", Color(200, 255, 255), Rect(10, 10, 0, 0)),
		new GUIButton("Play level 1", Color(200, 255, 255), Color(0, 0, 0), Color(25, 25, 25), Color(50, 50, 50), Rect(10, 100, 0, 0), 8, levelSelectMenu, hudMenu, OnPlay),
		new GUIButton("Back", Color(200, 255, 255), Color(0, 0, 0), Color(25, 25, 25), Color(50, 50, 50), Rect(10, 150, 0, 0), 8, levelSelectMenu, mainMenu)
	});

	levelEditorMenu->AddElements({
		new GUIText("Level editor", Color(200, 255, 255), Rect(10, 10, 0, 0)),
		new GUIButton("Back", Color(200, 255, 255), Color(0, 0, 0), Color(25, 25, 25), Color(50, 50, 50), Rect(10, 150, 0, 0), 8, levelEditorMenu, mainMenu)
	});

	hudMenu->AddElements({
		new GUIText("Score: 0", Color(255, 255, 255), Rect(10, 10, 0, 0)),
		new GUIButton("End game", Color(200, 255, 255), Color(0, 0, 0), Color(25, 25, 25), Color(50, 50, 50), Rect(10, 100, 0, 0), 8, hudMenu, levelIntermissionMenu, OnEndGame)
	});
	_scoreText = hudMenu->GetElement<GUIText>();

	endMenu->AddElements({
		new GUIText("Game over!", Color(10, 25, 55), Rect(10, 10, 0, 0)),
		new GUIButton("Main menu", Color(200, 255, 255), Color(1, 1, 1), Color(255, 25, 25), Color(50, 50, 50), Rect(10, 100, 0, 0), 8, endMenu, mainMenu)
	});

	levelIntermissionMenu->AddElements({
		new GUIText("Level completed!", Color(200, 255, 255), Rect(10, 10, 0, 0)),
		new GUIText("Score: 1000", Color(10, 25, 55), Rect(10, 10, 0, 0)),
		new GUIButton("Next level", Color(200, 255, 255), Color(0, 0, 0), Color(25, 25, 25), Color(50, 50, 50), Rect(10, 100, 0, 0), 8, levelIntermissionMenu, hudMenu, OnPlay),
		new GUIButton("Restart", Color(200, 255, 255), Color(0, 0, 0), Color(25, 25, 25), Color(50, 50, 50), Rect(10, 150, 0, 0), 8, levelIntermissionMenu, hudMenu, OnRestart),
		new GUIButton("Main menu", Color(200, 255, 255), Color(0, 0, 0), Color(25, 25, 25), Color(50, 50, 50), Rect(10, 150, 0, 0), 8, levelIntermissionMenu, mainMenu)
	});
}

void GUIManager::UpdateScoreText(int score)
{
	std::ostringstream oss;
	oss << "Score: " << score;
	_scoreText->SetText(oss.str());
}

void GUIManager::Awake()
{
	GameObject* playerObj = GameObjectManager::GetInstance().FindGameObjectByTag(Tags::Paddle);
	_playerController = playerObj->GetComponent<PlayerController>();
}
