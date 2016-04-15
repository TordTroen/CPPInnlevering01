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

void GUIManager::Init()
{
	menuObj = GameObjectManager::GetInstance().CreateObject(Tags::MenuObject);
	eventHandler = dynamic_cast<GUIEventHandler*>(menuObj->AddComponent(new GUIEventHandler()));
}

void GUIManager::SetupMenus()
{
	customLevelCount = -1;
	customLevelStartElementIndex = -1;

	buttonColorNormal = Color(25, 25, 25);
	buttonColorHover = buttonColorNormal.Tinted(1.2);
	buttonColorDown = buttonColorNormal.Shaded(0.8);

	// TODO Find a better way to do these ugly lines
	// Create the menus
	GUILayoutMenu* mainMenu = dynamic_cast<GUILayoutMenu*>(menuObj->AddComponent(new GUILayoutMenu(Alignment::VerticalCenter, 8, 8)));
	levelSelectMenu = dynamic_cast<GUILayoutMenu*>(menuObj->AddComponent(new GUILayoutMenu(Alignment::VerticalCenter, 8, 8, false)));
	GUIMenu* levelEditorMenu = dynamic_cast<GUIMenu*>(menuObj->AddComponent(new GUIMenu(false)));
	GUIMenu* hudMenu = dynamic_cast<GUIMenu*>(menuObj->AddComponent(new GUIMenu(false)));
	instructionsMenu = dynamic_cast<GUIMenu*>(menuObj->AddComponent(new GUIMenu(false)));
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
		new GUIText("Breakout", Color(200, 255, 255), Rect(10, 10, 0, 0)),
		new GUIButton("Play", Color(200, 255, 255), buttonColorNormal, buttonColorDown, buttonColorHover, Rect(10, 100, 0, 0), 8, levelSelectMenu, hudMenu, &GUIEventHandler::OnMainMenuPlay),
		new GUIButton("Back", Color(200, 255, 255), buttonColorNormal, buttonColorDown, buttonColorHover, Rect(10, 150, 0, 0), 8, levelSelectMenu, mainMenu),
		new GUIText("Pick a level:", Color(200, 255, 255), Rect(10, 10, 0, 0))
	});

	levelSelectToggleGroup = dynamic_cast<GUIToggleGroup*>(menuObj->AddComponent(new GUIToggleGroup()));
	LoadLevelList();

	//////// LEVEL EDITOR ////////
	LevelEditorMenu* editorMenu = dynamic_cast<LevelEditorMenu*>(menuObj->AddComponent(new LevelEditorMenu(levelEditorMenu, mainMenu)));

	//////// IN-GAME MENU ////////
	scoreText = new GUIText("Score: 0", Color(255, 255, 255), Rect(10, 10, 0, 0));
	healthText = new GUIText("Lives: 0", Color(255, 255, 255), Rect(10, 40, 0, 0));
	hudMenu->AddElements({
		scoreText,
		healthText,
		new GUIButton("End game", Color(200, 255, 255), buttonColorNormal, buttonColorDown, buttonColorHover, Rect(10, 100, 0, 0), 8, hudMenu, levelIntermissionMenu, &GUIEventHandler::OnEndLevel)
	});

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

	//////// INSTRUCTIONS MENU ////////
	instructionsMenu->AddElement(new GUIText("Press space to start", Color(255, 255, 255), Rect(220, 500, 0, 0)));

	eventHandler->SetLevelEditorMenuReference(editorMenu);
}

void GUIManager::UpdateScoreText(int score)
{
	std::ostringstream oss;
	oss << "Score: " << score;
	scoreText->SetText(oss.str());
}

void GUIManager::UpdateHealthText(int health)
{
	std::ostringstream oss;
	oss << "Lives: " << health;
	healthText->SetText(oss.str());
}

void GUIManager::LoadLevelList()
{
	// Remove the old toggles for the level selction
	if (customLevelStartElementIndex > -1)
	{
		levelSelectMenu->RemoveElements(customLevelStartElementIndex, customLevelCount);
		levelSelectToggleGroup->Reset();
		BoardManager::GetInstance().ImportAllLevels();
	}

	// Get the range of the levelselect toggles in the menu element list
	customLevelStartElementIndex = levelSelectMenu->GetElementCount();
	customLevelCount = BoardManager::GetInstance().GetLevelNames().size();

	// Add a new GUIToggle for each level
	for (auto it : BoardManager::GetInstance().GetLevelNames())
	{
		std::cout << "Rendering level: " << it << std::endl;
		levelSelectMenu->AddElement(new GUIToggle(it, Color(100, 255, 255), buttonColorNormal, buttonColorDown, buttonColorHover, Color(10, 200, 10), Rect(10, 100, 0, 0), 8, levelSelectToggleGroup));
	}
}

void GUIManager::SetInstructionsActive(bool active)
{
	instructionsMenu->SetActive(active);
}
