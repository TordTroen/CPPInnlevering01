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

void GUIManager::Init(GameManager* gameManager)
{
	this->gameManager = gameManager;
	menuObj = gameManager->CreateObject(Tags::MenuObject);

	eventHandler = new GUIEventHandler();
	menuObj->AddComponent(eventHandler);
}

void GUIManager::SetupMenus()
{
	customLevelCount  = -1;
	customLevelStartElementIndex = -1;

	buttonColorNormal = Color(25, 25, 25);
	buttonColorHover  = buttonColorNormal.Tinted(1.2);
	buttonColorDown   = buttonColorNormal.Shaded(0.8);
	textColor = Color(200, 255, 255);

	// TODO Find a better way to do these ugly lines
	// Create the menus
	GUILayoutMenu* mainMenu  = dynamic_cast<GUILayoutMenu*>(menuObj->AddComponent(new GUILayoutMenu(Alignment::VerticalCenter, 8, 8)));
	levelSelectMenu			 = dynamic_cast<GUILayoutMenu*>(menuObj->AddComponent(new GUILayoutMenu(Alignment::VerticalCenter, 8, 8, false)));
	GUIMenu* levelEditorMenu = dynamic_cast<GUIMenu*>(menuObj->AddComponent(new GUIMenu(false)));
	GUILayoutMenu* levelSaveMenu = dynamic_cast<GUILayoutMenu*>(menuObj->AddComponent(new GUILayoutMenu(Alignment::VerticalCenter, 8, 8, false)));
	hudMenu		 = dynamic_cast<GUIMenu*>(menuObj->AddComponent(new GUIMenu(false)));
	instructionsMenu		 = dynamic_cast<GUIMenu*>(menuObj->AddComponent(new GUIMenu(false)));
	endMenu	 = dynamic_cast<GUILayoutMenu*>(menuObj->AddComponent(new GUILayoutMenu(Alignment::VerticalCenter, 8, 8, false)));
	levelIntermissionMenu = dynamic_cast<GUILayoutMenu*>(menuObj->AddComponent(new GUILayoutMenu(Alignment::VerticalCenter, 8, 8, false)));

	//mainMenu->SetOverrideSize(Vector2D(100, -1));

	//////// MAIN MENU ////////
	mainMenu->AddElements({
		new GUIText(  "Breakout", textColor, Rect(10, 10, 0, 0)),
		new GUIButton("Play", textColor, buttonColorNormal, buttonColorDown, buttonColorHover, Rect(10, 100, 0, 0), 8, mainMenu, levelSelectMenu),
		new GUIButton("Level editor", textColor, buttonColorNormal, buttonColorDown, buttonColorHover, Rect(10, 100, 0, 0), 8, mainMenu, levelEditorMenu),
		new GUIButton("Exit",textColor, buttonColorNormal, buttonColorDown, buttonColorHover, Rect(10, 150, 0, 0), 8, &GUIEventHandler::OnMainMenuExit),
	});

	//////// LEVEL SELECT ////////
	levelSelectMenu->AddElements({
		new GUIText(  "Breakout", textColor, Rect(10, 10, 0, 0)),
		new GUIButton("Play", textColor, buttonColorNormal, buttonColorDown, buttonColorHover, Rect(10, 100, 0, 0), 8, levelSelectMenu, hudMenu, &GUIEventHandler::OnMainMenuPlay),
		new GUIButton("Back", textColor, buttonColorNormal, buttonColorDown, buttonColorHover, Rect(10, 150, 0, 0), 8, levelSelectMenu, mainMenu),
		new GUIText(  "Pick a level:", textColor, Rect(10, 10, 0, 0))
	});

	levelSelectToggleGroup = dynamic_cast<GUIToggleGroup*>(menuObj->AddComponent(new GUIToggleGroup()));
	LoadLevelList();

	//////// LEVEL EDITOR ////////
	LevelEditorMenu* editorMenu = dynamic_cast<LevelEditorMenu*>(menuObj->AddComponent(new LevelEditorMenu(levelEditorMenu, mainMenu, levelSaveMenu)));

	//////// IN-GAME MENU ////////
	scoreText = new GUIText("Score: 0", textColor, Rect(10, 10, 0, 0));
	healthText = new GUIText("Lives: 0", textColor, Rect(10, 40, 0, 0));
	hudMenu->AddElements({
		scoreText,
		healthText,
		//new GUIButton("End game", textColor, buttonColorNormal, buttonColorDown, buttonColorHover, Rect(10, 100, 0, 0), 8, hudMenu, levelIntermissionMenu, &GUIEventHandler::OnEndLevel)
	});
	// Set the score/health text positions to the bottom of the screen
	int yPos = gameManager->GetWindowHeight() - scoreText->GetTransform()->GetSize().Y;
	scoreText->GetTransform()->SetPosition(Vector2D(10, yPos));
	healthText->GetTransform()->SetPosition(Vector2D(200, yPos));

	//////// GAME OVER MENU ////////
	endMenu->AddElements({
		new GUIText("Game over!", textColor, Rect(10, 10, 0, 0)),
		new GUIButton("Restart", textColor, buttonColorNormal, buttonColorDown, buttonColorHover, Rect(10, 150, 0, 0), 8, endMenu, hudMenu, &GUIEventHandler::OnRestartLevel),
		new GUIButton("Main menu", textColor, buttonColorNormal, buttonColorDown, buttonColorHover, Rect(10, 100, 0, 0), 8, endMenu, mainMenu)
	});

	//////// MENU BETWEEN LEVELS ////////
	endScoreText = new GUIText("Score: 1000", textColor, Rect(10, 10, 0, 0));
	levelIntermissionMenu->AddElements({
		new GUIText("Level completed!", textColor, Rect(10, 10, 0, 0)),
		endScoreText,
		new GUIButton("Next level", textColor, buttonColorNormal, buttonColorDown, buttonColorHover, Rect(10, 100, 0, 0), 8, levelIntermissionMenu, hudMenu, &GUIEventHandler::OnNextLevel),
		new GUIButton("Restart", textColor, buttonColorNormal, buttonColorDown, buttonColorHover, Rect(10, 150, 0, 0), 8, levelIntermissionMenu, hudMenu, &GUIEventHandler::OnRestartLevel),
		new GUIButton("Main menu", textColor, buttonColorNormal, buttonColorDown, buttonColorHover, Rect(10, 150, 0, 0), 8, levelIntermissionMenu, mainMenu)
	});

	//////// INSTRUCTIONS MENU ////////
	instructionsMenu->AddElement(new GUIText("Press space to start", textColor, Rect(220, 500, 0, 0)));

	eventHandler->Init(editorMenu, gameManager);
}

