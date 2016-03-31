#pragma once
#include "Component.h"
#include <vector>
#include "GUIElement.h"

class GUIMenu :
	public Component
{
public:
	GUIMenu(bool activeState = true);
	GUIMenu(std::vector<GUIElement*> elements, bool activeState = true);
	~GUIMenu();
	void AddElement(GUIElement* element);
	void AddElements(std::vector<GUIElement*> elements);
	template <class T>
	inline T* GetElement()
	{
		for (auto it : _elements)
		{
			T* t = static_cast<T*>(it);
			if (it != NULL)
			{
				return dynamic_cast<T*>(t);
			}
		}
		return NULL;
	}
protected:
	void OnSetActive() override;
private:
	std::vector<GUIElement*> _elements;
};

