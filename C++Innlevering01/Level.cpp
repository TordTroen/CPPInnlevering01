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
	: _startYPosition(startYPosition), _levelText(levelText)
{
	Theme::Theme(GameManager::GetInstance().GetWindowWidth(), GameManager::GetInstance().GetWindowHeight(), 0);
	//_levelText = levelText;
	// TODO read the level text and insert it into the level vertices
}

Level::~Level()
{
}

void Level::LoadBricks()
{
	Vector2D startPos = Vector2D(0, _startYPosition);
	int brickWidthCount = 0;
	for (char& c : _levelText)
	{
		if (c == '|')
		{
			break;
		}
		brickWidthCount++;
	}
	float levelWidth = (brickWidthCount * LevelBrick::BrickWidth);
	startPos.X = GameManager::GetInstance().GetWindowWidth() / 2 - levelWidth / 2;
	Vector2D curPos = startPos;

	for (char& c : _levelText)
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
		if (c == '|')
		{
			curPos.Y += LevelBrick::BrickHeight;
			curPos.X = startPos.X;
		}
		else
		{
			if (brickType != BrickType::BrickEmpty)
			{
				GameObject* brick = GameObjectManager::GetInstance().CreateObject();
				brickObjects.emplace_back(brick);
				brick->AddComponent(new LevelBrick(curPos, brickType, brickScore, brickHealth, (brickType == BrickType::BrickIndestructible)));
			}
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
