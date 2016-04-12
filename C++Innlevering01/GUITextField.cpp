#include "GUITextField.h"
#include "SDL.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include <string>
#include <iostream>
#include <sstream>

GUITextField::GUITextField()
	: GUIButton("Text input", Color(255, 255, 255), Color(0, 0, 0), Color(0, 255, 0), Color(255, 0, 0), Rect(10, 400, 100, 100), 8, NULL, true, 117),
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
		bool renderText = false;
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_KEYDOWN)
			{
				if (e.key.keysym.sym == SDLK_ESCAPE || e.key.keysym.sym == SDLK_KP_ENTER)
				{
					StopInput();
				}
			}
			else if (e.type == SDL_TEXTINPUT)
			{
				inputText += e.text.text;
				renderText = true;
			}
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
	//Main loop flag 
	//bool quit = false; 
	//Event handler 
	//SDL_Event e; 
	//Set text color as black 
	//SDL_Color textColor = { 0, 0, 0, 0xFF }; 
	//The current input text. 
	//std::string inputText = "Some Text"; 
	//gInputTextTexture.loadFromRenderedText( inputText.c_str(), textColor ); 
	

	//Enable text input 
	SDL_StartTextInput();
	takeInput = true;
	//std::cout << "Input: " << inputText << std::endl;
}

void GUITextField::StopInput()
{
	takeInput = false;
	SDL_StopTextInput();
	std::cout << "Input: " << inputText << std::endl;
}
