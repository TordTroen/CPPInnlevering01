#pragma once

enum GameState
{
	MainMenu,
	InGame,
	Exit
};

class GameManager
{
public:
	int GetWindowWidth() const { return _windowWidth; }
	int GetWindowHeight() const { return _windowHeight; }
	float GetCenterXPosition(float width) const;
	float GetGravity() const { return _gravity; }
	void SetGameState(GameState newState) { _gameState = newState; }
	GameState GetGameState() const { return _gameState; }
private:
	int _windowWidth = 700;
	int _windowHeight = 700;
	float _gravity = -9.81f;
	GameState _gameState;

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

