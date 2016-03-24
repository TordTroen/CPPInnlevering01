#include "ImageRenderer.h"
#include "Transform.h"
#include <iostream>
using namespace std;

ImageRenderer::ImageRenderer(GameObject *gameobject, std::string imageFilename)
{
	_gameObject = gameobject;
	_image = SDLWrapper::GetInstance().CreateImage(imageFilename, Rect(0, 0, 0, 0));
	UpdateRect();
}

ImageRenderer::~ImageRenderer()
{
}

void ImageRenderer::Update()
{
	UpdateRect();
}

void ImageRenderer::UpdateRect() const
{
	_image->rect.x = _gameObject->GetTransform()->_position.X;
	_image->rect.y = _gameObject->GetTransform()->_position.Y;
	_image->rect.w = _gameObject->GetTransform()->_size.X;
	_image->rect.h = _gameObject->GetTransform()->_size.Y;
}
