#include "Level.h"
#include "Vector2D.h"
#include "LevelBrick.h"
#include "GameObjectManager.h"
#include <iostream>
Level::Level(std::string levelText)
{
	_levelText = levelText;
	// TODO read the level text and insert it into the level vertices
}

Level::~Level()
{
}

void Level::LoadBricks()
{
	Vector2D startPos = Vector2D(20, 20);
	Vector2D curPos = startPos;

	for (char& c : _levelText)
	{
		BrickType brickType = static_cast<BrickType>(c - '0');
		if (c == '\n')
		{
			curPos.Y += LevelBrick::BrickHeight;
			curPos.X = startPos.X;
		}
		else
		{
			if (brickType != Empty)
			{
				int brickHealth = static_cast<int>(brickType);
				GameObject* brick = GameObjectManager::GetInstance().CreateObject();
				brick->AddComponent(new LevelBrick(curPos, brickType, brickHealth, false));
			}
			curPos.X += LevelBrick::BrickWidth;
		}
	}
}
