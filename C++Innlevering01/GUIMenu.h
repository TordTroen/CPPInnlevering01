#pragma once
#include "Component.h"
#include <vector>
#include "GUIElement.h"

class GUIMenu :
	public Component
{
public:
	GUIMenu(std::vector<GUIElement*> elements);
	~GUIMenu();
	void AddElement(GUIElement* element);
	void AddElements(std::vector<GUIElement*> elements);
protected:
	void OnSetActive() override;
private:
	std::vector<GUIElement*> _elements;
};

