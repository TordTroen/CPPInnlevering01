#include "Level.h"
#include "Vector2D.h"
#include "LevelBrick.h"
#include "GameObjectManager.h"
#include "Tags.h"
#include "GameManager.h"
#include "Theme.h"

Level::Level(std::string levelText)
	: levelId(0), levelText(levelText)
{
	Theme::Theme(GameManager::GetInstance().GetWindowWidth(), GameManager::GetInstance().GetWindowHeight(), 0);

	// Remove name from levelText
	int nameEndPos = levelText.find('|');
	levelName = levelText.substr(0, nameEndPos);
	this->levelText.erase(0, nameEndPos + 1);
}

Level::~Level()
{
	
}

void Level::LoadBricks()
{
	// Figure out the startposition for the first brick
	Vector2D startPos = Vector2D(0, 0);
	// Calculate the width of the whole level to be able to place it in the center
	int brickWidthCount = 0;
	brickWidthCount = levelText.find('|');
	float levelWidth = (brickWidthCount * LevelBrick::BrickWidth);
	startPos.X = GameManager::GetInstance().GetWindowWidth() / 2 - levelWidth / 2;

	Vector2D curPos = startPos;

	for (char& c : levelText)
	{
		// Figure out the brick parameters
		int brickHealth = 1;
		int brickScore = 0;
		int brickId = c - '0';
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
				brick->AddComponent(new LevelBrick(curPos, brickType, brickScore, brickHealth, (brickType == BrickType::BrickIndestructible)));
			}
			
			// Increase the x pos by the brickwidth
			curPos.X += LevelBrick::BrickWidth;
		}
	}
}

void Level::DeleteBricks()
{
	for (auto it : brickObjects)
	{
		it->Destroy();
	}
	brickObjects.clear();
}

int Level::GetBrickCount() const {

	int numberOfActiveBricks = 0;
	for (auto i : brickObjects) {
		if (i->IsActive()) {
			numberOfActiveBricks++;
		}
	}

	return numberOfActiveBricks;
}
