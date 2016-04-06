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
#include "GameObjectManager.h"
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
#include "PlayerController.h"
#include "Player.h"

using namespace std;

int main(int argc, char** argv)
{

	InputManager::GetInstance().Init();			// Keeps track of keyboard and mouse input
	Time		  time;							// Keeps track of ellapsed time between frames
	//GUIManager	  gui;							// Keeps track of activating visual elements like menu, ball, paddle and boxes
	//BoardManager  board;						// Keeps track of the board and it's level.
	float		  paddleSpeed = 1000;			// The speed of the paddle
	float		  ballSpeed   = 0.25;			// The speed of the ball
	int			  score		  = 0;				// The number of boxes that is shot down
	

	// Initialize SDL components for background, window, sizes, etc. that gameobject, gameloop, etc are dependant on
	if (SDLWrapper::GetInstance().InitializeWindow("Breakout", GameManager::GetInstance().GetWindowWidth(),
		GameManager::GetInstance().GetWindowHeight(), Color(0, 200, 200)) == 0)
	{
		//std::string testLevelString = "3333333333\n2222222222\n1111111111";
		//board.AddLevel(new Level(testLevelString));
		//board.SetCurrentLevel(0);
		BoardManager::GetInstance().InitializeBoard();

		// Holds start position, number of bricks and name of level.
		// Parameter holds 1 digit for each brick - each number has different coloring, 1: blue, 2: black
		//Level* level(new Level("3333333333\n2222222222\n1111111111", 90));
		//board.LoadLevel(level);

		GUIManager::GetInstance().SetupMenus();

		// Make the ball object. Both the visual ball and the positioning of the ball. 
		GameObject* ballObj = GameObjectManager::GetInstance().CreateObject(Tags::Ball);
		ballObj->AddComponent(new ImageRenderer("WhiteTexture.png", Color(100, 150, 200)));
		ballObj->AddComponent(new BoxCollider(false));
		ballObj->AddComponent(new BallMovement(Vector2D(2, 1), ballSpeed));
		ballObj->GetTransform()->SetRect(Rect(200, 200, 20, 20));

		// Make the paddle object. Both the visual paddle and the positioning of the paddle. 
		GameObject* paddleObj = GameObjectManager::GetInstance().CreateObject(Tags::Paddle);
		paddleObj->AddComponent(new ImageRenderer("WhiteTexture.png", Color(100, 100, 255)));
		paddleObj->AddComponent(new BoxCollider());
		Rect paddleStartRect = Rect(GameManager::GetInstance().GetCenterXPosition(200), GameManager::GetInstance().GetWindowHeight() - 100, 150, 15);
		paddleObj->GetTransform()->SetRect(paddleStartRect);
		paddleObj->AddComponent(new PaddleMovement());
		paddleObj->AddComponent(new Player());
		PlayerController* playerController = dynamic_cast<PlayerController*>(paddleObj->AddComponent(new PlayerController()));
		playerController->SetStartingLives(3);
		playerController->Stop();

		GameManager::GetInstance().Init(MainMenu);
		GameState gameState = MainMenu; // Sets the positioning data. Has x,y,w,h, position and gravity

		//	The game loop
		while (gameState != Exit)
		{
			gameState = GameManager::GetInstance().GetGameState(); // Holds which state the game is in: MainMenu, Paused, InGame, Exit

			// Update everything that needs to be updated every frame
			GameObjectManager::GetInstance().Update();
			InputManager::GetInstance().Update();
			time.Update();
			CollisionManager::Update();

			//	Exit program if user pushes escape
			if (InputManager::GetInstance().GetKeyDown(SDL_SCANCODE_ESCAPE))
			{
				break;
			}

			if (gameState == InGame)
			{
				// DEBUG
				if (InputManager::GetInstance().GetMouseDown(1))
				{
					cout << "-" << endl;
					playerController->ChangeScore(1);
					GUIManager::GetInstance().UpdateScoreText(playerController->GetScore());
				}
			}
			
			//// Render ////
			SDLWrapper::GetInstance().RenderImages(true);
		}
	}

	return 0;
}
