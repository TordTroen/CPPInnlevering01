#include "GUIManager.h"
#include "GUIMenu.h"
#include "GameObjectManager.h"
#include "GUIText.h"
#include "GUIButton.h"
#include <sstream>
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
	std::shared_ptr<GameObject> mainMenuObj = GameObjectManager::GetInstance().CreateObject();
	std::shared_ptr<GameObject> hudMenuObj = GameObjectManager::GetInstance().CreateObject();
	std::shared_ptr<GameObject> endMenuObj = GameObjectManager::GetInstance().CreateObject();
	// TODO Find a better way to do these ugly lines
	std::shared_ptr<GUIMenu> mainMenu = dynamic_pointer_cast<GUIMenu>(mainMenuObj->AddComponent(std::shared_ptr<GUIMenu>(new GUIMenu())));
	std::shared_ptr<GUIMenu> hudMenu = dynamic_pointer_cast<GUIMenu>(hudMenuObj->AddComponent(std::shared_ptr<GUIMenu>(new GUIMenu(false))));
	std::shared_ptr<GUIMenu> endMenu = dynamic_pointer_cast<GUIMenu>(endMenuObj->AddComponent(std::shared_ptr<GUIMenu>(new GUIMenu(false))));

	mainMenu->AddElements({
		std::shared_ptr<GUIText>(new GUIText("Main menu", Color(200, 255, 255), Rect(10, 10, 0, 0))),
		std::shared_ptr<GUIButton>(new GUIButton("Play", Color(200, 255, 255), Color(0, 0, 0), Color(25, 25, 25), Color(50, 50, 50), Rect(10, 100, 0, 0), 8, mainMenu, hudMenu, OnPlay)),
		std::shared_ptr<GUIButton>(new GUIButton("Exit", Color(200, 255, 255), Color(0, 0, 0), Color(25, 25, 25), Color(50, 50, 50), Rect(10, 150, 0, 0), 8, OnExit))
	});

	hudMenu->AddElements({
		std::shared_ptr<GUIText>(new GUIText("Score: 0", Color(10, 25, 55), Rect(10, 10, 0, 0))),
		std::shared_ptr<GUIButton>(new GUIButton("End game", Color(200, 255, 255), Color(0, 0, 0), Color(25, 25, 25), Color(50, 50, 50), Rect(10, 100, 0, 0), 8, hudMenu, endMenu, OnEndGame))
	});
	_scoreText = hudMenu->GetElement<GUIText>();

	endMenu->AddElements({
		std::shared_ptr<GUIText>(new GUIText("Game over!", Color(10, 25, 55), Rect(10, 10, 0, 0))),
		std::shared_ptr<GUIButton>(new GUIButton("Main menu", Color(200, 255, 255), Color(1, 1, 1), Color(255, 25, 25), Color(50, 50, 50), Rect(10, 100, 0, 0), 8, endMenu, mainMenu))
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
	std::shared_ptr<GameObject> playerObj = GameObjectManager::GetInstance().FindGameObjectByTag(Tags::Paddle);
	_playerController = playerObj->GetComponent<PlayerController>();
}
