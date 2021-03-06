#pragma once
#include "Component.h"
#include <vector>
#include "GUIElement.h"

class GUIMenu :
	public Component
{
public:

	/* TODO: Make the menu "parent" the GUIelements, so when a GUIMenu is moved, all attached elements also moves. */

	GUIMenu(bool activeState = true);
	~GUIMenu();
	virtual void AddElement(GUIElement* const element);

	// TODO Expand AddElementsLayout so it can align left/middle/right and also both horizontally and vertically
	/* Adds the elements of the elements parameter aligned to the center of the screen, one element under the other starting at the specified startYposition. */
	virtual void AddElements(std::vector<GUIElement*> elements);

	/* Returns the first element of the specified type */
	template <class T>
	inline T* GetElement()
	{
		// Goes through all the elements and checks if the element is of the specified type
		for (auto it : elements)
		{
			if (typeid(*it) == typeid(T))
			{
				// Cast the element to the specified type before returning it
				return dynamic_cast<T*>(it);
			}
		}
		std::cout << "WARNING: Couldn't find the element " << typeid(T).name() << " on this menu" << std::endl;
		return NULL;
	}
	int GetElementCount() const { return elements.size(); }
	virtual void RemoveElements(int startIndex, int count);
protected:
	void OnSetActive() override;
	std::vector<GUIElement*> elements;
};

