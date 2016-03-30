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

using namespace std;

GUIMenu* menu;
void ClickTest()
{
	cout << "ClickTest()" << endl;
	menu->SetActive(false);
}

int main(int argc, char** argv)
{
	//GameObjectManager goManager = GameObjectManager(GameManager::GetInstance().GetWindowWidth(),
	//	GameManager::GetInstance().GetWindowHeight());
//	SDLWrapper sdl;
//	InputManager io;
	InputManager::GetInstance().Init();
	Time time;
	float paddleSpeed = 0.8;

	// Initialize stuff that gameobject, gameloop, etc are dependant on
	if (SDLWrapper::GetInstance().InitializeWindow("Breakout", GameManager::GetInstance().GetWindowWidth(),
		GameManager::GetInstance().GetWindowHeight(), Color(200, 200, 200)) == 0)
	{
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
		ballObj->AddComponent(new BallMovement(Vector2D(2, 1), 0.1));
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
		float scw = GameManager::GetInstance().GetWindowWidth();
		float sch = GameManager::GetInstance().GetWindowHeight();
		leftWall->GetTransform()->SetRect(Rect(inset, 0, 1, sch));
		rightWall->GetTransform()->SetRect(Rect(scw - inset, 0, 1, sch));
		topWall->GetTransform()->SetRect(Rect(0, inset, scw, 1));
		bottomWall->GetTransform()->SetRect(Rect(0, sch - inset, scw, 1));
		
		//// Create gameobject here
		//GameObject* player = goManager.CreateObject();
		//player->AddComponent(new ImageRenderer(player, "Person.png", &sdl));
		////player->AddComponent(new Rigidbody());

		//Transform* t = player->GetComp<Transform>();
		//t->SetPosition(Vector2D(200, 200));

		//std::cout << "GetCompo results: " << t << std::endl;

		//GameObject* enemy = goManager.CreateObject();
		//enemy->AddComponent(new ImageRenderer(enemy, "Person.png", &sdl));
		//enemy->GetComp<Transform>()->SetPosition(Vector2D(0, 0));

		// Game loop
		while (true)
		{
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

			// DEBUG
			if (InputManager::GetInstance().GetMouseDown(1))
			{
				cout << "-" << endl;
			}
			// DEBUG


			//obj1->GetTransform()->SetPosition(InputManager::GetInstance().GetMousePosition());

			//ImageRenderer* playerImg = static_cast<ImageRenderer*>(player->GetComponent("ImageRenderer"));
			/*if (io.GetKey(SDL_SCANCODE_RIGHT))
			{
				velX = 1;
			}*/

			Vector2D velocity = Vector2D(InputManager::GetInstance().GetAxis(SDL_SCANCODE_RIGHT, SDL_SCANCODE_LEFT), InputManager::GetInstance().GetAxis(SDL_SCANCODE_DOWN, SDL_SCANCODE_UP));
			paddleObj->GetTransform()->Translate(velocity * paddleSpeed, true);
			//playerText->rect.x = player->GetTransform()->_position.X - playerText->rect.h / 2;
			//playerText->rect.y = player->GetTransform()->_position.Y - playerText->rect.h;

			//Vector2D scaleocity = Vector2D(InputManager::GetInstance().GetAxis(SDL_SCANCODE_D, SDL_SCANCODE_A), InputManager::GetInstance().GetAxis(SDL_SCANCODE_S, SDL_SCANCODE_W));
			//player->GetTransform()->SetSize(player->GetTransform()->_size + scaleocity);

			//if (io.GetMouseDown(1))
			//{
			//	Image *temp = sdl.CreateImage("Person.png");
			//	int offsetX = temp->rect.w / 2, offsetY = temp->rect.h / 2;

			//	temp->rect.x = io.GetMouseX() - offsetX;
			//	temp->rect.y = io.GetMouseY() - offsetY;
			//}

			//// Logic
			//int velX = 0, velY = 0;
			//int offsetX = playerImage->rect.w / 2, offsetY = playerImage->rect.h / 2;

			//velX = io.GetMouseX();
			//velY = io.GetMouseY();
			//playerImage->rect.x = velX - offsetX;
			//playerImage->rect.y = velY - offsetY;

			//// Render ////
			SDLWrapper::GetInstance().RenderImages(true);
		}
	}

	return 0;
}
