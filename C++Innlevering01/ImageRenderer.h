#pragma once
#include "Component.h"
#include "GameObject.h"
#include "SDLWrapper.h"

class ImageRenderer :
	public Component
{
public:
	ImageRenderer(GameObject *gameobject, std::string imageFilename, SDLWrapper* sdl);
	~ImageRenderer();
private:
	GameObject* _gameObject;
	Image* _image;
	void Update() override;
	void UpdateRect() const;
};

