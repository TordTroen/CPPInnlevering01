#pragma once
#include <memory>
#include <SDL.h>

class InputManager
{
public:
	InputManager();
	~InputManager();
	void Update();
	bool GetKeyDown(int keyId) const { return CurKeyDown(keyId) && !OldKeyDown(keyId); }
	bool GetKeyUp(int keyId) const { return !CurKeyDown(keyId) && OldKeyDown(keyId); }
	bool GetKey(int keyId) const { return CurKeyDown(keyId) && OldKeyDown(keyId); }
	bool GetMouseDown(int buttonId) const { return CurMouseDown(buttonId) && !OldMouseDown(buttonId); }
	bool GetMouseUp(int buttonId) const { return !CurMouseDown(buttonId) && OldMouseDown(buttonId); }
	bool GetMouse(int buttonId) const { return CurMouseDown(buttonId) && OldMouseDown(buttonId); }
	int GetMouseX() const { return mouseX; }
	int GetMouseY() const { return mouseY; }
protected:
	const Uint8 *keys;
	std::unique_ptr<Uint8> oldKeys;
	int keyCount;
	int mouseX;
	int mouseY;
	Uint8 mouseButtons;
	Uint8 oldMouseButtons;
private:
	bool CurKeyDown(const int& keyId) const { return keys[keyId] == 1; }
	bool OldKeyDown(const int& keyId) const { return oldKeys.get()[keyId] == 1; }
	bool CurMouseDown(const int& buttonId) const { return mouseButtons == SDL_BUTTON(buttonId); }
	bool OldMouseDown(const int& buttonId) const { return oldMouseButtons == SDL_BUTTON(buttonId); }
};

