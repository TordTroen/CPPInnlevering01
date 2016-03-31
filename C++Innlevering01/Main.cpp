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

using namespace std;

GUIMenu* menu;
void ClickTest()
{
	cout << "ClickTest()" << endl;
	menu->SetActive(false);
}

int main(int argc, char** argv)
{
	InputManager::GetInstance().Init();
	Time time;
	GUIManager gui;
	float paddleSpeed = 1;
	float ballSpeed = 0.5;
	int score = 0;
	GameManager::GetInstance().SetGameState(MainMenu);

	// Initialize stuff that gameobject, gameloop, etc are dependant on
	if (SDLWrapper::GetInstance().InitializeWindow("Breakout", GameManager::GetInstance().GetWindowWidth(),
		GameManager::GetInstance().GetWindowHeight(), Color(200, 200, 200)) == 0)
	{
		gui.SetupMenus();
		//GameObject* menuObj = GameObjectManager::GetInstance().CreateObject();
		//menu = dynamic_cast<GUIMenu*>(menuObj->AddComponent(new GUIMenu({
		//	new GUIText("Main menu", Color(0, 0, 0), Rect(10, 130, 100, 50)),
		//	new GUIButton("Button with padding", Color(40, 40, 40), Color(50, 50, 200), Color(255, 255, 255), Color(50, 140, 255), Rect(10, 200, 100, 50), 10, ClickTest),
		//	new GUIButton("Close", Color(40, 40, 40), Color(50, 50, 200), Color(255, 255, 255), Color(60, 200, 10), Rect(10, 250, 100, 50), 0, ClickTest)
		//})));

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
		Rect paddleStartPos = Rect(GameManager::GetInstance().GetCenterXPosition(200), GameManager::GetInstance().GetWindowHeight() - 100, 200, 50);
		paddleObj->GetTransform()->SetRect(paddleStartPos);

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
		GameState gameState = MainMenu;
		// Game loop
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
