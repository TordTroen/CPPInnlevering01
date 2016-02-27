#include "SDLWrapper.h"
#include "InputManager.h"

int main(int argc, char** argv)
{
	SDLWrapper sdl;
	InputManager io;

	if (sdl.InitializeWindow(600, 480, Color(255, 255, 255)) == 0)
	{
		Image *playerImage = sdl.CreateImage("Person.png");

		while (true)
		{
			io.Update();
			if (io.GetKeyDown(SDL_SCANCODE_ESCAPE))
			{
				break;
			}

			if (io.GetMouseDown(1))
			{
				Image *temp = sdl.CreateImage("Person.png");
				int offsetX = temp->rect.w / 2, offsetY = temp->rect.h / 2;

				temp->rect.x = io.GetMouseX() - offsetX;
				temp->rect.y = io.GetMouseY() - offsetY;
			}

			// Logic
			int velX = 0, velY = 0;
			int offsetX = playerImage->rect.w / 2, offsetY = playerImage->rect.h / 2;

			velX = io.GetMouseX();
			velY = io.GetMouseY();
			playerImage->rect.x = velX - offsetX;
			playerImage->rect.y = velY - offsetY;

			sdl.RenderImages(true);
		}
	}

	return 0;
}