#pragma once
#include "Component.h"
#include "GameObject.h"
#include "SDLWrapper.h"

class ImageRenderer :
	public Component
{
public:
	ImageRenderer(std::string imageFilename);
	~ImageRenderer();
private:
	GameObject* _gameObject;
	Drawable* _image;
	void Update() override;
	void UpdateRect() const;
};

