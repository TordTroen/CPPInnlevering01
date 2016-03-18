#pragma once

class GameManager
{
public:
	int GetWindowWidth() const { return _windowWidth; }
	int GetWindowHeight() const { return _windowHeight; }
	float GetGravity() const { return _gravity; }
private:
	int _windowWidth = 700;
	int _windowHeight = 700;
	float _gravity = -9.81f;

// Singleton stuff
public:
	static GameManager& GetInstance()
	{
		static GameManager instance;
		return instance;
	}
private:
	GameManager() {};
	GameManager(GameManager const&);
	void operator=(GameManager const&);
};

