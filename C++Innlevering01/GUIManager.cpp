#include "GUIManager.h"
#include <sstream>
#include <memory>
#include "GUIMenu.h"
#include "GameObjectManager.h"
#include "GUIText.h"
#include "GUIButton.h"
#include "GameManager.h"
#include "Tags.h"

void OnExit()
{
	GameManager::GetInstance().SetGameState(Exit);
}

void OnPlay()
{
	GameManager::GetInstance().SetGameState(InGame);
}

void OnEndGame()
{
	GameManager::GetInstance().SetGameState(MainMenu);
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
	GUIMenu* mainMenu = dynamic_cast<GUIMenu*>(menuObj->AddComponent(new GUIMenu()));
	GUIMenu* levelSelectMenu = dynamic_cast<GUIMenu*>(menuObj->AddComponent(new GUIMenu(false)));
	GUIMenu* levelEditorMenu = dynamic_cast<GUIMenu*>(menuObj->AddComponent(new GUIMenu(false)));
	GUIMenu* hudMenu = dynamic_cast<GUIMenu*>(menuObj->AddComponent(new GUIMenu(false)));
	GUIMenu* endMenu = dynamic_cast<GUIMenu*>(menuObj->AddComponent(new GUIMenu(false)));
	GUIMenu* levelIntermissionMenu = dynamic_cast<GUIMenu*>(menuObj->AddComponent(new GUIMenu(false)));

	mainMenu->AddElementsLayout(0, 24, {
		new GUIText("Breakout", Color(200, 255, 255), Rect(10, 10, 0, 0)),
		new GUIButton("Play", Color(200, 255, 255), Color(0, 0, 0), Color(25, 25, 25), Color(50, 50, 50), Rect(10, 100, 0, 0), 8, mainMenu, levelSelectMenu),
		new GUIButton("Level editor", Color(200, 255, 255), Color(0, 0, 0), Color(25, 25, 25), Color(50, 50, 50), Rect(10, 100, 0, 0), 8, mainMenu, levelEditorMenu),
		new GUIButton("Exit", Color(200, 255, 255), Color(0, 0, 0), Color(25, 25, 25), Color(50, 50, 50), Rect(10, 150, 0, 0), 8, OnExit)
	});

	levelSelectMenu->AddElementsLayout(0, 24, {
		new GUIText("Select a level", Color(200, 255, 255), Rect(10, 10, 0, 0)),
		new GUIButton("Start game", Color(200, 255, 255), Color(0, 0, 0), Color(25, 25, 25), Color(50, 50, 50), Rect(10, 100, 0, 0), 8, levelSelectMenu, hudMenu, OnPlay),
		new GUIButton("Back", Color(200, 255, 255), Color(0, 0, 0), Color(25, 25, 25), Color(50, 50, 50), Rect(10, 150, 0, 0), 8, levelSelectMenu, mainMenu)
	});

	levelEditorMenu->AddElementsLayout(0, 24, {
		new GUIText("Level editor", Color(200, 255, 255), Rect(10, 10, 0, 0)),
		new GUIButton("Back", Color(200, 255, 255), Color(0, 0, 0), Color(25, 25, 25), Color(50, 50, 50), Rect(10, 150, 0, 0), 8, levelEditorMenu, mainMenu)
	});

	hudMenu->AddElementsLayout(0, 24, {
		new GUIText("Score: 0", Color(255, 255, 255), Rect(10, 10, 0, 0)),
		new GUIButton("End game", Color(200, 255, 255), Color(0, 0, 0), Color(25, 25, 25), Color(50, 50, 50), Rect(10, 100, 0, 0), 8, hudMenu, levelIntermissionMenu, OnEndGame)
	});
	_scoreText = hudMenu->GetElement<GUIText>();

	endMenu->AddElementsLayout(0, 24, {
		new GUIText("Game over!", Color(10, 25, 55), Rect(10, 10, 0, 0)),
		new GUIButton("Main menu", Color(200, 255, 255), Color(1, 1, 1), Color(255, 25, 25), Color(50, 50, 50), Rect(10, 100, 0, 0), 8, endMenu, mainMenu)
	});

	levelIntermissionMenu->AddElementsLayout(0, 24, {
		new GUIText("Level completed!", Color(200, 255, 255), Rect(10, 10, 0, 0)),
		new GUIText("Score: 1000", Color(10, 25, 55), Rect(10, 10, 0, 0)),
		new GUIButton("Next level", Color(200, 255, 255), Color(0, 0, 0), Color(25, 25, 25), Color(50, 50, 50), Rect(10, 100, 0, 0), 8, levelIntermissionMenu, hudMenu, OnPlay),
		new GUIButton("Restart", Color(200, 255, 255), Color(0, 0, 0), Color(25, 25, 25), Color(50, 50, 50), Rect(10, 150, 0, 0), 8, levelIntermissionMenu, hudMenu),
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
