#include "Level.h"
#include "Vector2D.h"
#include "LevelBrick.h"
#include "GameObjectManager.h"
#include <iostream>
#include "GameManager.h"

Level::Level(std::string levelText, float startYPosition)
	: _startYPosition(startYPosition), _levelText(levelText)
{
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
		if (c == '\n')
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
		int brickId = c - '0';
		if (brickId == 2 || brickId == 3)
		{
			brickHealth = brickId;
			brickId = 1;
		}
		BrickType brickType = static_cast<BrickType>(brickId);

		// Make the brick
		if (c == '\n')
		{
			curPos.Y += LevelBrick::BrickHeight;
			curPos.X = startPos.X;
		}
		else
		{
			if (brickType != BrickEmpty)
			{
				GameObject* brick = GameObjectManager::GetInstance().CreateObject();
				brick->AddComponent(new LevelBrick(curPos, brickType, brickHealth, (brickType == BrickIndestructible)));
			}
			curPos.X += LevelBrick::BrickWidth;
		}
	}
}
