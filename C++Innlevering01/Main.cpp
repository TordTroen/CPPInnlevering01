#include "SDLWrapper.h"
#include "InputManager.h"
#include "GameObject.h"
#include "Transform.h"
#include "GameObjectManager.h"
#include "ImageRenderer.h"
#include <iostream>
#include "GameManager.h"
#include "Vector2D.h"
#include "Time.h"
#include "GUIButton.h"
#include "GUIMenu.h"
using namespace std;
GUIMenu* menu;
void ClickTest()
{
	cout << "ClickTest()" << endl;
	menu->SetActive(false);
}

int main(int argc, char** argv)
{
	GameObjectManager goManager = GameObjectManager(GameManager::GetInstance().GetWindowWidth(),
		GameManager::GetInstance().GetWindowHeight());
//	SDLWrapper sdl;
//	InputManager io;
	InputManager::GetInstance().Init();
	Time time;

	// Initialize stuff that gameobject, gameloop, etc are dependant on
	if (SDLWrapper::GetInstance().InitializeWindow("Breakout", GameManager::GetInstance().GetWindowWidth(),
		GameManager::GetInstance().GetWindowHeight(), Color(200, 200, 200)) == 0)
	{
		/*Drawable* playerText = sdl.CreateText("Playername", Color(100, 200, 0), Rect());
		Drawable* testImg = sdl.CreateImage("Person.png", Rect(100, 100, 140, 100));
		Drawable* testTxt = sdl.CreateText("Testing", Color(100, 200, 0), Rect());*/
		//Drawable* r = sdl.CreateRect(Color(150, 100, 150, 255), Rect(20, 20, 100, 100));
		
		GameObject* menuObj = goManager.CreateObject();
		menu = dynamic_cast<GUIMenu*>(menuObj->AddComponent(new GUIMenu()));

		GameObject* button = goManager.CreateObject();
		GUIButton* btn1 = dynamic_cast<GUIButton*>(button->AddComponent(new GUIButton("Button with padding", Color(40, 40, 40), Color(50, 50, 200), Color(255, 255, 255), Color(50, 140, 255), Rect(10, 200, 100, 50), 10, ClickTest)));
		GameObject* button2 = goManager.CreateObject();
		GUIButton* btn2 = dynamic_cast<GUIButton*>(button2->AddComponent(new GUIButton("Close", Color(40, 40, 40), Color(50, 50, 200), Color(255, 255, 255), Color(60, 200, 10), Rect(10, 400, 100, 50), 0, ClickTest)));

		menu->AddElements({ btn1, btn2 });
		// TODO Make the elements through a function in GUIMenu

		/*menu->AddElement(btn1);
		menu->AddElement(btn2);*/

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
			goManager.Update();
			InputManager::GetInstance().Update();
			time.Update();

			//// Logic ////
			if (InputManager::GetInstance().GetKeyDown(SDL_SCANCODE_ESCAPE))
			{
				break;
			}
			//ImageRenderer* playerImg = static_cast<ImageRenderer*>(player->GetComponent("ImageRenderer"));
			/*if (io.GetKey(SDL_SCANCODE_RIGHT))
			{
				velX = 1;
			}*/

			/*Vector2D velocity = Vector2D(InputManager::GetInstance().GetAxis(SDL_SCANCODE_RIGHT, SDL_SCANCODE_LEFT), InputManager::GetInstance().GetAxis(SDL_SCANCODE_DOWN, SDL_SCANCODE_UP));
			player->GetTransform()->Translate(velocity, true);
			playerText->rect.x = player->GetTransform()->_position.X - playerText->rect.h / 2;
			playerText->rect.y = player->GetTransform()->_position.Y - playerText->rect.h;

			Vector2D scaleocity = Vector2D(InputManager::GetInstance().GetAxis(SDL_SCANCODE_D, SDL_SCANCODE_A), InputManager::GetInstance().GetAxis(SDL_SCANCODE_S, SDL_SCANCODE_W));
			player->GetTransform()->SetSize(player->GetTransform()->_size + scaleocity);*/

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
