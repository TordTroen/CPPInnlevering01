#include "ImageRenderer.h"
#include "Transform.h"
#include <iostream>
using namespace std;

ImageRenderer::ImageRenderer(std::string imageFilename)
{
	_image = SDLWrapper::GetInstance().CreateImage(imageFilename, Rect(0, 0, 0, 0));
}

ImageRenderer::ImageRenderer(std::string imageFilename, Color color)
{
	_image = SDLWrapper::GetInstance().CreateImage(imageFilename, Rect(0, 0, 0, 0), color);
}


ImageRenderer::~ImageRenderer()
{
}

void ImageRenderer::OnSetActive()
{
	_image->SetActive(IsActive());
}

void ImageRenderer::Update()
{
	UpdateRect();
}

void ImageRenderer::UpdateRect() const
{
	_image->SetRect(GetTransform()->GetRect());
}
