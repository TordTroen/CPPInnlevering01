#include "BoardManager.h"
#include <memory>
#include <fstream>
#include "PError.h"
#include "GameObject.h"
#include "ImageRenderer.h"
#include "GameObjectManager.h"
#include "BoxCollider.h"
#include "Tags.h"
#include "GameManager.h"
#include "GUIManager.h"
#include "Transform.h"

const int BoardManager::CustomLevelCount = 3;

BoardManager::~BoardManager()
{
}

void BoardManager::InitializeBoard()
{
	standardLevelCount = 0;

	ImportAllLevels();

	// Set current level to the first level
	SetCurrentLevel(0);

	// Setup the walls at the screenedges
	GameObject* leftWall   = GameObjectManager::GetInstance().CreateObject({ new ImageRenderer("WhiteTexture.png"), new BoxCollider() }, Tags::WallLeft);
	GameObject* rightWall  = GameObjectManager::GetInstance().CreateObject({ new ImageRenderer("WhiteTexture.png"), new BoxCollider() }, Tags::WallRight);
	GameObject* topWall    = GameObjectManager::GetInstance().CreateObject({ new ImageRenderer("WhiteTexture.png"), new BoxCollider() }, Tags::WallTop);
	GameObject* bottomWall = GameObjectManager::GetInstance().CreateObject({ new ImageRenderer("WhiteTexture.png"), new BoxCollider() }, Tags::WallBottom);

	float inset		= 0;	// Holds the padding between size window and game walls, 0 is no padding - 100 is some padding, etc..			
	float wallDepth = 50;	// Holds the thickness of the walls
	float scw = GameManager::GetInstance().GetWindowWidth();
	float sch = GameManager::GetInstance().GetWindowHeight();
	leftWall->GetTransform()->SetRect(Rect(inset - wallDepth, 0, wallDepth, sch));
	rightWall->GetTransform()->SetRect(Rect(scw - inset, 0, wallDepth, sch));
	topWall->GetTransform()->SetRect(Rect(0, inset - wallDepth, scw, wallDepth));
	bottomWall->GetTransform()->SetRect(Rect(0, sch - inset, scw, wallDepth));

	// Get the references to the ball and paddle
	ballMovement   = GameObjectManager::GetInstance().FindGameObjectByTag(Tags::Ball)->GetComponent<BallMovement>();
	paddleMovement = GameObjectManager::GetInstance().FindGameObjectByTag(Tags::Paddle)->GetComponent<PaddleMovement>();
	player		   = GameObjectManager::GetInstance().FindGameObjectByTag(Tags::Paddle)->GetComponent<Player>();

	ClearBoard();
}

void BoardManager::ResetBoard()
{
	// Reset current level, ball and paddle
	curLevel->DeleteBricks();
	ballMovement->Reset();
	paddleMovement->Reset();
	player->Reset();
}

void BoardManager::ClearBoard()
{
	curLevel->DeleteBricks();
	ballMovement->GetGameObject()->SetActive(false);
	paddleMovement->GetGameObject()->SetActive(false);
}

Level* BoardManager::GetCurrentLevel() const
{
	return curLevel;
}

void BoardManager::SetCurrentLevel(int levelId)
{
	curLevelId = levelId;

	// Make sure the index is valid
	if (curLevelId > allLevels.size() - 1)
	{
		curLevelId = 0;
		std::cout << "Can't load the current level, loading level 1 instead." << std::endl;
	}

	// Destroy old level
	if (curLevel != NULL)
	{
		curLevel->DeleteBricks();
	}

	// Set new level
	curLevel = allLevels[curLevelId];
}

void BoardManager::SetCurrentLevelToNextLevel()
{
	SetCurrentLevel(curLevelId + 1);
}

void BoardManager::AddLevel(Level * level)
{
	allLevels.emplace_back(level);
}

void BoardManager::StartLevel()
{
	GameManager::GetInstance().SetGameState(GameState::InGame);
	ResetBoard();
	LoadCurrentLevel(); // TODO load next level OR selected level from level select
}

void BoardManager::EndGame()
{
	GUIManager::GetInstance().UpdateEndScoreText(player->GetHighscore());
	GameManager::GetInstance().SetGameState(GameState::MainMenu);
	ClearBoard();
}

std::vector<std::string> BoardManager::GetLevelNames() const
{
	std::vector<std::string> names;
	for (auto it : allLevels)
	{
		names.emplace_back(it->GetLevelName());
	}
	return names;
}

void BoardManager::ImportAllLevels()
{
	allLevels.erase(allLevels.begin(), allLevels.end());

	// Import all the levels
	ImportLevelData("LevelDataStandard.txt");
	standardLevelCount = allLevels.size();

	ImportLevelData("LevelDataCustom.txt");
}

void BoardManager::SaveLevel(int index, std::string levelText)
{
	index += standardLevelCount;
	if (index < allLevels.size())
	{
		allLevels[index]->SetLevelText(levelText);
	}

	// Write that string to the custom leves data file
	std::ofstream fileOut;
	fileOut.open("LevelDataCustom.txt", std::ios_base::trunc);

	if (fileOut.is_open())
	{
		for (int i = 0; i < CustomLevelCount; i++)
		{
			// TODO Properly handle error here, and make sure the LevelDataCustom.txt always has three levels
			if (i + standardLevelCount > allLevels.size() - 1)
			{
				std::cout << "ERROR: Can't save level. Please make sure the LevelDataCustom.txt has three levels." << std::endl;
			}
			fileOut << allLevels[i+standardLevelCount]->GetLevelString() << "\n";
		}
		fileOut.close();
	}
	else
	{
		std::cout << "Couldn't open file for writing custom level to!" << std::endl;
	}

	std::cout << "Level saved!" << std::endl;
}

void BoardManager::LoadCurrentLevel()
{
	if (curLevel != NULL)
	{
		curLevel->LoadBricks();
	}
	else
	{
		PError("Couldn't load a level, because no curLevel is assigned.");
	}
}

void BoardManager::ImportLevelData(std::string filename)
{
	std::string line;

	// Open a stream to the file
	std::ifstream levelDataFile(filename);

	if (levelDataFile.is_open()) // Check if the file is open
	{
		while (!levelDataFile.eof()) // Read until eof
		{
			// Get each line and make a new level with that line
			getline(levelDataFile, line);
			
			if (line.empty()) continue; // Skip this line if it is empty
			// TODO Somehow validate to make sure the leveltext string is a valid level??

			Level* level = new Level(line); 
			AddLevel(level);
		}
	}
	else
	{
		std::cout << "Couldn't open the level data file when trying to import the leveldata!" << std::endl;
	}
}
