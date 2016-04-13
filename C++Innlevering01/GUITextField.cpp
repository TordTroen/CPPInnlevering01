#include "GUITextField.h"
#include "SDL.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include <string>
#include <iostream>
#include <sstream>

GUITextField::GUITextField(std::string startText, Rect rect)
	: GUIButton(startText, Color(255, 255, 255), Color(0, 0, 0), Color(0, 255, 0), Color(255, 0, 0), rect, 8, NULL, true, 117),
	takeInput(false)
{
	//GameObject* textObj = GameObjectManager::GetInstance().CreateObject();
	//textItem = dynamic_cast<GUIText*>(textObj->AddComponent(new GUIText("Text", Color(250, 250, 250), Rect(10, 400, 100, 100))));
}


GUITextField::~GUITextField()
{
}

void GUITextField::Update()
{
	GUIButton::Update();
	if (takeInput)
	{
		// TODO Put this in the SDLWrapper and InputManager, so we can just call a function here
		// TODO Implement a cursor for the input (either SDL has something or we have to calculate the position, that can be very hard...)
		// Made with help from Lazyfoo's tutorial (http://lazyfoo.net/tutorials/SDL/32_text_input_and_clipboard_handling/index.php)
		bool renderText = false;
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_KEYDOWN)
			{
				if (e.key.keysym.sym == SDLK_ESCAPE || e.key.keysym.sym == SDLK_RETURN) // Stop input when ESC or Enter is pressed
				{
					StopInput();
				}
				else if (e.key.keysym.sym == SDLK_BACKSPACE && inputText.length() > 0) // Delete last character when pressing backspace
				{
					inputText.pop_back();
					renderText = true;
				}
				else if (e.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL) // Copy the text in the field
				{
					SDL_SetClipboardText(inputText.c_str());
				}
				else if (e.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL) // Paste at the end of the text field
				{
					inputText += SDL_GetClipboardText();
					renderText = true;
				}
			}
			else if (e.type == SDL_TEXTINPUT)
			{
				inputText += e.text.text;
				renderText = true;
			}

			// Change the text 
			if (renderText)
			{
				if (inputText == "")
				{
					inputText = " ";
				}

				// TODO Replace with textItem->SetText() when GUIButton uses two GUIXXX instead of Drawables
				Color color = textItem->GetColor();
				if (textItem != NULL)
				{
					// TODO Delete the previous text instead of deactivating it
					textItem->SetActive(false);
				}
				textItem = SDLWrapper::GetInstance().CreateText(inputText, color, textItem->GetRect());
				textItem->SetActive(IsActive());
			}
		}
	}
}

void GUITextField::OnClick()
{
	if (takeInput)
	{
		StopInput();
	}
	else
	{
		StartInput();
	}
}


void GUITextField::StartInput()
{
	//Enable text input 
	SDL_StartTextInput();
	takeInput = true;
	
	// TODO Highlight the field when inputting
}

void GUITextField::StopInput()
{
	takeInput = false;
	SDL_StopTextInput();
	std::cout << "Input: " << inputText << std::endl;
}