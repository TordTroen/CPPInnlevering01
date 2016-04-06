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
	Drawable* GetImageDrawable() const { return image; }
private:
	GameObject* gameObject;
	Drawable* image;
	void Update() override;
	void UpdateRect() const;
};