void GUIManager::UpdateScoreText(int score)
{
	std::ostringstream oss;
	oss << "Score: " << score;
	scoreText->SetText(oss.str());
}

void GUIManager::UpdateEndScoreText(int score)
{
	std::ostringstream oss;
	oss << "Score: " << score;
	endScoreText->SetText(oss.str());
}

void GUIManager::UpdateHealthText(int health)
{
	std::ostringstream oss;
	oss << "Lives: " << health;
	healthText->SetText(oss.str());
}

void GUIManager::LoadLevelList()
{
	int standardCount = BoardManager::GetInstance().GetStandardLevelCount();

	// Remove the old toggles for the level selction
	if (customLevelStartElementIndex > -1)
	{
		levelSelectMenu->RemoveElements(customLevelStartElementIndex, customLevelCount+1);
		BoardManager::GetInstance().ImportAllLevels();
		levelSelectToggleGroup->Reset();
	}

	// Get the range of the levelselect toggles in the menu element list
	customLevelStartElementIndex = levelSelectMenu->GetElementCount();
	customLevelCount = BoardManager::GetInstance().GetLevelNames().size();

	// Add a new GUIToggle for each level
	int i = 0;
	for (auto it : BoardManager::GetInstance().GetLevelNames())
	{
		if (i == standardCount)
		{
			levelSelectMenu->AddElement(new GUIText("Custom levels:", textColor, Rect(0, 0, 0, 0)));
		}
		levelSelectMenu->AddElement(new GUIToggle(it, Color(100, 255, 255), buttonColorNormal, buttonColorDown, buttonColorHover, Color(10, 200, 10), Rect(10, 100, 0, 0), 8, levelSelectToggleGroup));
		i++;
	}
}

void GUIManager::SetInstructionsActive(bool active)
{
	instructionsMenu->SetActive(active);
}

void GUIManager::SetGameOverMenuActive(bool active)
{
	endMenu->SetActive(active);
	hudMenu->SetActive(false);
}

void GUIManager::SetWinMenuActive(bool active)
{
	levelIntermissionMenu->SetActive(active);
	hudMenu->SetActive(false);
}

void GUIManager::SetHUDMenuActive(bool active)
{
	hudMenu->SetActive(active);
}
