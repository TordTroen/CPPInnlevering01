#pragma once
#include <vector>
#include <memory>
#include <string>
#include "Component.h"

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
	int GetWindowWidth()                   const { return windowWidth; }
	int GetWindowHeight()				   const { return windowHeight; }
	float GetCenterXPosition(float width)  const;
	float GetCenterYPosition(float height) const;
	void SetGameState(GameState newState) { gameState = newState; }
	GameState GetGameState()			   const { return gameState; }

	void Update();
	GameObject* CreateObject();
	GameObject* CreateObject(std::string tag);
	GameObject* CreateObject(std::vector<Component*> components, std::string tag = NULL);

	/* Takes a reference to a GameObject pointer and deletes that gameobject before setting the pointer to NULL. */
	void DeleteGameObject(GameObject** go);

	/* Returns a reference to the first GameObject found with the specified tag. */
	GameObject* FindGameObjectByTag(std::string tag);

private:
	std::vector<std::unique_ptr<GameObject>> allGameObjects;
	int windowWidth  = 700;
	int windowHeight = 700;
	GameState gameState;
};

