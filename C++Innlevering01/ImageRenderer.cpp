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
	std::cout << "Deleting component " << typeid(this).name() << std::endl;
	SDLWrapper::GetInstance().DeleteDrawable(&image);
}

void ImageRenderer::OnSetActive()
{
	image->SetActive(IsActive());
}

void ImageRenderer::Update()
{
	image->SetRect(GetTransform()->GetRect());
}
