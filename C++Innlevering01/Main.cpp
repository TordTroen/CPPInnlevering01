#include "SDLWrapper.h"
#include "InputManager.h"
#include "GameObject.h"
#include "Component.h"
#include "GameObjectManager.h"
#include "ImageRenderer.h"
#include <iostream>

int main(int argc, char** argv)
{
	GameObjectManager goManager;
	SDLWrapper sdl;
	InputManager io;
	int windowWidth = 600, windowHeight = 480;
	// Initialize stuff that gameobject, gameloop, etc are dependant on
	if (sdl.InitializeWindow(windowWidth, windowHeight, Color(255, 255, 255)) == 0)
	{
		// Create gameobject here
		GameObject* player = goManager.CreateObject();
		player->AddComponent(new ImageRenderer(player, "Person.png", &sdl));

		//Image *playerImage = sdl.CreateImage("Person.png");

		// Game loop
		while (true)
		{
			goManager.Update();
			io.Update();

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
			player->GetTransform()->Translate(velocity);
			if (player->GetTransform()->_position.X > windowWidth)
			{
				player->GetTransform()->SetPosition(Vector2D(-player->GetTransform()->_size.X, 0));
			}


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

			sdl.RenderImages(true);
		}
	}

	return 0;
}
