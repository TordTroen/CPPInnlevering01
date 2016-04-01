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

using namespace std;

int main(int argc, char** argv)
{
	InputManager::GetInstance().Init();
	Time time;
	GUIManager gui;
	BoardManager board;
	float paddleSpeed = 1;
	float ballSpeed = 0.25;
	int score = 0;
	GameManager::GetInstance().SetGameState(MainMenu);

	// Initialize stuff that gameobject, gameloop, etc are dependant on
	if (SDLWrapper::GetInstance().InitializeWindow("Breakout", GameManager::GetInstance().GetWindowWidth(),
		GameManager::GetInstance().GetWindowHeight(), Color(200, 200, 200)) == 0)
	{
		gui.SetupMenus();




		// Level test
		//GameObject* brick = GameObjectManager::GetInstance().CreateObject();
		//brick->AddComponent(new LevelBrick(Vector2D(100, 100), Yellow, 1, false));
		Level* level = new Level("01100110\n01231230\n21211212");
		board.LoadLevel(level);


		// Make the ball
		GameObject* ballObj = GameObjectManager::GetInstance().CreateObject(Tags::Ball);
		ballObj->AddComponent(new ImageRenderer("WhiteTexture.png", Color(100, 150, 200)));
		ballObj->AddComponent(new BoxCollider(false));
		ballObj->AddComponent(new BallMovement(Vector2D(2, 1), ballSpeed));
		ballObj->GetTransform()->SetRect(Rect(200, 200, 20, 20));

		// Make the paddle
		GameObject* paddleObj = GameObjectManager::GetInstance().CreateObject(Tags::Paddle);
		paddleObj->AddComponent(new ImageRenderer("WhiteTexture.png", Color(100, 100, 255)));
		paddleObj->AddComponent(new BoxCollider());
		Rect paddleStartRect = Rect(GameManager::GetInstance().GetCenterXPosition(200), GameManager::GetInstance().GetWindowHeight() - 100, 150, 15);
		paddleObj->GetTransform()->SetRect(paddleStartRect);

		// Make the walls
		GameObject* leftWall = GameObjectManager::GetInstance().CreateObject({ new ImageRenderer("WhiteTexture.png"), new BoxCollider() } , Tags::WallLeft);
		GameObject* rightWall = GameObjectManager::GetInstance().CreateObject({ new ImageRenderer("WhiteTexture.png"), new BoxCollider() }, Tags::WallRight);
		GameObject* topWall = GameObjectManager::GetInstance().CreateObject({ new ImageRenderer("WhiteTexture.png"), new BoxCollider() }, Tags::WallTop);
		GameObject* bottomWall = GameObjectManager::GetInstance().CreateObject({ new ImageRenderer("WhiteTexture.png"), new BoxCollider() }, Tags::WallBottom);
		float inset = 0;
		float wallDepth = 25;
		float scw = GameManager::GetInstance().GetWindowWidth();
		float sch = GameManager::GetInstance().GetWindowHeight();
		leftWall->GetTransform()->SetRect(Rect(inset - wallDepth, 0, wallDepth, sch));
		rightWall->GetTransform()->SetRect(Rect(scw - inset, 0, wallDepth, sch));
		topWall->GetTransform()->SetRect(Rect(0, inset - wallDepth, scw, wallDepth));
		bottomWall->GetTransform()->SetRect(Rect(0, sch - inset, scw, wallDepth));

		// Game loop
		GameState gameState = MainMenu;
		while (gameState != Exit)
		{
			gameState = GameManager::GetInstance().GetGameState();

			//// Update everything that needs to be updated every frame ////
			GameObjectManager::GetInstance().Update();
			InputManager::GetInstance().Update();
			time.Update();
			CollisionManager::Update();

			//// Logic ////
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
					score++;
					gui.UpdateScoreText(score);
				}
				// DEBUG

				Vector2D velocity = Vector2D(InputManager::GetInstance().GetAxis(SDL_SCANCODE_RIGHT, SDL_SCANCODE_LEFT), InputManager::GetInstance().GetAxis(SDL_SCANCODE_DOWN, SDL_SCANCODE_UP));
				paddleObj->GetTransform()->Translate(velocity * paddleSpeed, true);
			}
			
			//// Render ////
			SDLWrapper::GetInstance().RenderImages(true);
		}
	}

	return 0;
}
