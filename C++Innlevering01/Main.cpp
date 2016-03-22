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
using namespace std;

int main(int argc, char** argv)
{
	GameObjectManager goManager = GameObjectManager(GameManager::GetInstance().GetWindowWidth(),
		GameManager::GetInstance().GetWindowHeight());
	SDLWrapper sdl;
	InputManager io;
	Time time;

	// Initialize stuff that gameobject, gameloop, etc are dependant on
	if (sdl.InitializeWindow("Breakout", GameManager::GetInstance().GetWindowWidth(),
		GameManager::GetInstance().GetWindowHeight(), Color(200, 200, 200)) == 0)
	{
		Text* playerText = sdl.CreateText("Playername", { 100, 200, 0 }, 0, 0);

		// Create gameobject here
		GameObject* player = goManager.CreateObject();
		player->AddComponent(new ImageRenderer(player, "Person.png", &sdl));
		//player->AddComponent(new Rigidbody());

		Transform* t = player->GetComp<Transform>();
		t->SetPosition(Vector2D(200, 200));

		std::cout << "GetCompo results: " << t << std::endl;

		GameObject* enemy = goManager.CreateObject();
		enemy->AddComponent(new ImageRenderer(enemy, "Person.png", &sdl));
		enemy->GetComp<Transform>()->SetPosition(Vector2D(0, 0));
		//Image *playerImage = sdl.CreateImage("Person.png");

		// Game loop
		while (true)
		{
			//// Update everything that needs to be updated every frame ////
			goManager.Update();
			io.Update();
			time.Update();

			//// Logic ////
			if (io.GetKeyDown(SDL_SCANCODE_ESCAPE))
			{
				break;
			}
			//ImageRenderer* playerImg = static_cast<ImageRenderer*>(player->GetComponent("ImageRenderer"));
			/*if (io.GetKey(SDL_SCANCODE_RIGHT))
			{
				velX = 1;
			}*/
			
			Vector2D velocity = Vector2D(io.GetAxis(SDL_SCANCODE_RIGHT, SDL_SCANCODE_LEFT), io.GetAxis(SDL_SCANCODE_DOWN, SDL_SCANCODE_UP));
			player->GetTransform()->Translate(velocity, true);
			playerText->rect.x = player->GetTransform()->_position.X - playerText->rect.h / 2;
			playerText->rect.y = player->GetTransform()->_position.Y - playerText->rect.h;

			Vector2D scaleocity = Vector2D(io.GetAxis(SDL_SCANCODE_D, SDL_SCANCODE_A), io.GetAxis(SDL_SCANCODE_S, SDL_SCANCODE_W));
			player->GetTransform()->SetSize(player->GetTransform()->_size + scaleocity);

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
			sdl.RenderImages(true);
		}
	}

	return 0;
}
