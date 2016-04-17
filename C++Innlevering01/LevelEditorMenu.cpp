#include "LevelEditorMenu.h"
#include <sstream>
#include <fstream>
#include "GUIButton.h"
#include "LevelBrick.h"
#include "GUIButton.h"
#include "BoardManager.h"
#include "GUIToggleGroup.h"
#include "GUIToggle.h"
#include "GameObject.h"
#include "GUILevelEditorButton.h"
#include "GUITextField.h"
#include "GUIEventHandler.h"
#include "GameManager.h"

LevelEditorMenu::LevelEditorMenu(GUIMenu* levelEditorMenu, GUIMenu* previousMenu, GUILayoutMenu* levelSaveMenu, BoardManager* boardManager)
	: levelName("Unnamed"), levelEditorMenu(levelEditorMenu), previousMenu(previousMenu), levelSaveMenu(levelSaveMenu), boardManager(boardManager)
{
}

LevelEditorMenu::~LevelEditorMenu()
{
}

void LevelEditorMenu::Init()
{
	// TODO Do the layout of this menu so it looks better
	// The brick buttons position like they are in an actual level
	int index = 0;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			GameObject* btnObj = gameManager->CreateObject();
			GUILevelEditorButton* btn = new GUILevelEditorButton(Color(0, 0, 0), Color(25, 25, 25), Color(50, 50, 50), Rect(j * LevelBrick::BrickWidth, i * LevelBrick::BrickHeight, LevelBrick::BrickWidth, LevelBrick::BrickHeight), index);
			btnObj->AddComponent(btn);
			buttons.emplace_back(btn);
			levelEditorMenu->AddElement(btn);
			index++;
		}
	}

	// Editor control buttons
	//levelEditorMenu->AddElement(new GUIButton("Save", Color(200, 255, 255), Color(0, 0, 0), Color(25, 25, 25), Color(50, 50, 50), Rect(700 - 200, 400, 100, 100), 8, &GUIEventHandler::OnEditorSave));
	levelEditorMenu->AddElement(new GUIButton("Save",      Color(200, 255, 255), Color(0, 0, 0), Color(25, 25, 25), Color(50, 50, 50), Rect(700 - 200, 400, 100, 100), 8, levelEditorMenu, levelSaveMenu));
	levelEditorMenu->AddElement(new GUIButton("Clear",     Color(200, 255, 255), Color(0, 0, 0), Color(25, 25, 25), Color(50, 50, 50), Rect(700 - 200, 470, 100, 100), 8, &GUIEventHandler::OnEditorClear));
	levelEditorMenu->AddElement(new GUIButton("Main menu", Color(200, 255, 255), Color(0, 0, 0), Color(25, 25, 25), Color(50, 50, 50), Rect(700 - 200, 540, 100, 100), 8, levelEditorMenu, previousMenu));
	
	// Brick editor buttons
	//levelEditorToggleGroup = dynamic_cast<GUIToggleGroup*>(GetGameObject()->AddComponent(new GUIToggleGroup()));
	levelEditorToggleGroup = new GUIToggleGroup();
	GetGameObject()->AddComponent(levelEditorToggleGroup);
	for (int i = 0; i < 8; i++)
	{
		Color toolNormalColor = LevelBrick::GetBrickColor(static_cast<BrickType>(i));
		Color toolHoverColor = toolNormalColor.Tinted(1.1);
		Color toolDownColor = toolNormalColor.Shaded(0.1);
		Color toolSelectedColor = toolNormalColor.Shaded(0.6);
		levelEditorMenu->AddElement(new GUIToggle(" ", Color(200, 255, 255), toolNormalColor, toolDownColor, toolHoverColor, toolSelectedColor, Rect(16 + i * (LevelBrick::BrickWidth + 32), 700 - LevelBrick::BrickHeight - 16, LevelBrick::BrickWidth, LevelBrick::BrickHeight), 0, levelEditorToggleGroup, false));
	}

	// Saving menu
	levelSaveMenu->AddElement(new GUIText("Saving", Color(255, 255, 255), Rect(0, 0, 0, 0)));
	levelSaveMenu->AddElement(new GUIText(" ", Color(255, 255, 255), Rect(0, 0, 0, 0)));

	// Level name input
	levelSaveMenu->AddElement(new GUIText("Level name:", Color(255, 255, 255), Rect(10, 340, 10, 10)));
	GameObject* obj = gameManager->CreateObject();
	textField = new GUITextField("Unnamed", Rect(10, 400, 10, 10));
	obj->AddComponent(textField);
	levelSaveMenu->AddElement(textField);

	// Save slots
	levelSaveMenu->AddElement(new GUIText("Pick a save slot:", Color(255, 255, 255), Rect(0, 0, 0, 0)));
	levelSaveToggleGroup = new GUIToggleGroup();
	GetGameObject()->AddComponent(levelSaveToggleGroup);

	Color slotToggleColor = Color(50, 50, 50);
	int standardLevelCount = boardManager->GetStandardLevelCount();
	for (int i = 0; i < BoardManager::CustomLevelCount; i++)
	{
		// If there is a level in that slot, use the levels name as the text
		std::ostringstream toggleText;
		if (i + standardLevelCount < boardManager->GetLevelNames().size())
		{
			toggleText << boardManager->GetLevelNames()[i + standardLevelCount];
		}
		else
		{
			toggleText << "Slot " << i+1;
		}
		levelSaveMenu->AddElement(new GUIToggle(toggleText.str(), Color(255, 255, 255), slotToggleColor, slotToggleColor.Tinted(1.1), slotToggleColor.Tinted(1.2), slotToggleColor.Shaded(0.9), Rect(0, 0, 0, 0), 8, levelSaveToggleGroup));
	}

	// Save button
	levelSaveMenu->AddElement(new GUIText(" ", Color(255, 255, 255), Rect(0, 0, 0, 0)));
	levelSaveMenu->AddElement(new GUIButton("Save", Color(200, 255, 255), Color(0, 0, 0), Color(25, 25, 25), Color(50, 50, 50), Rect(700 - 200, 400, 100, 100), 8, levelSaveMenu, levelEditorMenu, &GUIEventHandler::OnEditorSave));

	Clear();
}

void LevelEditorMenu::Save()
{
	levelName = textField->GetInputText();

	// Create a string based on the name and what index all the buttons have
	std::ostringstream levelString;
	levelString << levelName;
	levelString << "|";
	int index   = 0;

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			levelString << buttons[index]->GetBrickId();
			index++;
		}
		if (i < rows - 1) levelString << "|";
	}

	levelString << "\n";

	boardManager->SaveLevel(levelSaveToggleGroup->GetCurrentToggleIndex(), levelString.str());
}

void LevelEditorMenu::Clear()
{
	for (auto it : buttons)
	{
		Color color = LevelBrick::GetBrickColor(BrickType::BrickEmpty);
		it->SetColors(color, color, color);
	}
}

int LevelEditorMenu::GetCurrentTool() const
{
	return levelEditorToggleGroup->GetCurrentToggleIndex();
}

void LevelEditorMenu::Awake()
{
	Init();
}
