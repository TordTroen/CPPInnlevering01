#pragma once
#include <memory>
#include "Component.h"
#include "GameObject.h"
#include "SDLWrapper.h"

class ImageRenderer :
	public Component
{
public:
	ImageRenderer(std::string imageFilename);
	ImageRenderer(std::string imageFilename, Color color);
	~ImageRenderer();
	void OnSetActive() override;
	Drawable* GetImageDrawable() const { return _image; }
private:
	GameObject* _gameObject;
	Drawable* _image;
	void Update() override;
	void UpdateRect() const;
};

