#include "ImageRenderer.h"
#include <iostream>

ImageRenderer::ImageRenderer(GameObject *gameobject, std::string imageFilename, SDLWrapper* sdl)
	: Component("ImageRenderer")
{
	_gameObject = gameobject;
	_image = sdl->CreateImage(imageFilename);
	UpdateRect();
}


ImageRenderer::~ImageRenderer()
{
}

void ImageRenderer::Update()
{
	UpdateRect();
}

void ImageRenderer::UpdateRect()
{
	_image->rect.x = _gameObject->GetTransform()->_position.X;
	_image->rect.y = _gameObject->GetTransform()->_position.Y;
	_image->rect.w = _gameObject->GetTransform()->_size.X;
	_image->rect.h = _gameObject->GetTransform()->_size.Y;
}
