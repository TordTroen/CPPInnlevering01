#include "ImageRenderer.h"
#include "Transform.h"
#include <iostream>
using namespace std;

ImageRenderer::ImageRenderer(std::string imageFilename)
{
	_image = SDLWrapper::GetInstance().CreateImage(imageFilename, Rect(0, 0, 0, 0));
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
	_image->SetRect(GetTransform()->GetRect());
}
