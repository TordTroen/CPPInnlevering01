#include "InputManager.h"
#include <Memory>
#include "SDL.h"
#include <iostream>
using namespace std;

void InputManager::Init()
{
	keyCount		= 0;
	keys			= SDL_GetKeyboardState(&keyCount);
	oldKeys			= unique_ptr<Uint8>(new Uint8[keyCount]);
	mouseButtons	= SDL_GetRelativeMouseState(&mouseX, &mouseY);
	oldMouseButtons = mouseButtons;
}

void InputManager::Update()
{
	// TODO Try to make Update return an int
	// events like hitting window X, returns 1 or something
	memcpy(oldKeys.get(), keys, keyCount * sizeof(Uint8));

	oldMouseButtons = mouseButtons;
	mouseButtons	= SDL_GetRelativeMouseState(NULL, NULL);
	SDL_GetMouseState(&mouseX, &mouseY);

	SDL_PumpEvents();
}

int InputManager::GetAxis(int positiveKey, int negativeKey) const
{
	int ret = 0;
	if (GetKey(positiveKey) && !GetKey(negativeKey)) { ret =  1; }
	if (GetKey(negativeKey) && !GetKey(positiveKey)) { ret = -1; }
	return ret;
}

int InputManager::GetAxisDown(int positiveKey, int negativeKey) const
{
	int ret = 0;
	if (GetKeyDown(positiveKey) && !GetKeyDown(negativeKey)) { ret = 1; }
	if (GetKeyDown(negativeKey) && !GetKeyDown(positiveKey)) { ret = -1; }
	return ret;
}
