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
#include "LevelBrick.h"

// TODO: Make these into GUIManager member functions. I don't currently know an easy way to do this...
void OnExit()
{
	GameManager::GetInstance().SetGameState(GameState::Exit);
}

void OnPlay()
{
	GameManager::GetInstance().SetGameState(GameState::InGame);
	int levelIndex = GUIManager::GetInstance().GetLevelSelectToggleGroup()->GetCurrentToggleIndex();
	BoardManager::GetInstance().SetCurrentLevel(levelIndex);
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
	GUILayoutMenu* mainMenu = dynamic_cast<GUILayoutMenu*>(menuObj->AddComponent(new GUILayoutMenu(Alignment::Bottom, 20, 8)));
	GUILayoutMenu* levelSelectMenu = dynamic_cast<GUILayoutMenu*>(menuObj->AddComponent(new GUILayoutMenu(Alignment::VerticalCenter, 0, 8, false)));
	GUIMenu* levelEditorMenu = dynamic_cast<GUIMenu*>(menuObj->AddComponent(new GUIMenu(false)));
	GUIMenu* hudMenu = dynamic_cast<GUIMenu*>(menuObj->AddComponent(new GUIMenu(false)));
	GUILayoutMenu* endMenu = dynamic_cast<GUILayoutMenu*>(menuObj->AddComponent(new GUILayoutMenu(Alignment::VerticalCenter, 0, 8, false)));
	GUILayoutMenu* levelIntermissionMenu = dynamic_cast<GUILayoutMenu*>(menuObj->AddComponent(new GUILayoutMenu(Alignment::VerticalCenter, 0, 8, false)));

	//mainMenu->SetOverrideSize(Vector2D(100, -1));

	//////// MAIN MENU ////////
	mainMenu->AddElements({
		new GUIText("Breakout", Color(200, 255, 255), Rect(10, 10, 0, 0)),
		new GUIButton("Play", Color(200, 255, 255), Color(0, 0, 0), Color(25, 25, 25), Color(50, 50, 50), Rect(10, 100, 0, 0), 8, mainMenu, levelSelectMenu),
		new GUIButton("Level editor", Color(200, 255, 255), Color(0, 0, 0), Color(25, 25, 25), Color(50, 50, 50), Rect(10, 100, 0, 0), 8, mainMenu, levelEditorMenu),
		new GUIButton("Exit", Color(200, 255, 255), Color(0, 0, 0), Color(25, 25, 25), Color(50, 50, 50), Rect(10, 150, 0, 0), 8, OnExit),
	});

	//////// LEVEL SELECT ////////
	levelSelectMenu->AddElements({
		new GUIText("Select a level", Color(200, 255, 255), Rect(10, 10, 0, 0)),
		new GUIButton("Play", Color(200, 255, 255), Color(0, 0, 0), Color(25, 25, 25), Color(50, 50, 50), Rect(10, 100, 0, 0), 8, levelSelectMenu, hudMenu, OnPlay),
		new GUIButton("Back", Color(200, 255, 255), Color(0, 0, 0), Color(25, 25, 25), Color(50, 50, 50), Rect(10, 150, 0, 0), 8, levelSelectMenu, mainMenu)
	});

	levelSelectToggleGroup = dynamic_cast<GUIToggleGroup*>(menuObj->AddComponent(new GUIToggleGroup()));
	for (auto it : BoardManager::GetInstance().GetLevelNames())
	{
		levelSelectMenu->AddElement(new GUIToggle(it, Color(100, 255, 255), Color(100, 100, 100), Color(25, 25, 25), Color(50, 50, 50), Color(10, 200, 10), Rect(10, 100, 0, 0), 8, levelSelectToggleGroup));
	}

	//////// LEVEL EDITOR ////////
	for (int i = 0; i < 14; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			levelEditorMenu->AddElement(new GUIButton(" ", Color(200, 255, 255), Color(0, 0, 0), Color(25, 25, 25), Color(50, 50, 50), Rect(i * LevelBrick::BrickWidth, j * LevelBrick::BrickHeight, LevelBrick::BrickWidth, LevelBrick::BrickHeight), 0, NULL, false));
		}
	}

	levelEditorMenu->AddElement(new GUIButton("Back", Color(200, 255, 255), Color(0, 0, 0), Color(25, 25, 25), Color(50, 50, 50), Rect(10, 600, 100, 100), 8, levelEditorMenu, mainMenu));
	levelEditorToggleGroup = dynamic_cast<GUIToggleGroup*>(menuObj->AddComponent(new GUIToggleGroup()));
	for (int i = 0; i < 6; i ++)
	{
		levelEditorMenu->AddElement(new GUIToggle("tool", Color(200, 255, 255), Color(0, 0, 0), Color(25, 25, 25), Color(50, 50, 50), Color(0, 200, 200), Rect(i * (LevelBrick::BrickWidth + 32), 600, LevelBrick::BrickWidth, LevelBrick::BrickHeight), 8, levelEditorToggleGroup));
	}

	//////// IN-GAME MENU ////////
	hudMenu->AddElements({
		new GUIText("Score: 0", Color(255, 255, 255), Rect(10, 10, 0, 0)),
		new GUIButton("End game", Color(200, 255, 255), Color(0, 0, 0), Color(25, 25, 25), Color(50, 50, 50), Rect(10, 100, 0, 0), 8, hudMenu, levelIntermissionMenu, OnEndGame)
	});
	scoreText = hudMenu->GetElement<GUIText>();

	//////// GAME OVER MENU ////////
	endMenu->AddElements({
		new GUIText("Game over!", Color(10, 25, 55), Rect(10, 10, 0, 0)),
		new GUIButton("Main menu", Color(200, 255, 255), Color(1, 1, 1), Color(255, 25, 25), Color(50, 50, 50), Rect(10, 100, 0, 0), 8, endMenu, mainMenu)
	});

	//////// MENU BETWEEN LEVELS ////////
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
	scoreText->SetText(oss.str());
}

void GUIManager::Awake()
{
	GameObject* playerObj = GameObjectManager::GetInstance().FindGameObjectByTag(Tags::Paddle);
	playerController = playerObj->GetComponent<PlayerController>();
}
