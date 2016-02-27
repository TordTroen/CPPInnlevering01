#include "InputManager.h"
#include <Memory>
#include "SDL.h"
#include <iostream>
using namespace std;

InputManager::InputManager()
{
	keyCount = 0;
	keys = SDL_GetKeyboardState(&keyCount);
	oldKeys = unique_ptr<Uint8>(new Uint8[keyCount]);
	mouseButtons = SDL_GetRelativeMouseState(&mouseX, &mouseY);
	oldMouseButtons = mouseButtons;
}


InputManager::~InputManager()
{
}

void InputManager::Update()
{
	// TODO Try to make Update return an int
	// events like hitting window X, returns 1 or something
	memcpy(oldKeys.get(), keys, keyCount * sizeof(Uint8));

	oldMouseButtons = mouseButtons;
	mouseButtons = SDL_GetRelativeMouseState(NULL, NULL);
	SDL_GetMouseState(&mouseX, &mouseY);

	SDL_PumpEvents();
}
