#pragma once
#include <memory>
#include <vector>
#include "Component.h"
using namespace std;
class Transform;

class GameObject
{
public:
	GameObject();
	~GameObject();
	void Update();
	std::shared_ptr<Component> AddComponent(std::shared_ptr<Component> comp);
	void AddComponents(std::vector<std::shared_ptr<Component>> components);
	std::shared_ptr<Transform> GetTransform() const;
	//template <class T>
	//inline T* GetComponent()
	//{
	//	for (auto it : _components)
	//	{
	//		//T* t = static_cast<T*>(it);
	//		//if (t != NULL)
	//		if (typeid(*it) == typeid(T))
	//		{
	//			return static_cast<T*>(it);
	//			//return dynamic_cast<T*>(it);
	//			//return t;
	//		}
	//	}
	//	return NULL;
	//}
	template <class T>
	inline shared_ptr<T> GetComponent()
	{
		for (auto it : _components)
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
	//inline T* GetComp()
	//{
	//	for (auto it : _components)
	//	{
	//		T* t = static_cast<T*>(it);
	//		if (t != NULL)
	//		{
	//			return dynamic_cast<T*>(it);
	//			//return it;
	//		}
	//	}
	//	return NULL;
	//}
	void SetTag(std::string tag);
	std::string GetTag() const { return _tag; }
	bool CompareTag(std::string otherTag) const { return (_tag == otherTag); }
	void SendCollisionEnter(std::shared_ptr<Collider> other);
	void SendCollisionExit(std::shared_ptr<Collider> other);
	void SetActive(bool active);
	bool IsActive() const { return _isActive; }
private:
	std::string _tag;
	std::vector<shared_ptr<Component>> _components;
	std::shared_ptr<Transform> _transform;
	bool _isActive;
};
