#include <iostream>
#include "SDLWrapper.h"
#include "InputManager.h"
#include "GameObject.h"
#include "Transform.h"
#include "GameObjectManager.h"
#include "ImageRenderer.h"
#include "GameManager.h"
#include "Time.h"
#include "GUIMenu.h"
#include "BoxCollider.h"
#include "CollisionManager.h"
#include "BallMovement.h"
#include "Tags.h"
#include "GUIManager.h"
#include "LevelBrick.h"
#include "BoardManager.h"
#include "Level.h"
#include "PaddleMovement.h"
#include "PlayerController.h"

using namespace std;

int main(int argc, char** argv)
{
	InputManager::GetInstance().Init();			// Keeps track of keyboard and mouse input
	Time time;									// Keeps track of ellapsed time between frames
	GUIManager gui;								// Keeps track of activating visual elements like menu, ball, paddle and boxes
	BoardManager board;							// Keeps track of the board and it's level.
	float paddleSpeed = 1000;					// The speed of the paddle
	float ballSpeed = 0.25;						// The speed of the ball
	int score = 0;								// The number of boxes that is shot down

	GameManager::GetInstance().SetGameState(MainMenu);	

	// Initialize SDL components for background, window, sizes, etc. that gameobject, gameloop, etc are dependant on
	if (SDLWrapper::GetInstance().InitializeWindow("Breakout", GameManager::GetInstance().GetWindowWidth(),
		GameManager::GetInstance().GetWindowHeight(), Color(0, 200, 200)) == 0)
	{


		Rect rect = Rect(0, 0, GameManager::GetInstance().GetWindowWidth(), GameManager::GetInstance().GetWindowHeight());
		SDLWrapper::GetInstance().CreateImage("heaven.jpg", rect, true);


		// Holds start position, number of bricks and name of level.
		// Parameter holds 1 digit for each brick - each number has different coloring, 1: blue, 2: black
		Level* level = new Level("3333333333\n2222222222\n1111111111", 90); 
		board.LoadLevel(level);

		gui.SetupMenus();

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
		PlayerController* playerController = dynamic_cast<PlayerController*>(paddleObj->AddComponent(new PlayerController()));
		playerController->Stop();

		// Make the walls
		GameObject* leftWall = GameObjectManager::GetInstance().CreateObject({ new ImageRenderer("WhiteTexture.png"), new BoxCollider() } , Tags::WallLeft);
		GameObject* rightWall = GameObjectManager::GetInstance().CreateObject({ new ImageRenderer("WhiteTexture.png"), new BoxCollider() }, Tags::WallRight);
		GameObject* topWall = GameObjectManager::GetInstance().CreateObject({ new ImageRenderer("WhiteTexture.png"), new BoxCollider() }, Tags::WallTop);
		GameObject* bottomWall = GameObjectManager::GetInstance().CreateObject({ new ImageRenderer("WhiteTexture.png"), new BoxCollider() }, Tags::WallBottom);
		
		float inset		= 100;	// Holds the padding between size window and game walls, 0 is no padding - 100 is some padding, etc..			
		float wallDepth = 1;	// Holds the thickness of the walls
		float scw = GameManager::GetInstance().GetWindowWidth();
		float sch = GameManager::GetInstance().GetWindowHeight();
		leftWall->GetTransform()->SetRect(Rect(inset - wallDepth, 0, wallDepth, sch));
		rightWall->GetTransform()->SetRect(Rect(scw - inset, 0, wallDepth, sch));
		topWall->GetTransform()->SetRect(Rect(0, inset - wallDepth, scw, wallDepth));
		bottomWall->GetTransform()->SetRect(Rect(0, sch - inset, scw, wallDepth));

		
		GameState gameState = MainMenu; // Sets the positioning data. x,y,w,h, position, gravity

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
					gui.UpdateScoreText(playerController->GetScore());
				}
			}
			
			//// Render ////
			SDLWrapper::GetInstance().RenderImages(true);
		}
	}

	return 0;
}
