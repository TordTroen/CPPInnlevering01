#include "ImageRenderer.h"
#include "Transform.h"
#include <iostream>
using namespace std;

ImageRenderer::ImageRenderer(std::string imageFilename)
{
	image = SDLWrapper::GetInstance().CreateImage(imageFilename, Rect(0, 0, 0, 0));
}

ImageRenderer::ImageRenderer(std::string imageFilename, Color color)
{
	image = SDLWrapper::GetInstance().CreateImage(imageFilename, Rect(0, 0, 0, 0), color);
}


ImageRenderer::~ImageRenderer()
{
	SDLWrapper::GetInstance().DeleteDrawable(image);
}

void ImageRenderer::OnSetActive()
{
	image->SetActive(IsActive());
}

void ImageRenderer::Update()
{
	UpdateRect();
}

void ImageRenderer::UpdateRect() const
{
	image->SetRect(GetTransform()->GetRect());
}
