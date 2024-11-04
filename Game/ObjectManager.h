#pragma once
#include <vector>
#include <utility>

class Object
{
private:
	unsigned int _index;

public:
	explicit Object(int id) : _index(id) {}
	virtual ~Object() = default;

	const unsigned int GetIndex();

	virtual void Update(double deltaTime);
	virtual void Draw(double deltaTime);
};

class ObjectManager
{
private:
	std::vector<Object*> _createdObjects;

public:
	std::vector<Object*> GetCreatedObjects();

	template <typename T, typename... Args>
	T* CreateObject(Args&&... args); // Pass int to create object
};

template <typename T, typename... Args>
T* ObjectManager::CreateObject(Args&&... args) {
	static_assert(std::is_base_of<Object, T>::value, "T must be derived from Object");

	T* object = new T(_createdObjects.size(), std::forward<Args>(args)...); 
	_createdObjects.push_back(object);
	return object;
}

