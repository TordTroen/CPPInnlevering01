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
	std::shared_ptr<Drawable> GetImageDrawable() const { return _image; }
private:
	std::shared_ptr<GameObject> _gameObject;
	std::shared_ptr<Drawable> _image;
	void Update() override;
	void UpdateRect() const;
};

