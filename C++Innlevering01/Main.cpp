//Using SDL, SDL_image, standard IO, and strings
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include "SDLWrapper.h"
#include "InputManager.h"
#include "GameObject.h"
#include "Transform.h"
#include "ImageRenderer.h"
#include "GameManager.h"
#include "Time.h"
#include "BoxCollider.h"
#include "CollisionManager.h"
#include "BallMovement.h"
#include "Tags.h"
#include "GUIManager.h"
#include "BoardManager.h"
#include "Level.h"
#include "PaddleMovement.h"
#include "Player.h"

using namespace std;

int main(int argc, char** argv)
{
	GameManager gameManager;
	BoardManager boardManager(&gameManager);

	InputManager::GetInstance().Init();			// Keeps track of keyboard and mouse input
	Time::Init();								// Keeps track of ellapsed time between frames
	//GUIManager	  gui;							// Keeps track of activating visual elements like menu, ball, paddle and boxes
	//BoardManager  board;						// Keeps track of the board and it's level.
	float		  paddleSpeed = 10;				// The speed of the paddle
	float		  ballSpeed = 5;				// The speed of the ball
	int			  score = 0;				// The number of boxes that is shot down


	// Initialize SDL components for background, window, sizes, etc. that gameobject, gameloop, etc are dependant on
	if (SDLWrapper::GetInstance().InitializeWindow("Breakout", gameManager.GetWindowWidth(),
		gameManager.GetWindowHeight(), Color(0, 200, 200)) == 0)
	{
		Rect paddleStartRect = Rect(gameManager.GetCenterXPosition(200), gameManager.GetWindowHeight() - 100, 150, 15);
		Rect ballStartRect = Rect(gameManager.GetCenterXPosition(18), paddleStartRect.y - 50, 18, 18);
		GUIManager::GetInstance().Init(&gameManager, &boardManager);

		// Make the paddle object. Both the visual paddle and the positioning of the paddle. 
		GameObject* paddleObj = gameManager.CreateObject(Tags::Paddle);
		paddleObj->AddComponent(new ImageRenderer("WhiteTexture.png", Color(100, 100, 255)));
		paddleObj->AddComponent(new BoxCollider());
		paddleObj->AddComponent(new PaddleMovement(paddleStartRect, paddleSpeed));
		paddleObj->AddComponent(new Player());

		// Make the ball object. Both the visual ball and the positioning of the ball. 
		GameObject* ballObj = gameManager.CreateObject(Tags::Ball);
		ballObj->AddComponent(new ImageRenderer("Ball.png", Color(100, 150, 200)));
		ballObj->AddComponent(new BoxCollider(false));
		BallMovement* ballMove = dynamic_cast<BallMovement*>(ballObj->AddComponent(new BallMovement(Vector2D(0.5, -1), ballStartRect, ballSpeed)));
		ballObj->GetTransform()->SetRect(Rect(200, 200, 20, 20));

		// Initialize stuff that uses the paddle and ball
		boardManager.InitializeBoard();
		GUIManager::GetInstance().SetupMenus();

		GameState gameState = GameState::MainMenu;

		//	The game loop
		while (gameState != GameState::Exit)
		{
			gameState = gameManager.GetGameState(); // Holds which state the game is in: MainMenu, Paused, InGame, Exit

			//// Update everything that needs to be updated every frame ////
			InputManager::GetInstance().Update();
			gameManager.Update();
			Time::Update();
			CollisionManager::Update();

			//	Exit program if user pushes escape
			if (InputManager::GetInstance().GetKeyDown(SDL_SCANCODE_ESCAPE))
			{
				if (gameState == GameState::InGame)
				{
					GUIManager::GetInstance().GetGUIEventHandler()->OnEndLevel();
					GUIManager::GetInstance().SetHUDMenuActive(false);
					GUIManager::GetInstance().SetGameOverMenuActive(true);
				}
				else
				{
					break;
				}
			}

			//// Rendering ////
			SDLWrapper::GetInstance().RenderImages(true);
		}
	}
	return 0;
}
