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

GUIManager::GUIManager()
{
}

GUIManager::~GUIManager()
{
}

void GUIManager::SetupMenus()
{
	GameObject* mainMenuObj = GameObjectManager::GetInstance().CreateObject();
	GameObject* hudMenuObj = GameObjectManager::GetInstance().CreateObject();
	GameObject* endMenuObj = GameObjectManager::GetInstance().CreateObject();
	// TODO Find a better way to do these ugly lines
	GUIMenu* mainMenu = dynamic_cast<GUIMenu*>(mainMenuObj->AddComponent(new GUIMenu()));
	GUIMenu* hudMenu = dynamic_cast<GUIMenu*>(hudMenuObj->AddComponent(new GUIMenu(false)));
	GUIMenu* endMenu = dynamic_cast<GUIMenu*>(endMenuObj->AddComponent(new GUIMenu(false)));

	mainMenu->AddElementsLayout(0, 24, {
		new GUIText("Breakout", Color(200, 255, 255), Rect(10, 10, 0, 0)),
		new GUIButton("Play", Color(200, 255, 255), Color(0, 0, 0), Color(25, 25, 25), Color(50, 50, 50), Rect(10, 100, 0, 0), 8, mainMenu, hudMenu, OnPlay),
		new GUIButton("Exit", Color(200, 255, 255), Color(0, 0, 0), Color(25, 25, 25), Color(50, 50, 50), Rect(10, 150, 0, 0), 8, OnExit)
	});

	hudMenu->AddElementsLayout(0, 24, {
		new GUIText("Score: 0", Color(10, 25, 55), Rect(10, 10, 0, 0)),
		new GUIButton("End game", Color(200, 255, 255), Color(0, 0, 0), Color(25, 25, 25), Color(50, 50, 50), Rect(10, 100, 0, 0), 8, hudMenu, endMenu, OnEndGame)
	});
	_scoreText = hudMenu->GetElement<GUIText>();

	endMenu->AddElementsLayout(0, 24, {
		new GUIText("Game over!", Color(10, 25, 55), Rect(10, 10, 0, 0)),
		new GUIButton("Main menu", Color(200, 255, 255), Color(1, 1, 1), Color(255, 25, 25), Color(50, 50, 50), Rect(10, 100, 0, 0), 8, endMenu, mainMenu)
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
