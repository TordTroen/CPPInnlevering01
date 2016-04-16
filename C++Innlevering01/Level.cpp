#include "Level.h"
#include "Vector2D.h"
#include "LevelBrick.h"
#include "GameObjectManager.h"
#include "Tags.h"
#include "GameManager.h"
#include "Theme.h"

using namespace std;

Level::Level(std::string levelText)
	: levelId(0)
{
	Theme::Theme(GameManager::GetInstance().GetWindowWidth(), GameManager::GetInstance().GetWindowHeight(), 0);

	SetLevelText(levelText);
}

Level::~Level()
{
}

void Level::LoadBricks()
{
	// Figure out the startposition for the first brick
	Vector2D startPos	= Vector2D(0, 0);

	// Calculate the width of the whole level to be able to place it in the center
	int brickWidthCount = 0;
	brickWidthCount		= levelText.find('|');
	float levelWidth	= (brickWidthCount * LevelBrick::BrickWidth);
	startPos.X			= GameManager::GetInstance().GetWindowWidth() / 2 - levelWidth / 2;

	Vector2D curPos = startPos;
	int numberOfBricks = 0;

	for (char& c : levelText)
	{
		// Figure out the brick parameters
		int brickHealth = 1;
		int brickScore  = 0;
		int brickId		= c - '0';
		BrickType brickType = static_cast<BrickType>(brickId);

		// Make the brick
		if (c == '|') // If end of line
		{
			// Increase y pos, and reset x pos to starting pos
			curPos.Y += LevelBrick::BrickHeight;
			curPos.X = startPos.X;
		}
		else
		{
			// Spawn a brick if the bricktype isn't empty
			if (brickType != BrickType::BrickEmpty)
			{
				GameObject* brick = GameObjectManager::GetInstance().CreateObject(Tags::Brick);
				brickObjects.emplace_back(brick);
				LevelBrick* levelBrick = dynamic_cast<LevelBrick*>(brick->AddComponent(new LevelBrick(curPos, brickType, brickScore, brickHealth, (brickType == BrickType::BrickIndestructible))));
				
				if (brickType != BrickType::BrickIndestructible) {

					numberOfBricks += levelBrick->GetHealth();
				}
			}
			// Increase the x pos by the brickwidth
			curPos.X += LevelBrick::BrickWidth;
		}
	}
	// Updates the number of bricks at current level.
	if (player == NULL)
	{
		player = GameObjectManager::GetInstance().FindGameObjectByTag(Tags::Paddle)->GetComponent<Player>();
	}
	player->SetBricksForCurrentLevel(numberOfBricks - 1);
}

void Level::DeleteBricks()
{
	if (brickObjects.size() > 0)
	{
		for (auto it : brickObjects)
		{
			it->Destroy();
		}
		brickObjects.clear();
	}
}

void Level::SetLevelText(std::string levelText)
{
	this->levelText = levelText;

	// Remove name from levelText
	int nameEndPos = levelText.find('|');
	levelName = levelText.substr(0, nameEndPos);
	this->levelText.erase(0, nameEndPos + 1);

	DeleteBricks();
}

