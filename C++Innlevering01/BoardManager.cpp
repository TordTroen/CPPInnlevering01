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
#include "Transform.h"

BoardManager::~BoardManager()
{
}

void BoardManager::InitializeBoard()
{
	// Import all the levels
	ImportLevelData();

	SetCurrentLevel(0);

	// Setup the walls at the screenedges
	GameObject* leftWall = GameObjectManager::GetInstance().CreateObject({ new ImageRenderer("WhiteTexture.png"), new BoxCollider() }, Tags::WallLeft);
	GameObject* rightWall = GameObjectManager::GetInstance().CreateObject({ new ImageRenderer("WhiteTexture.png"), new BoxCollider() }, Tags::WallRight);
	GameObject* topWall = GameObjectManager::GetInstance().CreateObject({ new ImageRenderer("WhiteTexture.png"), new BoxCollider() }, Tags::WallTop);
	GameObject* bottomWall = GameObjectManager::GetInstance().CreateObject({ new ImageRenderer("WhiteTexture.png"), new BoxCollider() }, Tags::WallBottom);
	BoxCollider* col = bottomWall->GetComponent<BoxCollider>();

	float inset = 0;	// Holds the padding between size window and game walls, 0 is no padding - 100 is some padding, etc..			
	float wallDepth = 50;	// Holds the thickness of the walls
	float scw = GameManager::GetInstance().GetWindowWidth();
	float sch = GameManager::GetInstance().GetWindowHeight();
	leftWall->GetTransform()->SetRect(Rect(inset - wallDepth, 0, wallDepth, sch));
	rightWall->GetTransform()->SetRect(Rect(scw - inset, 0, wallDepth, sch));
	topWall->GetTransform()->SetRect(Rect(0, inset - wallDepth, scw, wallDepth));
	bottomWall->GetTransform()->SetRect(Rect(0, sch - inset, scw, wallDepth));
}

void BoardManager::ResetBoard()
{
	// TODO Reset paddle
	// TODO Reset ball
	// TODO Reset level
}

void BoardManager::SetCurrentLevel(int levelId)
{
	// TODO Destroy old level
	if (curLevel != NULL)
	{

	}

	// Set new level
	curLevel = allLevels[levelId];
	//LoadCurrentLevel();
}

void BoardManager::AddLevel(Level * level)
{
	allLevels.emplace_back(level);
	std::cout << level->GetLevelText() << std::endl;
}

void BoardManager::OnStartLevel()
{
	ResetBoard();
	// TODO Activate player/ball
	LoadCurrentLevel(); // TODO load next level OR selected level from level select
}

void BoardManager::OnGameOver()
{
	// Open gameovermenu
	// set gamestate
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

void BoardManager::ImportLevelData()
{
	std::string line;

	// Open a stream to the file
	std::ifstream levelDataFile("LevelData.txt");

	if (levelDataFile.is_open()) // Check if the file is open
	{
		while (!levelDataFile.eof()) // Read until eof
		{
			// Get each line and make a new level with that line
			getline(levelDataFile, line);
			Level* level = new Level(line); // TODO Somehow validate to make sure the leveltext string is a valid level??
			AddLevel(level);
		}
	}
	else
	{
		std::cout << "Couldn't open the level data file when trying to import the leveldata!" << std::endl;
	}
}
