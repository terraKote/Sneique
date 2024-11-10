#pragma once
#include <vector>
#include <utility>
#include <string>

#include "Singleton.h"

class Object
{
private:
	unsigned int _index;
	std::string _name;

public:
	explicit Object(int id, std::string name) {
		_index = id;
		_name = name;
	}

	virtual ~Object() = default;

	const unsigned int GetIndex();
	const std::string GetName();

	virtual void Update(double deltaTime);
	virtual void Draw(double deltaTime);
};

class ObjectManager
{
	friend class Singleton<ObjectManager>;

private:
	std::vector<Object*> _createdObjects;

	ObjectManager() = default;
	~ObjectManager() = default;

public:
	std::vector<Object*> GetCreatedObjects();

	template <typename T, typename... Args>
	T* CreateObject(std::string name, Args&&... args);

	Object* FindObject(std::string name);
};

template <typename T, typename... Args>
T* ObjectManager::CreateObject(std::string name, Args&&... args) {
	static_assert(std::is_base_of<Object, T>::value, "T must be derived from Object");

	T* object = new T(_createdObjects.size(), name, std::forward<Args>(args)...);
	_createdObjects.push_back(object);
	return object;
}

