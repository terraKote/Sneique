#include "ObjectManager.h"

const unsigned int Object::GetIndex() {
	return _index;
}

const std::string Object::GetName()
{
	return _name;
}

void Object::Update(double deltaTime) {
}

void Object::Draw(double deltaTime) {
}

std::vector<Object*> ObjectManager::GetCreatedObjects() {
	return _createdObjects;
}

Object* ObjectManager::FindObject(std::string name)
{
	Object* target = nullptr;

	for (const auto object : _createdObjects)
	{
		if (object->GetName() == name)
		{
			target = object;
			break;
		}
	}

	return target;
}
