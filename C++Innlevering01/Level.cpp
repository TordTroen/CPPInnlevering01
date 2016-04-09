#include "Level.h"
#include "Vector2D.h"
#include "LevelBrick.h"
#include "GameObjectManager.h"
#include <iostream>
#include "GameManager.h"
#include "Theme.h"
#include "Drawable.h"
#include "Rect.h"
#include "SDLWrapper.h"
#include "Tags.h"

Level::Level(std::string levelText, float startYPosition)
	: startYPosition(startYPosition), levelText(levelText)
{
	Theme::Theme(GameManager::GetInstance().GetWindowWidth(), GameManager::GetInstance().GetWindowHeight(), 0);

	// Remove name from levelText
	int nameEndPos = levelText.find('|');
	levelName = levelText.substr(0, nameEndPos);
	//levelText = levelText.substr(nameEndPos + 1, levelText.length());
	this->levelText.erase(0, nameEndPos + 1);
	std::cout << "Name: {" << levelName << "}, level: {" << levelText  << "}" << std::endl;
}

Level::~Level()
{
}

void Level::LoadBricks()
{
	Vector2D startPos = Vector2D(0, startYPosition);
	int brickWidthCount = 0;

	//for (char& c : levelText)
	//{
	//	if (c == '|')
	//	{
	//		break;
	//	}
	//	brickWidthCount++;
	//}
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
		if (brickId == 2 || brickId == 3)
		{
			brickHealth = brickId;
			brickId = 1;
		}
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
				GameObject* brick = GameObjectManager::GetInstance().CreateObject();
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
