#pragma once
#include "Component.h"
#include <vector>
#include "GUIElement.h"

class GUIMenu :
	public Component
{
public:
	GUIMenu(bool activeState = true);
	GUIMenu(std::vector<std::shared_ptr<GUIElement>> elements, bool activeState = true);
	~GUIMenu();
	void AddElement(std::shared_ptr<GUIElement> element);
	void AddElements(std::vector<std::shared_ptr<GUIElement>> elements);
	template <class T>
	inline std::shared_ptr<T> GetElement()
	{
		for (auto it : _elements)
		{
			//T* t = static_cast<T*>(it);
			//if (t != NULL)
			if (typeid(*it) == typeid(T))
			{
				//std::cout << "same type" << std::endl;
				//return it;
				return dynamic_pointer_cast<T>(it);
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
	std::vector<std::shared_ptr<GUIElement>> _elements;
};

