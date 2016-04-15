#pragma once
#include "PlayerController.h"
#include <memory>
enum class GameState
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
	int GetWindowWidth()                   const { return windowWidth; }
	int GetWindowHeight()				   const { return windowHeight; }
	float GetCenterXPosition(float width)  const;
	float GetCenterYPosition(float height) const;
	void SetGameState(GameState newState) { gameState = newState; }
	GameState GetGameState()			   const { return gameState; }

private:
	PlayerController* playerController;
	int windowWidth  = 700;
	int windowHeight = 700;
	GameState gameState;

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

