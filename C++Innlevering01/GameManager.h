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
	int GetWindowWidth() const { return _windowWidth; }
	int GetWindowHeight() const { return _windowHeight; }
	float GetCenterXPosition(float width) const;
	float GetGravity() const { return _gravity; }
	void SetGameState(GameState newState) { _gameState = newState; OnGameStateChanged(); }
	GameState GetGameState() const { return _gameState; }
	void SetPlayerController(PlayerController* pc) { playerController = pc; } // Debug only
private:
	PlayerController* playerController; // Debug
	void OnGameStateChanged();
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

