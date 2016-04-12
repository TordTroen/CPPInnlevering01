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

void SaveEditor()
{
	
}

void ClearEditor()
{
	
}

LevelEditorMenu::LevelEditorMenu(GUIMenu* levelEditorMenu, GUIMenu* previousMenu)
	: levelName("Unnamed"), levelEditorMenu(levelEditorMenu), previousMenu(previousMenu)
{
}

LevelEditorMenu::~LevelEditorMenu()
{
}

void LevelEditorMenu::Init()
{
	for (int i = 0; i < columns; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			//GUILevelEditorButton* btn = new GUILevelEditorButton(Color(0, 0, 0), Color(25, 25, 25), Color(50, 50, 50), Rect(i * LevelBrick::BrickWidth, j * LevelBrick::BrickHeight, LevelBrick::BrickWidth, LevelBrick::BrickHeight), NULL, i + j);
			GameObject* btnObj = GameObjectManager::GetInstance().CreateObject();
			GUILevelEditorButton* btn = dynamic_cast<GUILevelEditorButton*>(btnObj->AddComponent(new GUILevelEditorButton(Color(0, 0, 0), Color(25, 25, 25), Color(50, 50, 50), Rect(i * LevelBrick::BrickWidth, j * LevelBrick::BrickHeight, LevelBrick::BrickWidth, LevelBrick::BrickHeight), i + j)));
			buttons.emplace_back(btn);
			levelEditorMenu->AddElement(btn);
		}
	}

	levelEditorMenu->AddElement(new GUIButton("Save", Color(200, 255, 255), Color(0, 0, 0), Color(25, 25, 25), Color(50, 50, 50), Rect(700 - 200, 500, 100, 100), 8, SaveEditor));
	levelEditorMenu->AddElement(new GUIButton("Clear", Color(200, 255, 255), Color(0, 0, 0), Color(25, 25, 25), Color(50, 50, 50), Rect(700 - 200, 570, 100, 100), 8, ClearEditor));
	levelEditorMenu->AddElement(new GUIButton("Main menu", Color(200, 255, 255), Color(0, 0, 0), Color(25, 25, 25), Color(50, 50, 50), Rect(700 - 200, 640, 100, 100), 8, levelEditorMenu, previousMenu));
	levelEditorToggleGroup = dynamic_cast<GUIToggleGroup*>(GetGameObject()->AddComponent(new GUIToggleGroup()));
	for (int i = 0; i < 6; i++)
	{
		Color toolNormalColor = LevelBrick::GetBrickColor(static_cast<BrickType>(i));
		Color toolHoverColor = toolNormalColor.Tinted(1.1);
		Color toolDownColor = toolNormalColor.Shaded(0.9);
		levelEditorMenu->AddElement(new GUIToggle(" ", Color(200, 255, 255), toolNormalColor, toolDownColor, toolHoverColor, Color(0, 200, 200), Rect(16 + i * (LevelBrick::BrickWidth + 32), 700 - LevelBrick::BrickHeight - 16, LevelBrick::BrickWidth, LevelBrick::BrickHeight), 0, levelEditorToggleGroup, false));
	}
	Clear();
}

void LevelEditorMenu::Save()
{
	// Create a string based on the name and what index all the buttons have
	std::ostringstream levelString;
	levelString << levelName;
	levelString << "|";
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			levelString << buttons[i+j]->GetBrickId();
		}
		if (i < rows - 1) levelString << "|";
	}
	levelString << "\n";

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
