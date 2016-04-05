#pragma once
#include "PlayerController.h"
#include <memory>
enum GameState
{
	MainMenu,
	Paused,
	InGame,
	Exit
};

class GameManager
{
public:
	void Init(GameState startState);
	int GetWindowWidth() const { return _windowWidth; }
	int GetWindowHeight() const { return _windowHeight; }
	float GetCenterXPosition(float width) const;
	void SetGameState(GameState newState) { _gameState = newState; OnGameStateChanged(); }
	GameState GetGameState() const { return _gameState; }
private:
	PlayerController* _playerController;
	void OnGameStateChanged();
	int _windowWidth = 700;
	int _windowHeight = 700;
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

