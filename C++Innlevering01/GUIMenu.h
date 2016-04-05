#pragma once
#include "Component.h"
#include <vector>
#include "GUIElement.h"

class GUIMenu :
	public Component
{
public:
	GUIMenu(bool activeState = true);
	~GUIMenu();
	void AddElement(GUIElement* const element);
	/* Adds the elements of the elements parameter aligned to the center of the screen, one element under the other starting at the specified startYposition. */
	void AddElementsLayout(int startYposition, int spacing, std::vector<GUIElement*> elements);
	template <class T>
	inline T* GetElement()
	{
		for (auto it : _elements)
		{
			//T* t = static_cast<T*>(it);
			//if (t != NULL)
			if (typeid(*it) == typeid(T))
			{
				//std::cout << "same type" << std::endl;
				//return it;
				//return dynamic_pointer_cast<T>(it);
				return dynamic_cast<T*>(it);
				//return t;
				//return it;
			}
		}
		return NULL;
	}
	//template <class T>
	//inline std::shared_ptr<T> GetElement()
	//{
	//	for (auto it : _elements)
	//	{
	//		T* t = static_cast<T*>(it);
	//		if (it != NULL)
	//		{
	//			return dynamic_cast<T*>(t);
	//		}
	//	}
	//	return NULL;
	//}
protected:
	void OnSetActive() override;
private:
	std::vector<GUIElement*> _elements;
};

