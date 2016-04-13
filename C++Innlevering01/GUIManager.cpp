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
#include "LevelEditorMenu.h"

GUIManager::~GUIManager()
{
}

void GUIManager::SetupMenus()
{
	customLevelCount = -1;
	customLevelStartElementIndex = -1;

	buttonColorNormal = Color(25, 25, 25);
	buttonColorHover = buttonColorNormal.Tinted(1.2);
	buttonColorDown = buttonColorNormal.Shaded(0.8);

	// Store the screen dimensions for easy access
	int sWidth = GameManager::GetInstance().GetWindowWidth();
	int sHeight= GameManager::GetInstance().GetWindowHeight();

	GameObject* menuObj = GameObjectManager::GetInstance().CreateObject(Tags::MenuObject);
	GUIEventHandler* eventHandler = dynamic_cast<GUIEventHandler*>(menuObj->AddComponent(new GUIEventHandler()));

	// TODO Find a better way to do these ugly lines
	// Create the menus
	GUILayoutMenu* mainMenu = dynamic_cast<GUILayoutMenu*>(menuObj->AddComponent(new GUILayoutMenu(Alignment::VerticalCenter, 8, 8)));
	levelSelectMenu = dynamic_cast<GUILayoutMenu*>(menuObj->AddComponent(new GUILayoutMenu(Alignment::VerticalCenter, 8, 8, false)));
	GUIMenu* levelEditorMenu = dynamic_cast<GUIMenu*>(menuObj->AddComponent(new GUIMenu(false)));
	GUIMenu* hudMenu = dynamic_cast<GUIMenu*>(menuObj->AddComponent(new GUIMenu(false)));
	GUILayoutMenu* endMenu = dynamic_cast<GUILayoutMenu*>(menuObj->AddComponent(new GUILayoutMenu(Alignment::VerticalCenter, 8, 8, false)));
	GUILayoutMenu* levelIntermissionMenu = dynamic_cast<GUILayoutMenu*>(menuObj->AddComponent(new GUILayoutMenu(Alignment::VerticalCenter, 8, 8, false)));

	//mainMenu->SetOverrideSize(Vector2D(100, -1));

	//////// MAIN MENU ////////
	mainMenu->AddElements({
		new GUIText("Breakout", Color(200, 255, 255), Rect(10, 10, 0, 0)),
		new GUIButton("Play", Color(200, 255, 255), buttonColorNormal, buttonColorDown, buttonColorHover, Rect(10, 100, 0, 0), 8, mainMenu, levelSelectMenu),
		new GUIButton("Level editor", Color(200, 255, 255), buttonColorNormal, buttonColorDown, buttonColorHover, Rect(10, 100, 0, 0), 8, mainMenu, levelEditorMenu),
		new GUIButton("Exit", Color(200, 255, 255), buttonColorNormal, buttonColorDown, buttonColorHover, Rect(10, 150, 0, 0), 8, &GUIEventHandler::OnMainMenuExit),
	});

	//////// LEVEL SELECT ////////
	levelSelectMenu->AddElements({
		new GUIButton("Play", Color(200, 255, 255), buttonColorNormal, buttonColorDown, buttonColorHover, Rect(10, 100, 0, 0), 8, levelSelectMenu, hudMenu, &GUIEventHandler::OnMainMenuPlay),
		new GUIButton("Back", Color(200, 255, 255), buttonColorNormal, buttonColorDown, buttonColorHover, Rect(10, 150, 0, 0), 8, levelSelectMenu, mainMenu),
		new GUIText("Pick a level:", Color(200, 255, 255), Rect(10, 10, 0, 0))
	});

	levelSelectToggleGroup = dynamic_cast<GUIToggleGroup*>(menuObj->AddComponent(new GUIToggleGroup()));
	LoadLevelList();

	//////// LEVEL EDITOR ////////
	LevelEditorMenu* editorMenu = dynamic_cast<LevelEditorMenu*>(menuObj->AddComponent(new LevelEditorMenu(levelEditorMenu, mainMenu)));

	//////// IN-GAME MENU ////////
	hudMenu->AddElements({
		new GUIText("Score: 0", Color(255, 255, 255), Rect(10, 10, 0, 0)),
		new GUIButton("End game", Color(200, 255, 255), buttonColorNormal, buttonColorDown, buttonColorHover, Rect(10, 100, 0, 0), 8, hudMenu, levelIntermissionMenu, &GUIEventHandler::OnEndLevel)
	});
	scoreText = hudMenu->GetElement<GUIText>();

	//////// GAME OVER MENU ////////
	endMenu->AddElements({
		new GUIText("Game over!", Color(10, 25, 55), Rect(10, 10, 0, 0)),
		new GUIButton("Main menu", Color(200, 255, 255), buttonColorNormal, buttonColorDown, buttonColorHover, Rect(10, 100, 0, 0), 8, endMenu, mainMenu)
	});

	//////// MENU BETWEEN LEVELS ////////
	levelIntermissionMenu->AddElements({
		new GUIText("Level completed!", Color(200, 255, 255), Rect(10, 10, 0, 0)),
		new GUIText("Score: 1000", Color(10, 25, 55), Rect(10, 10, 0, 0)),
		//new GUIButton("Next level", Color(200, 255, 255), buttonColorNormal, buttonColorDown, buttonColorHover, Rect(10, 100, 0, 0), 8, levelIntermissionMenu, hudMenu, OnPlay),
		new GUIButton("Restart", Color(200, 255, 255), buttonColorNormal, buttonColorDown, buttonColorHover, Rect(10, 150, 0, 0), 8, levelIntermissionMenu, hudMenu, &GUIEventHandler::OnRestartLevel),
		new GUIButton("Main menu", Color(200, 255, 255), buttonColorNormal, buttonColorDown, buttonColorHover, Rect(10, 150, 0, 0), 8, levelIntermissionMenu, mainMenu)
	});

	eventHandler->SetLevelEditorMenuReference(editorMenu);
}

void GUIManager::UpdateScoreText(int score)
{
	std::ostringstream oss;
	oss << "Score: " << score;
	scoreText->SetText(oss.str());
}

void GUIManager::LoadLevelList()
{
	// TODO Remove previous elements
	if (customLevelStartElementIndex > -1)
	{
		levelSelectMenu->RemoveElements(customLevelStartElementIndex, customLevelCount);
		BoardManager::GetInstance().ImportAllLevels();
	}

	customLevelStartElementIndex = levelSelectMenu->GetElementCount();
	customLevelCount = BoardManager::GetInstance().GetLevelNames().size();
	for (auto it : BoardManager::GetInstance().GetLevelNames())
	{
		std::cout << "Rendering level: " << it << std::endl;
		levelSelectMenu->AddElement(new GUIToggle(it, Color(100, 255, 255), buttonColorNormal, buttonColorDown, buttonColorHover, Color(10, 200, 10), Rect(10, 100, 0, 0), 8, levelSelectToggleGroup));
	}
}

void GUIManager::Awake()
{
	GameObject* playerObj = GameObjectManager::GetInstance().FindGameObjectByTag(Tags::Paddle);
	playerController = playerObj->GetComponent<PlayerController>();
}
