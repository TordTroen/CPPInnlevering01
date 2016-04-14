#include "LevelEditorMenu.h"
#include <sstream>
#include <fstream>
#include "GUIButton.h"
#include "LevelBrick.h"
#include "GUIButton.h"
#include "GUIToggleGroup.h"
#include "GUIToggle.h"
#include "GameObject.h"
#include "GUILevelEditorButton.h"
#include "GameObjectManager.h"
#include "GUITextField.h"
#include "GUIEventHandler.h"

LevelEditorMenu::LevelEditorMenu(GUIMenu* levelEditorMenu, GUIMenu* previousMenu)
	: levelName("Unnamed"), levelEditorMenu(levelEditorMenu), previousMenu(previousMenu)
{
}

LevelEditorMenu::~LevelEditorMenu()
{
}

void LevelEditorMenu::Init()
{
	// TODO Clean up in this mess of a menu
	// The brick buttons position like they are in an actual level
	int index = 0;
	for (int i = 0; i < columns; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			GameObject* btnObj = GameObjectManager::GetInstance().CreateObject();
			GUILevelEditorButton* btn = dynamic_cast<GUILevelEditorButton*>(btnObj->AddComponent(new GUILevelEditorButton(Color(0, 0, 0), Color(25, 25, 25), Color(50, 50, 50), Rect(i * LevelBrick::BrickWidth, j * LevelBrick::BrickHeight, LevelBrick::BrickWidth, LevelBrick::BrickHeight), index)));
			buttons.emplace_back(btn);
			levelEditorMenu->AddElement(btn);
			std::cout << "Creating button: " << (index) << std::endl;
			index++;
		}
	}

	// Editor control buttons
	levelEditorMenu->AddElement(new GUIButton("Save", Color(200, 255, 255), Color(0, 0, 0), Color(25, 25, 25), Color(50, 50, 50), Rect(700 - 200, 400, 100, 100), 8, &GUIEventHandler::OnEditorSave));
	levelEditorMenu->AddElement(new GUIButton("Clear", Color(200, 255, 255), Color(0, 0, 0), Color(25, 25, 25), Color(50, 50, 50), Rect(700 - 200, 470, 100, 100), 8, &GUIEventHandler::OnEditorClear));
	levelEditorMenu->AddElement(new GUIButton("Main menu", Color(200, 255, 255), Color(0, 0, 0), Color(25, 25, 25), Color(50, 50, 50), Rect(700 - 200, 540, 100, 100), 8, levelEditorMenu, previousMenu));
	
	// Brick editor buttons
	levelEditorToggleGroup = dynamic_cast<GUIToggleGroup*>(GetGameObject()->AddComponent(new GUIToggleGroup()));
	for (int i = 0; i < 8; i++)
	{
		Color toolNormalColor = LevelBrick::GetBrickColor(static_cast<BrickType>(i));
		Color toolHoverColor = toolNormalColor.Tinted(1.1);
		Color toolDownColor = toolNormalColor.Shaded(0.1);
		Color toolSelectedColor = toolNormalColor.Shaded(0.6);
		levelEditorMenu->AddElement(new GUIToggle(" ", Color(200, 255, 255), toolNormalColor, toolDownColor, toolHoverColor, toolSelectedColor, Rect(16 + i * (LevelBrick::BrickWidth + 32), 700 - LevelBrick::BrickHeight - 16, LevelBrick::BrickWidth, LevelBrick::BrickHeight), 0, levelEditorToggleGroup, false));
	}

	// Level name input
	levelEditorMenu->AddElement(new GUIText("Level name:", Color(255, 255, 255), Rect(10, 340, 10, 10)));
	GameObject* obj = GameObjectManager::GetInstance().CreateObject();
	textField = dynamic_cast<GUITextField*>(obj->AddComponent(new GUITextField("Level name here", Rect(10, 400, 10, 10))));
	levelEditorMenu->AddElement(textField);

	Clear();
}

void LevelEditorMenu::Save()
{
	levelName = textField->GetInputText();

	// Create a string based on the name and what index all the buttons have
	std::ostringstream levelString;
	levelString << levelName;
	levelString << "|";
	int index = 0;
	for (int i = 0; i < columns; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			std::cout << "Saving button: " << buttons[index]->GetButtonIndex() << " - " << (index)<< std::endl;
			levelString << buttons[index]->GetBrickId();
			index++;
		}
		if (i < rows - 1) levelString << "|";
	}
	levelString << "\n";
	std::cout << "Level saved: " << levelString.str() << std::endl;
	// Write that string to the custom leves data file
	std::ofstream fileOut;
	fileOut.open("LevelDataCustom.txt", std::ios_base::app);
	if (fileOut.is_open())
	{
		fileOut << levelString.str();
		fileOut.close();
	}
	else
	{
		std::cout << "Couldn't open file for writing custom level to!" << std::endl;
	}

	std::cout << "Level saved!" << std::endl;
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
