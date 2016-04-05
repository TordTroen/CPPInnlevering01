#pragma once

#include "Level.h"
#include "Vector2D.h"
#include "LevelBrick.h"
#include "GameObjectManager.h"
#include <iostream>
#include "GameManager.h"

#include "Drawable.h"
#include "Rect.h"
#include "SDLWrapper.h"
#include <String>

class Theme {
public:
	Theme(int height, int width, int level);
	Theme() : Theme{ 0, 0, 0 } {}
	~Theme() {}

	void Init();

private:
	int _width;
	int _height;
	int _level;
	const std::string _images[6]{ "wonderland-2.png", "sky.png", "brick-wall-colored.png", "wonderland.png", "brick-wall-gray.png", "hell-02.png" };
};

